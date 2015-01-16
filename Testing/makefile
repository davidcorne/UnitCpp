#==============================================================================
# This is so I can test it with the visual studio compiler, g++ and clang.

.DEFAULT_GOAL = exe.$(COMPILER_TYPE)/utest.exe

COMPILER_TYPE = gcc

include ../common.mk

OBJECTS = $(shell find source -name "*.cpp" | sed -e 's:^source/:obj.$(COMPILER_TYPE)/:' -e 's:\.cpp$$:.obj:')

#==============================================================================
$(.DEFAULT_GOAL): $(OBJECTS)
	@mkdir -p exe.$(COMPILER_TYPE)
	$(COMPILER) $(COMPILER_ARGS) $^ $(OUT_EXE_FILE)$@

#==============================================================================
obj.$(COMPILER_TYPE)/%.obj: source/%.cpp $(UNITCPP_FILE)
	@mkdir -p obj.$(COMPILER_TYPE)
	$(COMPILER) $(COMPILER_ARGS) $(NO_LINK) $< $(OUT_OBJECT_FILE)$@

#==============================================================================
test: $(.DEFAULT_GOAL)
	./$< 0

#==============================================================================
clean:
	@rm -rf exe* obj*
