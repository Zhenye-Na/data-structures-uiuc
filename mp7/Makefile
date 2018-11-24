# Executable names:
EXE = mp7
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o dsets.o maze.o

# Generated files
CLEAN_RM = unsolved.png solved.png testdsets testsquaremaze \
						*.o *.d tests/*.o tests/*.d cs225/*.d cs225/*.o \
						cs225/lodepng/*.o cs225/lodepng/*.d \
						cs225/catch/*.o cs225/catch/*.d

# Use the cs225 makefile template:
include cs225/make/cs225.mk


# == MP7 specific targets ==
DSETS_OBJS = testdsets.o
DSETS_OBJS += dsets.o

testdsets: $(DSETS_OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

MAZE_OBJS = $(filter-out $(EXE_OBJ), $(OBJS))
MAZE_OBJS += testsquaremaze.o

testsquaremaze: $(MAZE_OBJS)
	$(LD) $^ $(LDFLAGS) -o $@
