#ifndef COLOREDOUT_H
#define COLOREDOUT_H

#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

class colored_out
{
	public:
	enum enable_t
	{
		DISABLE,
		ENABLE,
		TTY,
		COUT
	};
	
	static const char BORDER_CHAR;

	protected:

	static const bool was_originally_tty;

	static bool is_enabled(const std::ostream & out, enable_t e)
	{
		// http://stackoverflow.com/questions/3318714/check-if-ostream-object-is-cout-or-ofstream-c
		return (e == ENABLE) ||
		       (e == TTY && was_originally_tty) ||
			   (e == COUT && was_originally_tty && out.rdbuf() == std::cout.rdbuf());
	}

	protected:
	int fds[2];
	static const int READ_END  = 0;
	static const int WRITE_END = 1;
	std::string expected;
	bool sendnullchar;

	char get_next_char();
	bool check_opcode(char c);

	public:
	colored_out()
		: sendnullchar(false) { }

	~colored_out()
	{
		if (sendnullchar)
		{
			std::cout << '\0';
			std::cout.flush();
			fflush(stdout);
			close(fds[WRITE_END]);
			int st;
			wait(&st);
		}
	}

	int set_expected_file(const std::string & str)
	{
		std::ifstream file;
		file.open(str.c_str());
		std::stringstream ss;
		if (file.good())
			while (file.good())
			{
				char c;
				file.get(c);
				ss << c;
			}

		file.close();
		expected = ss.str();
		return 0;
	}
	int set_expected(const std::string & str)
	{
		expected = str;
		return 0;
	}

	template <typename T>
	static void output_red(T c)
	{
		std::cout << "\033[31m" << c << "\033[39m";
	}

	template <typename T>
	static void output_green(T c)
	{
		std::cout << "\033[32m" << c << "\033[39m";
	}

	template <typename T>
	static void output_notfound(T c)
	{
		std::cout << "\033[31;4m" << c << "\033[39;24m";
	}
	
	template <typename T>
	static void output_bold(T c, std::ostream & out = std::cout, enable_t enable = COUT)
	{
		if (is_enabled(out, enable))
			out << "\033[1m" << c << "\033[22m";
		else
			out << c;
	}

	static void output_bold_digits(std::string str, std::ostream & out = std::cout, enable_t enable = COUT)
	{
		if (!is_enabled(out, enable))
		{
			out << str;
			return;
		}
		
		for (size_t i = 0; i < str.length(); i++)
		{
			if (isdigit(str[i]) || str[i] == '-')
				out << "\033[1m" << str[i] << "\033[22m";
			else
				out << str[i];
		}
	}

	int start();
};

ssize_t readn(int fd, void *vptr, size_t n);

#endif
