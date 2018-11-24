# Add standard CS 225 object files
OBJS += cs225/HSLAPixel.o cs225/PNG.o cs225/lodepng/lodepng.o

# Use ./.objs to store all .o file (keeping the directory clean)
OBJS_DIR = .objs

# Use all .cpp files in /tests/
OBJS_TEST = $(filter-out $(EXE_OBJ), $(OBJS))
CPP_TEST = $(wildcard tests/*.cpp)
CPP_TEST += cs225/catch/catchmain.cpp
OBJS_TEST += $(CPP_TEST:.cpp=.o)

# Config
CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -msse2 -c
LDFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -lpthread
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

#  Rules for first executable
$(EXE):
	$(LD) $^ $(LDFLAGS) -o $@

# Rule for `all`
all: $(EXE) $(TEST)

# Pattern rules for object files
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/cs225
	@mkdir -p $(OBJS_DIR)/cs225/catch
	@mkdir -p $(OBJS_DIR)/cs225/lodepng
	@mkdir -p $(OBJS_DIR)/tests

$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Rules for executables
$(TEST):
	$(LD) $^ $(LDFLAGS) -o $@

# Executable dependencies
$(EXE):  $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
$(TEST): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_TEST))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d
-include $(OBJS_DIR)/cs225/*.d
-include $(OBJS_DIR)/cs225/catch/*.d
-include $(OBJS_DIR)/cs225/lodepng/*.d
-include $(OBJS_DIR)/tests/*.d

clean:
	rm -rf $(EXE) $(TEST) $(OBJS_DIR) $(CLEAN_RM)

tidy: clean
	rm -rf doc

.PHONY: all $(EXE) $(TEST) tidy clean
