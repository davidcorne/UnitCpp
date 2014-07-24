#!/bin/sh
# Written by: DGC

set -e

tested_compilers=""
#==============================================================================
if $(command -v clang >/dev/null 2>&1)
then
  echo "Has clang."
  make test COMPILER_TYPE=clang
  tested_compilers="$tested_compilers clang"
fi

#==============================================================================
if $(command -v cl >/dev/null 2>&1)
then
  echo "Has cl."
  make test COMPILER_TYPE=vs
  tested_compilers="$tested_compilers cl"
fi

#==============================================================================
if $(command -v g++ >/dev/null 2>&1)
then
  echo "Has g++."
  make test COMPILER_TYPE=gcc
  tested_compilers="$tested_compilers g++"
fi

echo "Tested using:$tested_compilers"
