#==============================================================================
# Not good practice to have a makefile with manually written dependencies, but
# this is just an example of testing, so I think it's ok.


CC = g++
CC_ARGS = -I.. -std=c++0x -Wall -Werror

UNITCPP_FILES = $(shell find ../UnitCpp -type f)

#==============================================================================
exe/utest.exe: TestHarness.cpp obj/utest_Maths.obj obj/utest_MyString.obj
	@mkdir -p exe
	$(CC) $(CC_ARGS) $^ -o $@

#==============================================================================
obj/utest_Maths.obj: utest_Maths.cpp Maths.h $(UNITCPP_FILES)
	@mkdir -p obj
	$(CC) $(CC_ARGS) -c $< -o $@

#==============================================================================
obj/utest_MyString.obj: utest_MyString.cpp MyString.h $(UNITCPP_FILES)
	@mkdir -p obj
	$(CC) $(CC_ARGS) -c $< -o $@

#==============================================================================
test: exe/utest.exe
	./$< 0
