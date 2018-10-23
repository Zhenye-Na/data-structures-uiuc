# This defines our compiler and linker, as we've seen before.
CXX = clang++
LD = clang++

# These are the options we pass to the compiler.
# -std=c++1y means we want to use the C++14 standard (called 1y in this version of Clang).
# -stdlib=libc++ specifies that we want to use the standard library implementation called libc++
# -c specifies making an object file, as you saw before
# -g specifies that we want to include "debugging symbols" which allows us to use a debugging program.
# -O0 specifies to do no optimizations on our code.
# -Wall, -Wextra, and -pedantic tells the compiler to look out for common problems with our code. -Werror makes it so that these warnings stop compilation.
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic

# These are the options we pass to the linker.
# The first two are the same as the compiler flags.
# -l<something> tells the linker to go look in the system for pre-installed object files to link with.
# Here we want to link with the object files from libpng (since we use it in our code) and libc++. Remember libc++ is the standard library implementation.
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread
