EXE = lab_inheritance
EXE_VIRTUAL = test_virtual
EXE_PURE_VIRTUAL = test_pure_virtual
EXE_DESTRUCTOR = test_destructor
EXE_SLICING = test_slicing
EXE_CONSTRUCTOR = test_constructor

OBJS_DIR = .objs

OBJS_STUDENT               = main.o              shape.o rectangle.o
OBJS_VIRTUAL_STUDENT       = test_virtual.o      shape.o rectangle.o
OBJS_PURE_VIRTUAL_STUDENT  = test_pure_virtual.o shape.o rectangle.o circle.o truck.o
OBJS_DESTRUCTOR_STUDENT    = test_destructor.o   shape.o triangle.o
OBJS_SLICING_STUDENT       = test_slicing.o      shape.o rectangle.o circle.o flower.o triangle.o
OBJS_CONSTRUCTOR_STUDENT   = test_constructor.o  shape.o circle.o
OBJS_PROVIDED              = cs225/PNG.o cs225/lodepng/lodepng.o cs225/HSLAPixel.o vector2.o line.o
OBJS_VIRTUAL_PROVIDED      = cs225/PNG.o cs225/lodepng/lodepng.o cs225/HSLAPixel.o vector2.o line.o
OBJS_PURE_VIRTUAL_PROVIDED = cs225/PNG.o cs225/lodepng/lodepng.o cs225/HSLAPixel.o vector2.o line.o
OBJS_DESTRUCTOR_PROVIDED   = cs225/PNG.o cs225/lodepng/lodepng.o cs225/HSLAPixel.o vector2.o line.o
OBJS_SLICING_PROVIDED      = cs225/PNG.o cs225/lodepng/lodepng.o cs225/HSLAPixel.o vector2.o line.o
OBJS_CONSTRUCTOR_PROVIDED  = cs225/PNG.o cs225/lodepng/lodepng.o cs225/HSLAPixel.o vector2.o line.o

CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-delete-non-virtual-dtor
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -c
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all: $(EXE) $(EXE)-asan \
	$(EXE_VIRTUAL) $(EXE_VIRTUAL)-asan \
	$(EXE_PURE_VIRTUAL) $(EXE_PURE_VIRTUAL)-asan \
	$(EXE_DESTRUCTOR) $(EXE_DESTRUCTOR)-asan \
	$(EXE_SLICING) $(EXE_SLICING)-asan \
	$(EXE_CONSTRUCTOR) $(EXE_CONSTRUCTOR)-asan

test: tests/basic.cpp $(OBJS_PROVIDED) shape.o rectangle.o triangle.o circle.o truck.o flower.o line.o vector2.o line.o vector2.o
	$(LD) $(LDFLAGS) $^ -o test

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJS_DIR)/%-asan.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir $(OBJS_DIR)/cs225
	@mkdir $(OBJS_DIR)/cs225/lodepng

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_VIRTUAL):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_PURE_VIRTUAL):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_DESTRUCTOR):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_SLICING):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_CONSTRUCTOR):
	$(LD) $^ $(LDFLAGS) -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@


# Executable dependencies
$(EXE):                   $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PROVIDED))
$(EXE)-asan:              $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PROVIDED))
$(EXE_VIRTUAL):           $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_VIRTUAL_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_VIRTUAL_PROVIDED))
$(EXE_VIRTUAL)-asan:      $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_VIRTUAL_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_VIRTUAL_PROVIDED))
$(EXE_PURE_VIRTUAL):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_PURE_VIRTUAL_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PURE_VIRTUAL_PROVIDED))
$(EXE_PURE_VIRTUAL)-asan: $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_PURE_VIRTUAL_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PURE_VIRTUAL_PROVIDED))
$(EXE_DESTRUCTOR):        $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_DESTRUCTOR_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_DESTRUCTOR_PROVIDED))
$(EXE_DESTRUCTOR)-asan:   $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_DESTRUCTOR_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_DESTRUCTOR_PROVIDED))
$(EXE_SLICING):           $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_SLICING_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_SLICING_PROVIDED))
$(EXE_SLICING)-asan:      $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_SLICING_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_SLICING_PROVIDED))
$(EXE_CONSTRUCTOR):       $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_CONSTRUCTOR_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_CONSTRUCTOR_PROVIDED))
$(EXE_CONSTRUCTOR)-asan:  $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_CONSTRUCTOR_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_CONSTRUCTOR_PROVIDED))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d
-include *.d

clean:
	rm -rf $(EXE) $(EXE)-asan \
		$(EXE_VIRTUAL) $(EXE_VIRTUAL)-asan \
		$(EXE_PURE_VIRTUAL) $(EXE_PURE_VIRTUAL)-asan  \
		$(EXE_DESTRUCTOR) $(EXE_DESTRUCTOR)-asan  \
		$(EXE_SLICING) $(EXE_SLICING)-asan  \
		$(EXE_CONSTRUCTOR) $(EXE_CONSTRUCTOR)-asan  \
		$(OBJS_DIR) \
		*.d *.o \
		cs225/*.d cs225/*.o \
		cs225/lodepng/*.d cs225/lodepng/*.o \
		test

tidy: clean
	rm -rf doc out.png test_constructor.png test_destructor.png test_pure_virtual.png test_slicing.png test_virtual.png

.PHONY: all tidy clean
