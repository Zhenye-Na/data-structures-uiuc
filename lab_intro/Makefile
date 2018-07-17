EXENAME = lab_intro
OBJS = main.o PNG.o HSLAPixel.o lodepng.o lab_intro.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpthread -lm
#-lc++abi

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp lab_intro.h cs225/PNG.h cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) main.cpp 

lab_intro.o : lab_intro.cpp lab_intro.h
	$(CXX) $(CXXFLAGS) lab_intro.cpp
	
PNG.o : cs225/PNG.cpp cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/PNG.cpp

HSLAPixel.o : cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs225/HSLAPixel.cpp

lodepng.o : cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/lodepng/lodepng.cpp


test: catchmain.o part1.o part2.o PNG.o HSLAPixel.o lodepng.o lab_intro.o
	$(LD) catchmain.o part1.o part2.o PNG.o HSLAPixel.o lodepng.o lab_intro.o $(LDFLAGS) -o test

catchmain.o : tests/catchmain.cpp tests/catch.hpp
	$(CXX) $(CXXFLAGS) tests/catchmain.cpp

part1.o : tests/part1.cpp tests/catch.hpp lab_intro.cpp lab_intro.h
	$(CXX) $(CXXFLAGS) tests/part1.cpp

part2.o : tests/part2.cpp tests/catch.hpp lab_intro.cpp lab_intro.h
	$(CXX) $(CXXFLAGS) tests/part2.cpp


clean :
	-rm -f *.o $(EXENAME) test
