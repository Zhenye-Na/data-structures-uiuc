CXX = clang++
LD = clang++
CXXFLAGS = -c -g -std=c++1y -stdlib=libc++ -Wall -Wextra -pedantic -MP -MMD $(CS225)
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

DEMO = graphdemo
DEMO_OBJS = graph.o demo.o

LAB = lab_graphs
LAB_OBJS = tests.o graph.o graph_tools.o dsets.o

OBJS_TEST = tests/basic.o graph.o graph_tools.o dsets.o

OBJS_DIR = .objs

all: nonasan asan
nonasan: $(DEMO) $(LAB) 
asan: $(DEMO)-asan $(LAB)-asan

# Pattern rules for object files
$(OBJS_DIR)/%-asan.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $@
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@


# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)


# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(DEMO):
	$(LD) $^ $(LDFLAGS) -o $@
$(LAB):
	$(LD) $^ $(LDFLAGS) -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@

# Executable dependencies
$(DEMO):          $(patsubst %.o, $(OBJS_DIR)/%.o,      $(DEMO_OBJS))
$(DEMO)-asan:     $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(DEMO_OBJS))
$(LAB):           $(patsubst %.o, $(OBJS_DIR)/%.o,      $(LAB_OBJS))
$(LAB)-asan:      $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(LAB_OBJS))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d
-include tests/*.d

test: $(OBJS_TEST)
	$(LD) $(OBJS_TEST) $(LDFLAGS) -o test

doc: lab_heaps.doxygen $(wildcard *.h) $(wildcard *.cpp)
	-doxygen lab_heaps.doxygen

clean:
	-rm -rf doc *.o *.d $(DEMO) $(DEMO)-asan $(LAB) $(LAB)-asan $(OBJS_DIR) test tests/*.d tests/*.o 

tidy:
	-rm -f images/*.png
	-rm -rf doc

.PHONY: all doc clean tidy nonasan asan

