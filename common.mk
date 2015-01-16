#==============================================================================
# This is a makefile for common defines and rules.

UNITCPP_ROOT := $(dir $(lastword $(MAKEFILE_LIST)))

#==============================================================================
# Variables and rules for making UnitCpp.h

UNITCPP_FILES := $(shell find $(UNITCPP_ROOT)/UnitCpp -type f)
UNITCPP_FILE := $(UNITCPP_ROOT)/UnitCpp.h

#==============================================================================
$(UNITCPP_FILE): $(UNITCPP_FILES)
	@echo "create_single_header.py > $@"
	@$(UNITCPP_ROOT)/Scripts/create_single_header.py > $@

#==============================================================================
# Variables for different compilers, and making objects.

ifdef COMPILER_TYPE

  #============================================================================
  ifeq ($(COMPILER_TYPE), gcc)
    COMPILER = g++
    COMPILER_ARGS = -I.. -I. -std=c++0x -Wall -Werror
    OUT_OBJECT_FILE = -o
    OUT_EXE_FILE = -o
    NO_LINK = -c
  endif

  #============================================================================
  ifeq ($(COMPILER_TYPE), clang)
    COMPILER = clang++
    COMPILER_ARGS = -I.. -I. -std=c++11 -Wall -Werror
    OUT_OBJECT_FILE = -o
    OUT_EXE_FILE = -o
    NO_LINK = -c
  endif

  #============================================================================
  ifeq ($(COMPILER_TYPE), vs)
    COMPILER = cl
    COMPILER_ARGS = /nologo /I.. /I. /W4 /wd4481 /WX /EHsc
    OUT_OBJECT_FILE = /Fo
    OUT_EXE_FILE = /Fe
    NO_LINK = /c
  endif

  ifndef COMPILER
    $(error Unknown compiler type $(COMPILER_TYPE))
  endif

  # Common variable for finding objects
  OBJECTS := $(shell \
               find source -name "*.cpp" | \
               sed -e 's:^source/:obj.$(COMPILER_TYPE)/:' -e 's:\.cpp$$:.obj:'\
             )

#==============================================================================
obj.$(COMPILER_TYPE)/%.obj: source/%.cpp $(UNITCPP_FILE)
	@mkdir -p obj.$(COMPILER_TYPE)
	$(COMPILER) $(COMPILER_ARGS) $(NO_LINK) $< $(OUT_OBJECT_FILE)$@


endif
