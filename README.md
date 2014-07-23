# UnitC++ #

This is a modern, light weight, header-only c++ library for unit testing. The intention of UnitC++ is to make it really easy to test c++ code in a portable way.

## How to use UnitC++ ##

### Get the repository ###
Clone this repository onto local disk.

    cd ~
    hg clone https://davidcorne@bitbucket.org/davidcorne/unitcpp

### Build against UnitC++ ###

While how you do this will vary depending on your build process, it will be straightforward. As this is a header-only library all you need to do is add the repository path to the compiler include line.

- Compiling from the command line you add `-I $(path_to_unitc++)`. This works for g++/clang/cl from the command line.
- In Visual Studio you go to Project Properties -> C/C++ -> Additional Include Directories, and browse to $(path_to_unitc++).