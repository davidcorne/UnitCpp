#==============================================================================
# This is so I can test it with visual studio and g++.

COMPILER_TYPE = gcc

TARGET = exe.$(COMPILER_TYPE)/utest.exe

#==============================================================================
ifeq ($(COMPILER_TYPE), gcc)
  COMPILER = g++
  COMPILER_ARGS = -I.. -std=c++0x -Wall -Werror
  OUT_OBJECT_FILE = -o
  OUT_EXE_FILE = -o
  NO_LINK = -c
endif

#==============================================================================
ifeq ($(COMPILER_TYPE), clang)
  COMPILER = clang++
  COMPILER_ARGS = -I.. -Wall -Werror
  OUT_OBJECT_FILE = -o
  OUT_EXE_FILE = -o
  NO_LINK = -c
endif

#==============================================================================
ifeq ($(COMPILER_TYPE), vs)
  COMPILER = cl
  COMPILER_ARGS = /I.. /W3 /WX /EHsc
  OUT_OBJECT_FILE = /Fo
  OUT_EXE_FILE = /Fe
  NO_LINK = /c
endif

ifndef COMPILER
$(error Unknown compiler type $(COMPILER_TYPE))
endif

OBJECTS = $(shell find source -name "*.cpp" | sed -e 's:^source/:obj.$(COMPILER_TYPE)/:' -e 's:\.cpp$$:.obj:')

#==============================================================================
$(TARGET): $(OBJECTS)
	@mkdir -p exe.$(COMPILER_TYPE)
	$(COMPILER) $(COMPILER_ARGS) $^ $(OUT_EXE_FILE)$@

#==============================================================================
obj.$(COMPILER_TYPE)/%.obj: source/%.cpp
	@mkdir -p obj.$(COMPILER_TYPE)
	$(COMPILER) $(COMPILER_ARGS) $(NO_LINK) $< $(OUT_OBJECT_FILE)$@

#==============================================================================
test: $(TARGET)
	./$<

#==============================================================================
clean:
	@rm -rf exe* obj*
