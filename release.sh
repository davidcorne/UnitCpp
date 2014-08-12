#!/bin/sh
# Written by: DGC

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

hg archive build/unitcpp
cd build
rm unitcpp/.hg*
zip -r unitcpp.zip unitcpp
cd ..
mv build/unitcpp.zip .
rm -r build
rsync.exe -avP -e ssh unitcpp.zip davidcorne1@frs.sourceforge.net:/home/frs/project/unitcpp/unitcpp$(cat Version.txt)/
rm unitcpp.zip
