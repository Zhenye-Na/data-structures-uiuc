// CS 225 util.h
// Created Spring 2011 by Jack Toole

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include "util.h"

extern char ** environ; // man 7 environ

namespace util
{

namespace internal
{
const char * error_prefix = "";
}

void SET_ERROR_MESSAGE(const char * message)
{
	internal::error_prefix = message;
}

namespace internal
{
namespace exec
{

char * allocateCstr(const string & str)
{
	char * cstr = new char[str.size() + 1];
	str.copy(cstr, str.size());
	cstr[str.size()] = '\0';
	return cstr;
}

void freeCstr(const char * cstr)
{
	delete [] cstr;
}

pair<int, int> getFdsFromStream(const ostream * stream)
{
	int redirect_fd;
	int outpipe_fd = -1;

	if (stream == NULL)
		redirect_fd = -1;
	else if (stream == &cout || stream == &cerr) // we don't handle cerr right now; it is just left unpiped
		redirect_fd = STDOUT_FILENO;
	else
	{
		int pipe_fds[2];
		EXIT_IF_ERROR(pipe(pipe_fds) != 0);
		redirect_fd = pipe_fds[1];
		outpipe_fd = pipe_fds[0];
	}

	return make_pair(redirect_fd, outpipe_fd);
}

struct exec_timers
{
	struct itimerval remaining_real;
	struct itimerval remaining_virtual;
	struct itimerval remaining_prof;
	bool supports_virtual;
	bool supports_prof;
	exec_timers() : supports_virtual(true), supports_prof(true) { }
};

exec_timers get_exec_timers()
{
	exec_timers result;

	EXIT_IF_ERROR(getitimer(ITIMER_REAL, &result.remaining_real));

	if (getitimer(ITIMER_VIRTUAL, &result.remaining_virtual) != 0)
	{
		if (errno == EINVAL)
		{
			result.supports_virtual = false;
			errno = 0;
		}
		else
			exit_if_error_output(__FILE__, __LINE__, "getitimer(ITIMER_VIRTUAL) failed");
	}

	if (getitimer(ITIMER_PROF, &result.remaining_prof) != 0)
	{
		if (errno == EINVAL)
		{
			result.supports_prof = false;
			errno = 0;
		}
		else
			exit_if_error_output(__FILE__, __LINE__, "getitimer(ITIMER_PROF) failed");
	}

	return result;
}

void set_exec_timers(const exec_timers & timers)
{
	EXIT_IF_ERROR(setitimer(ITIMER_REAL, &timers.remaining_real, NULL));
	if (timers.supports_virtual) EXIT_IF_ERROR(setitimer(ITIMER_VIRTUAL, &timers.remaining_virtual, NULL));
	if (timers.supports_prof)    EXIT_IF_ERROR(setitimer(ITIMER_PROF,    &timers.remaining_prof, NULL));
}

void redirect_to_fd(const int redirect_fd)
{
	if (redirect_fd == -1)
	{
		int devnull_fd = open("/dev/null", O_WRONLY | O_NONBLOCK);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		dup2(devnull_fd, STDOUT_FILENO);
		dup2(devnull_fd, STDERR_FILENO);
		close(devnull_fd);
	}
	else if (redirect_fd != STDOUT_FILENO)
	{
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		dup2(redirect_fd, STDOUT_FILENO);
		dup2(redirect_fd, STDERR_FILENO);
		close(redirect_fd);
	}
}

char ** cstr_array_from_vector_string(const string & command, const vector<string> & args)
{
	// TODO (toole1): check this doesn't cause a memleak
	char ** args_cstr = new char*[args.size() + 2];
	args_cstr[0] = allocateCstr(command);
	for (size_t i = 0; i < args.size(); i++)
		args_cstr[i + 1] = allocateCstr(args[i]);
	args_cstr[args.size() + 1] = NULL;
	return args_cstr;
}

void cstr_array_free(const char * const * cstr)
{
	const char * const * curr = cstr;
	while (*curr)
	{
		freeCstr(*curr++);
	}
	delete [] cstr;
}

void fd_to_ostream(int fd, ostream * output)
{
	EXIT_IF_ERROR(fd < 0);
	EXIT_IF_ERROR(output == NULL);

	vector<char> buffer(1024);
	ssize_t char_read_count;
	do
	{
		errno = 0;
		char_read_count = ::read(fd, &buffer[0], buffer.size() - 1);

		if (char_read_count < 0 && errno == EINTR) continue;
		EXIT_IF_ERROR(char_read_count < 0);
		EXIT_IF_ERROR(static_cast<size_t>(char_read_count) + 1 > buffer.size());

		buffer[char_read_count] = '\0';
		*output << &buffer[0];

	} while (char_read_count > 0);
}

/**
 * Forks and executes the given command in child process, then returns child
 * process pid.
 * Use exec_status() to wait and retrieve child return status.
 *
 * heavily refactored, but originally from:
 * http://stackoverflow.com/questions/2180079/how-can-i-copy-a-file-on-unix-using-c
 */
pid_t exec_cmd(const char * cmd,
               const char * const * args,
               int redirect_fd,
               int outpipe_fd = -1)
{
	// Save timer values :)
	// These are preserved across the parent, but not inherited by the child
	// let's change that
	exec_timers timers = get_exec_timers();
	pid_t pid = fork();
	if (pid == 0)
	{
		// child
		set_exec_timers(timers);
		redirect_to_fd(redirect_fd);
		if (outpipe_fd != -1)
		{
			close(outpipe_fd);
		}

		// Sanitize environment
		char path[] = "PATH=/class/cs225/llvm/bin:/bin/:/usr/bin:/usr/local/bin";
		char libpath[] = "LD_LIBRARY_PATH=/software/intel-composer-2011u5-x86_64/lib/intel64/:$LD_LIBRARY_PATH"; // path for libiomp5.so
		char licenses[] = "INTEL_LICENSE_FILE=28518@intel.webstore.illinois.edu:/software/intel-composer-2011u5-x86_64/composerxe-2011.5.220/licenses:/opt/intel/licenses:/home/massung1/intel/licenses"; // also for parallel labs
		// Turn off glibc errors default write-to-terminal behaviour, because
		// it does not get caught by stderr. This instead results in an abort.
		char redirect_glibc[] = "LIBC_FATAL_STDERR_=1";
		// Turn on ASAN leak detection
		char asan_options[] = "ASAN_OPTIONS=\"detect_leaks=1\"";
		char * newenv[] = { path, libpath, licenses, redirect_glibc, asan_options, NULL };
		environ = newenv;

		// Swap out child process image with the command, searching
		// in the specified path.
		//
		// The const_cast of the argument pointer from const char ** to
		// char * const * is perfectly safe, as the string contents are never
		// modified by the call.
		//
		// The reason the argument type is char * const * is to ensure
		// backwards-compatibility for existing code, as C standard does not
		// allow implicit cast from char ** to const char * const *.
		// See RATIONALE section of
		// http://pubs.opengroup.org/onlinepubs/009695399/functions/exec.html
		// for further details.
		execvp(cmd, const_cast<char * const *>(args));

        // If control reached here, an error occured
		cerr << "exec(" << '\"' << cmd << '\"';
		while (args) {
			cerr << ", \"" << *args++ << "\"";
		}
		cerr << ") failed: " << strerror(errno) << endl;
		exit(-1);
	}
	else if (pid > 0)
	{
		// parent (success)
		// close the other end of pipe if piped, then return control to caller
		if (outpipe_fd != -1)
		{
			close(redirect_fd);
		}
	}
	return pid;
}

uint8_t exec_status(pid_t pid)
{
	int childExitStatus;
	/* parent - wait for child - this has all error handling, you
	 * could just call wait() as long as you are only expecting to
	 * have one child process at a time.
	 */
	pid_t ws = waitpid(pid, &childExitStatus, 0);
	EXIT_IF_ERROR(ws == -1);

	if (WIFEXITED(childExitStatus)) /* exit code in childExitStatus */
	{
		int8_t status = WEXITSTATUS(childExitStatus); /* zero is normal exit */
		/* handle non-zero as you wish */
		return status;
	}
	else if (WIFSIGNALED(childExitStatus)) /* killed */
	{
		// No idea why I'm doing this anymore... if it segfaults, you do too??
		kill(getpid(), WTERMSIG(childExitStatus));
		return -1;
	}
	else if (WIFSTOPPED(childExitStatus)) /* stopped */
	{
		//cout << "exec error: " << __LINE__ << endl;
		return -1;
	}
	else
		EXIT_IF_ERROR(true);
	exit(-1);
}

} // namespace exec
} // namespace internal

// replace system to centralize environment control logic
int monad_system(const char * command)
{
	return exec("sh", "-c", command);
}

int8_t exec(const string & command, const vector<string> & args, ostream * output)
{
	using namespace internal;
	using namespace internal::exec;

	pair<int, int> fds = getFdsFromStream(output);
	int redirect_fd = fds.first;
	int outpipe_fd  = fds.second;

	char ** args_cstr = cstr_array_from_vector_string(command, args);

	pid_t pid = exec_cmd(command.c_str(), args_cstr, redirect_fd, outpipe_fd);
	EXIT_IF_ERROR(pid < 0);

	cstr_array_free(args_cstr);

	// Take the output of the pipe and put it into the *output stream
	if (outpipe_fd != -1)
	{
		fd_to_ostream(outpipe_fd, output);
	}

	return exec_status(pid);
}

// TODO (toole1) this is a total hack, should use execvp like exec() below
// originally from:
// http://stackoverflow.com/questions/2180079/how-can-i-copy-a-file-on-unix-using-c
int8_t exec(int redirect_fd, const string & command, const vector<string> & args)
{
	using namespace internal::exec;

	// avoid self destruction errors from closing then trying to duplicate output
	// you can't redirect to what's already there
	if (redirect_fd == STDOUT_FILENO || redirect_fd == STDERR_FILENO)
		redirect_fd = STDOUT_FILENO;

	char ** args_cstr = cstr_array_from_vector_string(command, args);

	pid_t pid = exec_cmd(command.c_str(), args_cstr, redirect_fd);
	EXIT_IF_ERROR(pid < 0);

	cstr_array_free(args_cstr);

	return exec_status(pid);
}


// originally from stackoverflow.com user plinth
// http://stackoverflow.com/questions/2180079/how-can-i-copy-a-file-on-unix-using-c
// Modified by Jack Toole
int8_t exec(int redirect_fd, const char * command,
            const char * arg1,
            const char * arg2,
            const char * arg3,
            const char * arg4,
            const char * arg5,
            const char * arg6)
{
	using namespace internal::exec;

	const char * args[] = {command, arg1, arg2, arg3, arg4, arg5, arg6, NULL};
	const size_t args_count = (sizeof args) / (sizeof args[0]);

	// shift all nulls to end
	size_t first_null = 0;
	for (size_t i = 0; i < args_count; i++)
		if (args[i] != NULL)
			swap(args[i], args[first_null++]);

	// avoid self destruction errors from closing then trying to duplicate output
	// you can't redirect to what's already there
	if (redirect_fd == STDOUT_FILENO || redirect_fd == STDERR_FILENO)
		redirect_fd = STDOUT_FILENO;

	pid_t pid = exec_cmd(command, args, redirect_fd);
	EXIT_IF_ERROR(pid < 0);

	return exec_status(pid);
}

const char * Signal::what() const
{
	const char * desc = strsignal(signum);
	return (desc == NULL) ? "Unknown Signal" : desc;
}


int chdir(const string & dir)
{
	return ::chdir(dir.c_str());
}

string stripTrailingSlash(const string & path)
{
	if (path[path.length() - 1] == '/')
		return path.substr(0, path.length() - 1);
	else
		return path;
}

string getBaseDir(const string & path)
{
	EXIT_IF_ERROR(path.length() == 0);
	if (path[path.length() - 1] == '/') return path;
	if (exists(path + "/")) return path + "/";
	size_t slash_pos = path.find_last_of('/');
	if (slash_pos == string::npos) return "./";
	return path.substr(0, slash_pos);
}

void assertExists(const string & path, int exit_code /* = -1 */)
{
	if (!exists(path))
	{
		cerr << "Error: " << path << " does not exist." << endl;
		exit(exit_code);
	}
}

bool exists(const string & path)
{
	// Try stat-ing it
	struct stat st;
	if (stat(path.c_str(), &st) != 0) return false;
	// Check for read permission
	if ((st.st_mode & S_IRUSR) == 0) return false;

	EXIT_IF_ERROR(path == "");
	// Check for correct file/directory nature
	if (path[path.length()-1] != '/' &&
		(path.length() < 2 || !(path[path.length()-2] == '/' && path[path.length()-1] == '.')))
		return S_ISREG(st.st_mode);

	// Otherwise we want a directory
	if ((st.st_mode & S_IXUSR) == 0) return false;
	return S_ISDIR(st.st_mode);
}


mode_t permissions(const string & path)
{
	// Try stat-ing it
	struct stat st;
	if (stat(path.c_str(), &st) != 0) return -1;
	// Check for read permission
	if ((st.st_mode & S_IRUSR) == 0) return -1;

	return (st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
}


void forceRemoveDir(string dir)
{
	size_t len = dir.length();
	if (dir[len-1] == '/') dir[len-1] = '\0';
	EXIT_IF_ERROR(exec("rm","-rf",dir.c_str()) != 0);
	if (dir[len-1] == '\0') dir[len-1] = '/';
}


string getcwdstr()
{
	int len = 256;
	char * buffer = new char[len];

	char * ret = getcwd(&buffer[0], len - 1);
	while (ret == NULL && errno == ERANGE)
	{
		len *= 2;

		delete[] buffer;
		buffer = new char[len];

		ret = getcwd(&buffer[0], len - 1);
	}

	EXIT_IF_ERROR(ret == NULL);

	string cwdstr(buffer);
	delete[] buffer;

	return cwdstr + "/";
}


void copyFile(const string & source, const string & dest)
{
	assertExists(source);
	vector<string> folders = tokenize(dest, '/');
	string currdir = "";
	for (size_t i = 0; i < folders.size() - 1; i++)
	{
		currdir += folders[i] + '/';
		if (!exists(currdir))
			exec("mkdir", currdir.c_str());
	}
	exec("cp", source.c_str(), dest.c_str());
}

void copyFileOrDir(const string & source, const string & dest)
{
	if (!exists(source) && !exists(source + "/"))
	{
		cerr << __func__ << ": " << source << " does not exist" << endl;
		exit(-1);
	}
	vector<string> folders = tokenize(dest, '/');
	string currdir = "";
	for (size_t i = 0; i < folders.size() - 1; i++)
	{
		currdir += folders[i] + '/';
		if (!exists(currdir))
			exec("mkdir", currdir.c_str());
	}
	exec("cp", "-R", source.c_str(), dest.c_str());
}

void copyFiles(const string & sourceFolder, const string & destFolder, const vector<string> & files)
{
	assertExists(destFolder);
	for (size_t i = 0; i < files.size(); i++)
	{
		string sourceFile = sourceFolder + files[i];
		assertExists(sourceFile);
		copyFile(sourceFile, destFolder);
	}
}


void protectFiles(const string & folder, const vector<string> & files)
{
	(void) folder;
	(void) files;
#if 0 // (debug)
	for (size_t i = 0; i < files.size(); i++)
	{
		string file = folder + files[i];
		assertExists(file);

		if (chmod(file.c_str(), S_IRUSR) != 0)
		{
			perror("chmod failed");
			exit(-1);
		}
	}
#endif
}

void protectDir(const string & dir)
{
	(void) dir;
	// (debug) EXIT_IF_ERROR(exec("/bin/chmod", "-R", "ugoa-w", dir.c_str()) != 0);
}

// Originally from Simon Biber
// http://bytes.com/topic/c/answers/545614-list-files-current-directory
vector<string> get_files_in_dir(const string & dir, bool concatdir /* = true */)
{
	EXIT_IF_ERROR(dir == "" || dir[dir.length()-1] != '/', "Directory name must end in a '/'");

	vector<string> files;
	DIR * dirp = opendir(dir.c_str());
	if (dirp == NULL) return files;

	struct dirent * ent = readdir(dirp);
	while (ent != NULL)
	{
		string file = ent->d_name;
		if (file != "." && file != "..")
			files.push_back(concatdir ? dir + file : file);
		ent = readdir(dirp);
	}

	closedir(dirp);
	return files;
}

bool is_symlink(const string & file)
{
	// Try lstat-ing it
	struct stat st;
	if (lstat(file.c_str(), &st) != 0) return -1;
	// Check for read permission
	if ((st.st_mode & S_IRUSR) == 0) return false;

	// & with symlink bit
	return (S_ISLNK(st.st_mode)) != 0;
}

string get_symlink_target(const string & symlink)
{
	const size_t buf_size = 4096;
	char buf[buf_size+1]; // TODO (toole1): hack-y value
	ssize_t len = readlink(symlink.c_str(), buf, buf_size);
	EXIT_IF_ERROR(len < 0 || static_cast<size_t>(len) == buf_size, "Error getting target of symlink " + symlink);
	buf[len] = '\0';
	return string(buf);
}

void linkDirs(const string & sourceFolder, const string & destFolder, const vector<string> & dirs)
{
	assertExists(destFolder);
	for (size_t i = 0; i < dirs.size(); i++)
	{
		string source = sourceFolder + dirs[i];
		string target = destFolder   + dirs[i];

		// Check for redundant monad/ directory
		// This allows the monad/ dir to be safely renamed
		if (replaceFirst(source, "/../monad/","/"))
			replaceFirst(target, "/monad/","/");

		assertExists(destFolder + source + '/');

		if (symlink(source.c_str(), target.c_str()) != 0)
		{
			cerr << "symlink failed: " << target << ": ";
			perror(NULL);
			exit(-1);
		}
	}
}


bool replaceFirst(string & str, const string & toreplace, const string & with)
{
	size_t i = str.find(toreplace);
	if (i != string::npos)
	{
		str.replace(i,toreplace.length(),with);
		return true;
	}
	return false;
}

size_t replaceAll(string & str, const string & toreplace, const string & with)
{
	size_t i = str.find(toreplace);
	size_t count = 0;

	while (i != string::npos)
	{
		str.replace(i,toreplace.length(),with);
		i = str.find(toreplace, i + with.length());
		count++;
	}

	return count;
}

size_t replaceAllInternal(string & str, const string & toreplace, const string & with)
{
	size_t i = str.find(toreplace);
	size_t count = 0;

	while ((i != string::npos) && (i != str.length() - toreplace.length()))
	{
		str.replace(i,toreplace.length(),with);
		i = str.find(toreplace, i + with.length());
		count++;
	}

	return count;
}


size_t findNthLast(const string & str, char c, size_t n)
{
	if (str.length() == 0) return string::npos;
	size_t i = str.length() - 1;

	do
	{
		if (str[i] == c) n--;
		if (n == 0) return i;
	} while (i-- != 0);

	return string::npos;
}


string read_string_from_FILE(FILE * file, size_t max_length /* = -1 */)
{
	vector<char> v;
	v.reserve(256);

	while (true)
	{
		int nextchar = fgetc(file);
		if (nextchar == '\0' || nextchar == EOF)
			break;
		if (v.size() < max_length)
			v.push_back(nextchar);
	}

	if (v.size() == max_length)
	{
		v.push_back('.');
		v.push_back('.');
		v.push_back('.');
	}

	v.push_back('\0');

	return string(&v[0]);
}

void write_string_to_FILE(FILE * file, const char * str)
{
	fflush(file);
	size_t i = 0;
	do
	{
//		cout << (int)str[i] << ' ';
		fputc(str[i], file);

		// We use a do-while because we want the \0 to be written to the stream
		// for sending multiple strings
	} while (str[i++] != 0);

//	cout << endl;

	fflush(file);
}



/**
*
*
**/

string readFile(const string & filename)
{
	ifstream file;
	file.open(filename.c_str());
	if (!file.good())
		return "";

	stringbuf linebuf;
	file.get(linebuf, '\0');
	linebuf.pubsync();
	return linebuf.str();
}

void readFile( string filename, vector<string> & lines ) {
    ifstream file( filename.c_str() );
    while( file ) {
        // read in line
        string line;
        getline( file, line );

        int len = line.length();
        if( len == 0 )
            continue;

        // if we're reading an improperly encoded file for this platform,
        // we may need to check for trailing \r's (e.g. reading Windows
        // files on Linux)
        if( line[len - 1] == '\r' )
            line.replace( --len, 1, "" );

        if( len == 0 )
            continue;
        lines.push_back( line );
    }
}

OptionsParser::OptionsParser()
{
	valueMap[""]      = true;

	valueMap["yes"]   = true;
	valueMap["no"]    = false;

	valueMap["on"]    = true;
	valueMap["off"]   = false;

	valueMap["true"]  = true;
	valueMap["false"] = false;

	valueMap["1"]     = true;
	valueMap["0"]     = false;
}

vector<string> OptionsParser::parse(int argc, const char * const * argv)
{
	vector<string> rawArgs(argv, argv + argc);
	return parse(rawArgs);
}

vector<string> OptionsParser::parse(const vector<string> & rawArgs)
{
	vector<string> unprocessedArgs;
	size_t out_arg_i = 0;

	for (size_t arg_i = 1; arg_i < rawArgs.size(); arg_i++)
	{
		const string & originalCaseArg = rawArgs[arg_i];
		string currarg = toLower(originalCaseArg);

		if (currarg.compare(0, 2, "--") == 0) //long option
		{
			bool invert = (currarg.compare(2, 2, "no") == 0);
			size_t name_i = (invert ? 4 : 2);
			size_t equalspos = currarg.find_first_of("=-", name_i);

			string name = currarg.substr(name_i, equalspos - name_i);
			string value = (equalspos >= currarg.length()) ? "" : currarg.substr(equalspos);

			optsMap_t::iterator option = optsMap.find(name);
			if (option == optsMap.end())
			{
				cerr << "Unknown option: " << currarg << endl;
				exit(-1);
			}

			valueMap_t::iterator valueIt = valueMap.find(value);
			if (valueIt == valueMap.end())
			{
				cerr << "Unknown value: " << currarg << endl;
				exit(-1);
			}

			*option->second = valueIt->second ^ invert;
		} // "--"

		else if (currarg[0] == '-') //string of single char options
		{
			for (size_t c = 1; currarg[c] != '\0'; c++)
			{
				optsMap_t::iterator option = optsMap.find(string(1,currarg[c]));
				if (option == optsMap.end())
				{
					cerr << "Unknown option: -" << currarg[c] << endl;
					exit(-1);
				}
				*option->second = true;
			}
		}

		else //positional argument
		{
			if (out_arg_i < args.size())
				*args[out_arg_i] = originalCaseArg;
			else
				unprocessedArgs.push_back(originalCaseArg);
			out_arg_i++;
		}
	}

	return unprocessedArgs;
}

char * processOptions(int argc, char ** argv, OptionsMap & opts, vector<string> & args)
{
	for (int arg_i = 1; arg_i < argc; arg_i++)
	{
		char * currarg = argv[arg_i];

		if (strncmp(currarg, "--", 2) == 0) //long option
		{
			bool value, invert;
			size_t string_i;

			if (strncasecmp(currarg+2, "no", 2) == 0)
			{
				invert = true;
				string_i = 4;
			}
			else
			{
				invert = false;
				string_i = 2;
			}

			size_t equals_i = string_i;
			while (currarg[equals_i] != '\0' && currarg[equals_i] != '=')
				equals_i++;
			if (currarg[equals_i] == '=')
				currarg[equals_i++] = '\0';

			OptionsMap::iterator option = opts.find(currarg+string_i);

			if (option == opts.end())
			{
				cerr << "Unknown option: " << currarg << endl;
				return currarg;
			}

			char valuechar = tolower(currarg[equals_i]);
			if (valuechar == 'o') valuechar = tolower(currarg[equals_i+1]) + 1;
			switch (valuechar)
			{
				case '\0'  : value = true;  break;
				case 'f'+1 : value = false; break; //off: see 'o' above
				case 'n'   : value = false; break;
				case 'n'+1 : value = true;  break; //on: contrast 'n': see 'o' above
				case 't'   : value = true;  break;
				case 'y'   : value = true;  break;
				default:
					cerr << "Unknown option value: " << currarg << endl;
					return currarg;
			}

			(*option).second = value ^ invert;
		} // "--"

		else if (currarg[0] == '-') //string of single char options
		{
			for (size_t c = 1; currarg[c] != '\0'; c++)
			{
				OptionsMap::iterator option = opts.find(string(1,currarg[c]));
				if (option == opts.end())
				{
					cerr << "Unknown option: -" << currarg[c] << endl;
					currarg[1] = currarg[c];
					currarg[2] = '\0';
					return currarg;
				}
				(*option).second = true;
			}
		}

		else //positional argument
			args.push_back(currarg);
	}

	return NULL;
}



void makeLower(string & str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		str[i] = tolower(str[i]);
	}
}

string toLower(const string & str)
{
	string s(str);
	makeLower(s);
	return s;
}



/**
*  A wrapper function which writes a buffer to a file.
**/
ssize_t writeBytesToFile(signed int fileDescriptor, const char * buffer, unsigned int bufferLength) {
	return writen(fileDescriptor, buffer, bufferLength);
}


// From Steven's Unix Net Programming
// http://www.kohala.com/start/
/* Write "n" bytes to a descriptor. */
ssize_t writen(int fd, const void *vptr, size_t n)
{
	size_t         nleft;
	ssize_t        nwritten;
	const int8_t * ptr;

	ptr = static_cast<const int8_t*>(vptr);
	nleft = n;
	while (nleft > 0) {
		if ( (nwritten = ::write(fd, ptr, nleft)) <= 0) {
			if (errno == EINTR)
				nwritten = 0; /* and call write() again */
			else
				return -1; /* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	return n;
}




// From Steven's Unix Net Programming
// http://www.kohala.com/start/
/* Read "n" bytes from a descriptor. */
ssize_t readn(int fd, void *vptr, size_t n)
{
	size_t   nleft;
	ssize_t  nread;
	int8_t * ptr;

	ptr = static_cast<int8_t*>(vptr);
	nleft = n;
	while (nleft > 0) {
		if ( (nread = ::read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0; /* and call read() again */
			else
				return -1;
		}
		else if (nread == 0)
			break; /* EOF */

		nleft -= nread;
		ptr   += nread;
	}
	return n - nleft; /* return >= 0 */
}


// TODO (toole1): This should be moved to monad since it's very
// namespace specific and unlikely to be used similarly elsewhere
void rename_main(const string & file, const string & newname)
{
	assertExists(file);
	exec( "sed", "-i", "-e",
	      ( "s/int[\\r\\n \\t][\\r\\n \\t]*main[\\r\\n \\t]*(\\(.*\\))/namespace proxy_test { int " + newname +
		    "(\\1); } int proxy_test::" + newname + "(\\1)/" ).c_str(),
	      file.c_str() );
}

vector<string> tokenize(const string & str, char delim)
{
	vector<string> args;

	size_t start = 0;
	size_t end;
	for (end = str.find(delim); end != string::npos; end = str.find(delim, start))
	{
		args.push_back(str.substr(start, end - start));
		start = end+1;
	}
	args.push_back(str.substr(start, str.size() - start));

	return args;
}

vector<string> tokenize(const string & str, const string & delims)
{
	vector<string> args;

	size_t start = 0;
	while (start < str.length() && delims.find(str[start]) != string::npos) start++;
	size_t end;
	for (end = str.find_first_of(delims); end != string::npos; end = str.find_first_of(delims, start))
	{
		args.push_back(str.substr(start, end - start));
		start = end+1;
		while (start < str.length() && delims.find(str[start]) != string::npos) start++;
	}
	if (start < str.length())
		args.push_back(str.substr(start, str.length() - start));

	return args;
}

namespace colorize
{
const char * BLACK = "\033[39m";
const char * GREEN = "\033[32m";
const char * RED   = "\033[31m";
const bool is_color_enabled = isatty(STDOUT_FILENO);


}

} // namespace util

