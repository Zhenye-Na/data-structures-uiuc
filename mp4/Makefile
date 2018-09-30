EXE = mp4

OBJS_DIR = .objs

CPP_FILES += main.cpp Point.cpp FloodFilledImage.cpp Animation.cpp
CPP_FILES += $(wildcard colorPicker/*.cpp)
CPP_FILES += $(wildcard imageTraversal/*.cpp)
CPP_FILES += $(wildcard cs225/*.cpp)
CPP_FILES += $(wildcard cs225/lodepng/*.cpp)
OBJS += $(CPP_FILES:.cpp=.o)

CPP_TESTS += $(filter-out main.cpp, $(CPP_FILES))
CPP_TESTS += $(wildcard tests/*.cpp)
OBJS_TEST = $(CPP_TESTS:.cpp=.o)

CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -c
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

$(EXE): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXE)

test: $(OBJS_TEST)
	$(LD) $(OBJS_TEST) $(LDFLAGS) -o test

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@

all: $(EXE) test

clean:
	rm -rf $(EXE) $(EXE)-asan test *.o tests/*.o cs225/*.o cs225/lodepng/*.o colorPicker/*.o imageTraversal/*.o

.PHONY: all $(EXE) test clean
