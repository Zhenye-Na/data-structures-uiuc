EXE = test_btree
TEST = test

EXE_OBJ = test_btree.cpp
# templated so header-only
OBJS = test_btree.cpp

OBJDIR_COPY = .objs/

# our extra stuff
RACER_EXE = dict_racer
RACER_OBJS = $(OBJDIR_COPY)dict_racer.o

# what extra stuff we want to delete
CLEAN_RM = $(RACER_EXE)

# include standard makefile
include cs225/make/cs225.mk

$(RACER_EXE): $(RACER_OBJS)
	$(LD) $^ $(LDFLAGS) -o $@
