EXE = allocate

OBJS_DIR = .objs

OBJS_STUDENT = letter.o room.o allocator.o
OBJS_PROVIDED = main.o fileio.o

CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -c $(CS225)
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread $(CS225)
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

#CPP_TESTS += letter.cpp room.cpp allocator.cpp fileio.cpp
CPP_TESTS += $(wildcard tests/*.cpp)
OBJS_TEST = $(CPP_TESTS:.cpp=.o) $(OBJS_DIR)/letter.o $(OBJS_DIR)/room.o $(OBJS_DIR)/allocator.o $(OBJS_DIR)/fileio.o




all: $(EXE) $(EXE)-asan

test: $(OBJS_TEST)
	$(LD) $(OBJS_TEST) $(LDFLAGS) -o test

tests/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJS_DIR)/%-asan.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE):
	$(LD) $^ $(LDFLAGS) -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@


# Executable dependencies
$(EXE):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PROVIDED))
$(EXE)-asan: $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PROVIDED))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d
-include tests/*d

clean:
	rm -rf $(EXE) $(EXE)-asan $(OBJS_DIR) tests/*.d tests/*.o test

tidy: clean
	rm -rf doc

.PHONY: all tidy clean
