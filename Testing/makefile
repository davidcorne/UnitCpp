#==============================================================================
# This is so I can test it with the visual studio compiler, g++ and clang.

.DEFAULT_GOAL = exe.$(COMPILER_TYPE)/utest.exe

COMPILER_TYPE = gcc

include ../MakeBase/common.mk

#==============================================================================
$(.DEFAULT_GOAL): $(OBJECTS)
	@mkdir -p exe.$(COMPILER_TYPE)
	$(COMPILER) $(COMPILER_ARGS) $^ $(OUT_EXE_FILE)$@

#==============================================================================
test: $(.DEFAULT_GOAL)
	./$< 0

#==============================================================================
clean:
	@rm -rf exe* obj*
