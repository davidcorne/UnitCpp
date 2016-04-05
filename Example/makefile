#==============================================================================
# Not good practice to have a makefile with manually written dependencies, but
# this is just an example of testing, so I think it's ok.

COMPILER_TYPE := gcc

include ../MakeBase/common.mk

.DEFAULT_GOAL := exe.$(COMPILER_TYPE)/utest.exe

#==============================================================================
$(.DEFAULT_GOAL): $(OBJECTS)
	@mkdir -p exe.$(COMPILER_TYPE)
	$(COMPILER) $(COMPILER_ARGS) $^ $(OUT_EXE_FILE)$@

#==============================================================================
test: exe.$(COMPILER_TYPE)/utest.exe
	./$< 0

