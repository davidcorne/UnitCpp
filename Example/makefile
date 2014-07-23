#==============================================================================
# Not good practice to have a makefile with manually written dependencies, but
# this is just an example of testing, so I think it's ok.


CC = g++
CC_ARGS = -I.. -std=c++0x -Wall -Werror

#==============================================================================
exe/utest.exe: TestHarness.cpp obj/utest_Maths.obj
	@mkdir -p exe
	$(CC) $(CC_ARGS) $^ -o $@

#==============================================================================
obj/utest_Maths.obj: utest_Maths.cpp Maths.h
	@mkdir -p obj
	$(CC) $(CC_ARGS) -c $< -o $@

#==============================================================================
test: exe/utest.exe
	./$<
