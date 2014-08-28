#!/bin/sh
# Written by: DGC

set -e

#==============================================================================
# setup globals
BASE_DIR=$(realpath $(dirname $0))

#==============================================================================
usage() {
  cat <<EOF
Usage: $(basename $0) <options> arguments

Builds a release of UnitC++.

Options:
-h                 Display this message.
EOF
  exit
}

#==============================================================================
cleanup() {
  rm -rf $BASE_DIR/build
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

trap cleanup EXIT

hg archive build/unitcpp
cd build
rm unitcpp/.hg*
zip -r unitcpp.zip unitcpp
rsync -avP -e ssh unitcpp.zip davidcorne1@frs.sourceforge.net:/home/frs/project/unitcpp/unitcpp$(cat ../Version.txt)/

