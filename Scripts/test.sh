#!/bin/sh
# Written by: DGC

set -e

#==============================================================================
usage() {
  cat <<EOF
Usage: $(basename $0) <options> arguments

Tests all of UnitC++. This builds the examples, and builds and runs the tests.

Options:
-h                 Display this message.
EOF
  exit
}

#==============================================================================
# Main
while getopts ":h?" option
do
  case $option in
    h)
      usage
      ;;
    \?)
      echo -e "Invalid option: -$OPTARG \n"
      usage
      ;;
  esac
done

#==============================================================================
test_with_compiler() 
{
  compiler_type=$1
  make -C Example COMPILER_TYPE=$compiler_type test
  make -C Testing COMPILER_TYPE=$compiler_type test
  
}

tested_compilers=""

#==============================================================================
if $(command -v clang >/dev/null 2>&1)
then
  echo "Has clang."
  test_with_compiler clang
  tested_compilers="$tested_compilers clang"
fi

#==============================================================================
if $(command -v cl >/dev/null 2>&1)
then
  echo "Has cl."
  test_with_compiler vs
  tested_compilers="$tested_compilers cl"
fi

#==============================================================================
if $(command -v g++ >/dev/null 2>&1)
then
  echo "Has g++."
  test_with_compiler gcc
  tested_compilers="$tested_compilers g++"
fi

echo "Tests and Examples run using:$tested_compilers"
