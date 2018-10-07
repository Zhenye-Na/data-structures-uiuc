#include "coloredout.h"

using namespace std;

const char colored_out::BORDER_CHAR = '~';

const bool colored_out::was_originally_tty = isatty(STDOUT_FILENO);

bool colored_out::check_opcode(char c)
{
	// Check for special color codes (i.e. bold)
	if (c == '\033')
	{
		int error = 1;
		ostringstream opcode;
		while (c != 'm' && c != '\0' && error > 0)
		{
			opcode << c;
			error = readn(fds[READ_END], &c, sizeof c);
		}
		opcode << 'm';
		cout << opcode.str();
		return true;
	}
	return false;
}


char colored_out::get_next_char()
{
	char c;
	int error = readn(fds[READ_END], &c, sizeof c);
	if (error <= 0 || c == '\0') return '\0';
	while (check_opcode(c))
	{
		error = readn(fds[READ_END], &c, sizeof c);
		if (error <= 0 || c == '\0') return '\0';
	}
	return c;
}


int colored_out::start()
{
	if (isatty(STDOUT_FILENO) == 0)
		return 0;

	pipe(fds);

	pid_t pid = fork();

	if (pid != 0)
	{
		sendnullchar = true;
		::close(STDOUT_FILENO);
		dup2(fds[WRITE_END], STDOUT_FILENO);
		return 0;
	}
	else
	{

//		cout << "***********************************" << endl;
//		cout << expected << endl;
//		cout << "***********************************" << endl;

		size_t i = 0;
		int error = 1;
		char c = '\0';
		char e = '\0';

		do
		{

			c = get_next_char();
			if (c == '\0') break;

			e = expected[i++];

			// Align on BORDER_CHAR (~)
			const char aligns[] = { BORDER_CHAR, '\n' };
			const size_t aligns_size = (sizeof aligns) / (sizeof aligns[0]);
			for (size_t align_i = 0; align_i < aligns_size; align_i++)
			{
				const char align = aligns[align_i];
				while (c != e && (c == align || e == align))
				{
					// Bring expected up to date with actual
					if (c == align && e != c && i < expected.size())
					{
						if (e == '\n' || e == ' ')
							cout << e;
						else
							output_notfound(e);

						e = expected[i++];
					}
					else if (c == '\0') break;

					// Wait for actual to catch up to expected
					if (e == align && c != e && c != '\0')
					{
						output_red(c);
						c = get_next_char();
					}
					else if (i >= expected.size()) break;
				}
			}


			// end if we're done with input
			if (c == '\0') break;

			if (isdigit(e) || e == '/' || e == '\\' || e == '_' || e == '-')
			{
				if (c == e)
					output_green(c);
				else
					output_red(c);
			}
			else
			{
				if (c == e)
					cout << c;
				else
					output_red(c);
			}
		}
		while (c != '\0' && error > 0 && i < expected.size());

		while (c != '\0' && error > 0)
		{
			output_red(c);
			c = get_next_char();
		}

		while (i < expected.size())
		{
			e = expected[i++];
			
			if (e == '\n')
				cout << e;
			else
				output_notfound(e);
		}
		
		close(fds[READ_END]);
		return -1;
	}
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

