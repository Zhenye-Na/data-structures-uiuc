EXE_DECODER = decoder
EXE_ENCODER = encoder
EXE_PRINTER = print_as_ascii
EXE_TEST = test

OBJS_DIR = .objs

OBJS_ENCODER = huffman_tree.o frequency.o encoder.o encoder_prog.o binary_file_writer.o binary_file_reader.o
OBJS_DECODER = huffman_tree.o frequency.o decoder.o decoder_prog.o binary_file_writer.o binary_file_reader.o
OBJS_PRINTER = binary_file_reader.o print_as_ascii.o
OBJS_TEST = frequency.o encoder.o decoder.o binary_file_writer.o binary_file_reader.o huffman_tree.o

CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -c $(CS225)
LDFLAGS = -std=c++1y -stdlib=libc++ 
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all: $(EXE_ENCODER) $(EXE_ENCODER)-asan \
	$(EXE_DECODER) $(EXE_DECODER)-asan \
	$(EXE_PRINTER) $(EXE_PRINTER)-asan

data:
	wget https://courses.engr.illinois.edu/cs225/sp2018/labs/huffman/lab_huffman_data.tar && tar -xf lab_huffman_data.tar && rm lab_huffman_data.tar

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJS_DIR)/%-asan.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE_DECODER):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_ENCODER):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_PRINTER):
	$(LD) $^ $(LDFLAGS) -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@
$(EXE_TEST): tests/basic.cpp
	$(LD) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_TEST)) tests/basic.cpp $(LDFLAGS) -o $@


# Executable dependencies
$(EXE_DECODER):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_DECODER))
$(EXE_DECODER)-asan: $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_DECODER))
$(EXE_ENCODER):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_ENCODER))
$(EXE_ENCODER)-asan: $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_ENCODER))
$(EXE_PRINTER):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_PRINTER))
$(EXE_PRINTER)-asan: $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_PRINTER))
$(EXE_TEST):         $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_TEST))
# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	rm -rf $(EXE_ENCODER) $(EXE_ENCODER)-asan \
		$(EXE_DECODER) $(EXE_DECODER)-asan \
		$(EXE_PRINTER) $(EXE_PRINTER)-asan \
		$(EXE_TEST) \
		$(OBJS_DIR)

tidy: clean
	rm -rf doc *.bin *.txt *.huff \
		tests/out.txt tests/test.bin tests/text.txt tests/tree.huff

.PHONY: all tidy clean
