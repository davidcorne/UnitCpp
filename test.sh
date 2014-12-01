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

make -C Example
chmod +x Example/exe/utest.exe
Example/exe/utest.exe 0
cd Testing
chmod +x test.sh
./test.sh


