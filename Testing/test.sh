#!/bin/sh
# Written by: DGC

set -e

#==============================================================================
if $(command -v clang >/dev/null 2>&1)
then
  echo "Has clang."
  # doesn't work under clang yet.
fi

#==============================================================================
if $(command -v cl >/dev/null 2>&1)
then
  echo "Has cl."
  make test COMPILER_TYPE=vs
fi

#==============================================================================
if $(command -v g++ >/dev/null 2>&1)
then
  echo "Has g++."
  make test COMPILER_TYPE=gcc
fi
