CXX = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -c $(CS225)
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

OBJS_DIR = .objs

CC_EXE = charcount
CC_OBJS = hashes.o textfile.o charcount.o

WC_EXE = wordcount
WC_OBJS = hashes.o textfile.o wordcount.o

ANAGRAM_EXE = anagramtest
ANAGRAM_OBJS = hashes.o textfile.o anagramtest.o

GENLOG_EXE = genlog
GENLOG_OBJS = logfile_generator.o

LFPARSE_EXE = lfparse
LFPARSE_OBJS = logfile_parser.o lfparse.o hashes.o

TEST_OBJS = hashes.o textfile.o

all: nonasan asan
nonasan: $(CC_EXE) $(WC_EXE) $(ANAGRAM_EXE) $(GENLOG_EXE) $(LFPARSE_EXE)
asan: $(CC_EXE)-asan $(WC_EXE)-asan $(ANAGRAM_EXE)-asan $(LFPARSE_EXE)-asan

data:
	wget https://courses.engr.illinois.edu/cs225/sp2018/labs/hash/lab_hash_data.tar && tar -xf lab_hash_data.tar && rm lab_hash_data.tar

test: tests/basic.o 
	$(LD) $(LDFLAGS) $^ -o ./test

basic.o: tests/basic.cpp
	$(CXX) $(CXXFLAGS) tests/basic.cpp

# Pattern rules for object files
$(OBJS_DIR)/%-asan.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $@
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@


# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)


# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(CC_EXE):
	$(LD) $^ $(LDFLAGS) -o $@
$(WC_EXE):
	$(LD) $^ $(LDFLAGS) -o $@
$(ANAGRAM_EXE):
	$(LD) $^ $(LDFLAGS) -o $@
$(GENLOG_EXE):
	$(LD) $^ $(LDFLAGS) -o $@
$(LFPARSE_EXE):
	$(LD) $^ $(LDFLAGS) -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@


# Executable dependencies
$(CC_EXE):           $(patsubst %.o, $(OBJS_DIR)/%.o,      $(CC_OBJS))
$(CC_EXE)-asan:      $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(CC_OBJS))
$(WC_EXE):           $(patsubst %.o, $(OBJS_DIR)/%.o,      $(WC_OBJS))
$(WC_EXE)-asan:      $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(WC_OBJS))
$(ANAGRAM_EXE):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(ANAGRAM_OBJS))
$(ANAGRAM_EXE)-asan: $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(ANAGRAM_OBJS))
$(GENLOG_EXE):       $(patsubst %.o, $(OBJS_DIR)/%.o,      $(GENLOG_OBJS))
$(GENLOG_EXE)-asan:  $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(GENLOG_OBJS))
$(LFPARSE_EXE):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(LFPARSE_OBJS))
$(LFPARSE_EXE)-asan: $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(LFPARSE_OBJS))
test:      			 $(patsubst %.o, $(OBJS_DIR)/%.o,      $(TEST_OBJS))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d
-include tests/*.d


doc: $(wildcard *.h) $(wildcard *.cpp)
	-doxygen lab_hash.doxygen

clean:
	-rm -rf doc *.o $(CC_EXE) $(CC_EXE)-asan $(WC_EXE) $(WC_EXE)-asan $(ANAGRAM_EXE) $(ANAGRAM_EXE)-asan $(GENLOG_EXE) $(LFPARSE_EXE) $(LFPARSE_EXE)-asan $(OBJS_DIR) tests/*.d tests/*.o test

tidy:
	-rm -f anagrams.txt

.PHONY: all doc clean tidy nonasan asan
