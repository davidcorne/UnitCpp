# Running the tests. #

These tests can run using g++ or cl

## Running tests automatically ##

If you have bash and make on your machine, all you do is.

~~~
cd UnitCpp/Testing
chmod +x test.sh
./test.sh
~~~

This will run all the tests on all the compilers you have available.

## Running tests manually ##

If you want to choose which compiler tests to run you can.

- cd UnitCpp/Testing
- Run `make test`.

This will default to using g++, if you give it compiler arguments COMPILER_TYPE= you can change this. Currently it accepts COMPILER_TYPE=gcc (uses g++), COMPILER_TYPE=vs (uses visual studio cl).

## Running using Visual Studio ##

- Make an empty project. This can be located anywhere, and called anything. For this example I will call mine UnitC++Tests.
- Right click on the project, choose Add->Existing Item.
- Browse to UnitCpp/Testing/source.
- Add all the .cpp files.
- Right click on the project, choose properties.
- Configuration Properties -> C/C++ -> General -> Additional Include Directories -> Edit.
- New Line (the new folder icon).
- Browse to UnitCpp.
- Ok this and the properties.
- The project should build and run the tests.
