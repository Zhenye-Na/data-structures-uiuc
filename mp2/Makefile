# Executable names:
EXE = mp2
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = Image.o StickerSheet.o

# Generated files
CLEAN_RM = out.png

# Use the cs225 makefile template:
include cs225/make/cs225.mk

# MP2-specific target
TMP_OBJ := $(OBJS)
OBJS = $(filter-out $(EXE_OBJ), $(TMP_OBJ))
OBJS += mp2-1.o

mp2-1: $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(LD) $^ $(LDFLAGS) -o $@
