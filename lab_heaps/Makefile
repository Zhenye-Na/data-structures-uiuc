CXX = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -c $(CS225)
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread $(CS225)
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

OBJS_DIR = .objs

EXE = testheap
OBJS = testheap.o coloredout.o
OBJS_TEST = tests/basic.o

all: nonasan asan
nonasan: $(EXE)
asan: $(EXE)-asan

# Pattern rules for object files
$(OBJS_DIR)/%-asan.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $@
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@


# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)


# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE):
	$(LD) $^ $(LDFLAGS) -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@

# Executable dependencies
$(EXE):           $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS))
$(EXE)-asan:      $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d
-include tests/*.d

test: $(OBJS_TEST)
	$(LD) $(OBJS_TEST) $(LDFLAGS) -o test

doc: lab_heaps.doxygen $(wildcard *.h) $(wildcard *.cpp)
	-doxygen lab_heaps.doxygen

clean:
	-rm -rf doc *.o $(EXE) $(EXE)-asan $(OBJS_DIR) test tests/*.o tests/*.d

.PHONY: all doc clean nonasan asan
