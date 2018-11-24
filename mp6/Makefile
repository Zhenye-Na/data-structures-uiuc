# Executable names:
EXE = mp6
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o skipList_given.o skipNode.o

# Generated files
CLEAN_RM = out-degenerate.png out-structure.png list swap switch recurse list playground loop test

# Use the cs225 makefile template:
include cs225/make/cs225.mk


# == MP6 specific targets ==
EXAMPLEFLAGS = $(WARNINGS) -std=c++1y -stdlib=libc++ -g -O0

loop: gdb-examples/loop.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/loop.cpp -o loop

list: gdb-examples/list.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/list.cpp -o list

playground: gdb-examples/playground.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/playground.cpp -o playground
	
recurse: gdb-examples/recurse.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/recurse.cpp -o recurse

swap: gdb-examples/swap.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/swap.cpp -o swap

switch: gdb-examples/switch.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/switch.cpp -o switch
