/**
 * @file util.cpp
 * CS 225 Util Library
 * @author Jack Toole
 */

#ifndef UTIL_H
#define UTIL_H

#define __STDC_LIMIT_MACROS

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace util
{
using namespace std;

namespace internal
{
extern const char * error_prefix;
}

/**
 * Comparator for case-insensitive comparison in STL assosiative containers.
 *
 * From Abhay:                                                        
 * @see http://stackoverflow.com/questions/1801892/making-mapfind-operation-case-insensitive 
 */
struct ci_less : std::binary_function<std::string, std::string, bool>
{
    // case-independent (ci) compare_less binary function
    struct nocase_compare : public std::binary_function<unsigned char,unsigned char,bool> 
    {
        bool operator() (const unsigned char& c1, const unsigned char& c2) const
        {
            return tolower (c1) < tolower (c2);
        }
    };
    bool operator() (const std::string & s1, const std::string & s2) const
    {
        return std::lexicographical_compare
            (s1.begin (), s1.end (),   // source range
             s2.begin (), s2.end (),   // dest range
             nocase_compare ());  // comparison
    }
};

// http://stackoverflow.com/questions/5300602/template-return-type-with-default-value
template <typename T>
struct Initializer
{
	T value;
	Initializer()
		:value() // ====> default construction, works for classes _and_ built-in
	{ }
};

class Signal
{
	private:
	const int signum;
	public:
	Signal(int signal_number) : signum(signal_number) { }
	int number() const { return signum; }
	const char * what() const;
};



/**
*  Here we create a useful and easily understanable alias for the map.
**/
typedef map<string, bool, ci_less> OptionsMap;

class OptionsParser
{
	private:
	typedef map<string, bool*> optsMap_t;
	typedef map<string, bool>  valueMap_t;
	valueMap_t valueMap; // not static to prevent still reachable memory
	
	optsMap_t  optsMap;
	vector<string *> args;

	public:
	OptionsParser();
	void addOption(const string & name, bool & setValue) { optsMap[name] = &setValue; }
	void addArg(string & setValue) { args.push_back(&setValue); }
	vector<string> parse(int argc, const char * const * argv);
	vector<string> parse(const vector<string> & rawArgs);
};

// this usage of macro is an ugly hack;
// this allows replacing system() calls in dependent code without
// ambiguity conflicts.
// TODO(roh7): consider removing this hack if feasible
#undef system
// system() replacement
int monad_system(const char * command);
#define system util::monad_system

// EXEC()
int8_t exec(int redirect_fd, const char * command,
            const char * arg1 = NULL,
            const char * arg2 = NULL,
            const char * arg3 = NULL,
            const char * arg4 = NULL,
            const char * arg5 = NULL,
            const char * arg6 = NULL);

inline
int8_t exec(const char * command,
            const char * arg1 = NULL,
            const char * arg2 = NULL,
            const char * arg3 = NULL,
            const char * arg4 = NULL,
            const char * arg5 = NULL,
            const char * arg6 = NULL)
{ return exec(STDOUT_FILENO, command, arg1, arg2, arg3, arg4, arg5, arg6); }

inline int8_t exec(const string & command) { return exec(command.c_str()); }
inline int8_t exec(const string & command, const string & arg1) { return exec(command.c_str(), arg1.c_str()); }
inline int8_t exec(const string & command, const string & arg1, const string & arg2) { return exec(command.c_str(), arg1.c_str(), arg2.c_str()); }
inline int8_t exec(const string & command, const string & arg1, const string & arg2, const string & arg3) { return exec(command.c_str(), arg1.c_str(), arg2.c_str(), arg3.c_str()); }
inline int8_t exec(const string & command, const string & arg1, const string & arg2, const string & arg3, const string & arg4) { return exec(command.c_str(), arg1.c_str(), arg2.c_str(), arg3.c_str(), arg4.c_str()); }
inline int8_t exec(const string & command, const string & arg1, const string & arg2, const string & arg3, const string & arg4, const string & arg5) { return exec(command.c_str(), arg1.c_str(), arg2.c_str(), arg3.c_str(), arg4.c_str(), arg5.c_str()); }
inline int8_t exec(const string & command, const string & arg1, const string & arg2, const string & arg3, const string & arg4, const string & arg5, const string & arg6) { return exec(command.c_str(), arg1.c_str(), arg2.c_str(), arg3.c_str(), arg4.c_str(), arg5.c_str(), arg6.c_str()); }
inline int8_t exec(int redirect_fd, const string & command) { return exec(redirect_fd, command.c_str()); }
inline int8_t exec(int redirect_fd, const string & command, const string & arg1) { return exec(redirect_fd, command.c_str(), arg1.c_str()); }
inline int8_t exec(int redirect_fd, const string & command, const string & arg1, const string & arg2) { return exec(redirect_fd, command.c_str(), arg1.c_str(), arg2.c_str()); }
inline int8_t exec(int redirect_fd, const string & command, const string & arg1, const string & arg2, const string & arg3) { return exec(redirect_fd, command.c_str(), arg1.c_str(), arg2.c_str(), arg3.c_str()); }
inline int8_t exec(int redirect_fd, const string & command, const string & arg1, const string & arg2, const string & arg3, const string & arg4) { return exec(redirect_fd, command.c_str(), arg1.c_str(), arg2.c_str(), arg3.c_str(), arg4.c_str()); }
inline int8_t exec(int redirect_fd, const string & command, const string & arg1, const string & arg2, const string & arg3, const string & arg4, const string & arg5) { return exec(redirect_fd, command.c_str(), arg1.c_str(), arg2.c_str(), arg3.c_str(), arg4.c_str(), arg5.c_str()); }
inline int8_t exec(int redirect_fd, const string & command, const string & arg1, const string & arg2, const string & arg3, const string & arg4, const string & arg5, const string & arg6) { return exec(redirect_fd, command.c_str(), arg1.c_str(), arg2.c_str(), arg3.c_str(), arg4.c_str(), arg5.c_str(), arg6.c_str()); }
int8_t exec(int redirect_fd, const string & command, const vector<string> & args);
int8_t exec(const string & command, const vector<string> & args, ostream * output);
inline int8_t exec(const string & command, const vector<string> & args) { return exec(command, args, &std::cout); }

// FILESYSTEM FUNCTIONS
void assertExists(const string & path, int exit_code = -1);
bool exists(const string & path);
mode_t permissions(const string & path);
void forceRemoveDir(string dir);
string getcwdstr();

int  chdir(const string & dir);
string stripTrailingSlash(const string & path);
string getBaseDir(const string & path);
void copyFile(const string & source, const string & dest);
void copyFileOrDir(const string & source, const string & dest);
void copyFiles(const string & sourceFolder, const string & destFolder, const vector<string> & files);
void protectFiles(const string & folder, const vector<string> & files);
void protectDir(const string & dir);
void linkDirs(const string & sourceFolder, const string & destFolder, const vector<string> & dirs);
vector<string> get_files_in_dir(const string & dir, bool concatdir = true);
bool is_symlink(const string & file);
string get_symlink_target(const string & symlink);

// STRING REPLACEMENT
bool   replaceFirst(string & str, const string & toreplace, const string & with);
size_t replaceAll  (string & str, const string & toreplace, const string & with);
size_t replaceAllInternal(string & str, const string & toreplace, const string & with);
size_t findNthLast(const string & str, char c, size_t n);
vector<string> tokenize(const string & str, char delim);
vector<string> tokenize(const string & str, const string & delims);


// IO OPERATIONS
string read_string_from_FILE(FILE * file, size_t max_length = -1);
void write_string_to_FILE(FILE * file, const char * str);
ssize_t writeBytesToFile(signed int fileDescriptor, const char * buffer, unsigned int bufferLength);
ssize_t writen(int fd, const void *vptr, size_t n);
ssize_t write(int fd, const string & str);
ssize_t write(int fd, int  val);
ssize_t write(int fd, long val);
ssize_t readn(int fd, void *vptr, size_t n);
ssize_t read(int fd, int  & val);
ssize_t read(int fd, long & val);


// STRING TYPE OPERATIONS
uint32_t intlen(uint32_t a);
void makeLower(string & str);
string toLower(const string & str);

// String concatenation
template <typename T>
string to_string(const T & value);
template <typename T>
T from_string(const string & s);
template <typename T, typename F>
T lexical_cast(const F & from);
string operator+(const string & lhs, const string & rhs); // These 5 functions are to disambiguate
string operator+(const string & lhs, const char * rhs);        // operator+ so that the following
string operator+(const string & lhs, char rhs);                // templates may exist
string operator+(const char * lhs, const string & rhs);
string operator+(char lhs, const string & rhs);
template <typename T>
string & operator+=(string & str, const T & value);
template <typename T>
string operator+(const string & str, const T & value);


// CLOCK / TIMING
uint64_t process_clock();
uint64_t system_clock();

// CONFIGURATION
string readFile(const string & filename);
void readFile(string filename, vector<string> & lines);
char * processOptions(int argc, char ** argv, OptionsMap & opts, vector<string> & args);


// Exceptions
class Exception : public std::exception
{
	private:
	std::string message;

	public:
	Exception(const std::string & _message) : message(_message) { }
	virtual const char * what() const throw() { return message.c_str(); }
	virtual ~Exception() throw() { }
};


template <bool condition, typename T = void>
class enable_if
{
	typedef T type;
};

template <typename T>
class enable_if<false, T>
{ }; // No ::type here


// AUTOGRADER


// STUDENT CODE COMPILATION FUNCTIONS
void rename_main(const string & file, const string & newname);


// MACROS
void SET_ERROR_MESSAGE(const char * message);

#define STRINGIFY1(p)   #p
#define STR(p)          STRINGIFY1(p)

namespace internal
{
template<typename StrType>
void exit_if_error_output(const char * file, int32_t line, StrType message)
{
	if (util::internal::error_prefix != NULL)
		cerr << util::internal::error_prefix;
	cerr << file << ":" << line << ": " << message;
	if (errno != 0)
		cerr << ": " << strerror(errno);
	cerr << endl;
	exit(-1);
}
}

#define EXIT_IF_ERROR2(statement_check, message)                       \
	do {                                                               \
		errno = 0;                                                     \
		if ((statement_check) || errno != 0)                                         \
			util::internal::exit_if_error_output(__FILE__, __LINE__, message); \
	} while (0)

#define EXIT_IF_ERROR1(statement_check)                                \
	EXIT_IF_ERROR2(statement_check, #statement_check)

// Crazy hack for overloading!
// Arg counting from:
// http://cplusplus.co.il/2010/07/17/variadic-macro-to-count-number-of-arguments/
// Overloading tips:
// http://stackoverflow.com/questions/3046889/optional-parameters-with-c-macros
#define EXIT_IF_ERROR_THIRD_ARG(a, b, c, ...) c

#define EXIT_IF_ERROR(...)                                    \
	EXIT_IF_ERROR_THIRD_ARG(__VA_ARGS__,                      \
	                        EXIT_IF_ERROR2,                   \
							EXIT_IF_ERROR1, 0) (__VA_ARGS__)

// Colorization
namespace colorize
{
	extern const char * BLACK;
	extern const char * GREEN;
	extern const char * RED;

	extern const bool is_color_enabled;

	inline string make_color(const char * color, const string & str)
	{
		return (is_color_enabled ? color + str + BLACK : str);
	}
} // namespace colorize


// INLINE IMPLEMENTATIONS
// Originally by radu
// http://notfaq.wordpress.com/2006/08/30/c-convert-int-to-string/
template <typename T>
inline string to_string(const T & value)
{
	stringstream ss;
	ss << value;
	return ss.str();
}

// http://stackoverflow.com/questions/5017001/like-atoi-but-to-float
template <typename T>
inline T from_string(const string & s)
{
	stringstream ss(s);
	T value;
	ss >> value;
	return value;
}

template <typename T, typename F>
inline T lexical_cast(const F & from)
{
	Initializer<T> to;
	stringstream ss;
	if (!(ss << from))
	{
		cerr << "ERROR: Could not convert types" << endl;
		return to.value;
	}
	if (!(ss >> to.value))
	{
		cerr << "ERROR: Could not convert types" << endl;
		return to.value;
	}
	return to.value; // TODO (toole1): Not sure if this forces a copy
}

inline uint32_t intlen(uint32_t a)
{
	uint32_t len = 1;
	a /= 10;

	while (a != 0)
	{
		a = a/10;
		len++;
	}
	return len;
}

inline ssize_t write(int fd, const string & str)
{
	return writen(fd, str.c_str(), str.length()+1);
}

inline ssize_t write(int fd, int val)
{
	return writen(fd, &val, sizeof val);
}

inline ssize_t write(int fd, long val)
{
	return writen(fd, &val, sizeof val);
}

inline ssize_t read(int fd, int & val)
{
	return readn(fd, &val, sizeof val);
}

inline ssize_t read(int fd, long & val)
{
	return readn(fd, &val, sizeof val);
}

inline string operator+(const string & lhs, const string & rhs)      { return std::operator+(lhs, rhs); }
inline string operator+(const string & lhs, const char * rhs)        { return std::operator+(lhs, rhs); }
inline string operator+(const string & lhs, char rhs)                { return std::operator+(lhs, rhs); }
inline string operator+(char lhs, const string & rhs)                { return std::operator+(lhs, rhs); }
inline string operator+(const char * lhs, const string & rhs)        { return std::operator+(lhs, rhs); }

template <typename T>
inline std::string & operator+=(std::string & str, const T & value)
{
	str += util::to_string(value);
	return str;
}

template <typename T>
inline std::string operator+(const std::string & str, const T & value)
{
	std::stringstream ss;
	ss << str << value;
	return ss.str();
}

inline uint64_t process_clock()
{
#ifdef CLOCK_PROCESS_CPUTIME_ID
	timespec ts;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
	return ts.tv_sec * 1000000 + (ts.tv_nsec + 500) / 1000;
#else
	return clock();
#endif
}

inline uint64_t system_clock()
{
	timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

} // namespace util

#endif // UTIL_H
