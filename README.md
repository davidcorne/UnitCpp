# UnitC++ #

UnitC++ is a modern, light weight, header-only c++ library for making unit testing easy. The intention of UnitC++ is to make it really easy to test c++ code in a portable way.

## How to use UnitC++ ##

### How to get UnitC++ ###
UnitC++ is stored in a mercurial repository. The best way to get it is to clone it onto local disk. Like so.

    cd ~
    hg clone https://davidcorne@bitbucket.org/davidcorne/unitcpp

### How to include UnitC++ in your project ###

As a header-only library this step should be easy to accomplish. However While how you do this will vary depending on your build process, it will be straightforward. As this is a header-only library all you need to do is add the repository path to the compiler include line. Here are two examples of how that is done.

__From command line__

Compiling from the command line you add the argument `-I $(path_to_unitc++)`. This works for g++/clang/cl from the command line. This can also be added to the compiler arguments in a makefile.

__From Visual Studio__

in Visual Studio you go to Project Properties -> C/C++ -> Additional Include Directories, and browse to $(path_to_unitc++).

### How to write a unit test using UnitC++ ##

__Writing a test__

The first thing to do is include `<UnitCpp/Test.h>`. This is the header whihc will bring in everything you need.

Then you need to declare you are writing a test by writing `TEST(goup_name, test_name)`. This works like declaring a function, so a set of tests for a class called `MyString` will look something like this.

~~~
#include <UnitCpp/Test.h>

TEST(MyString, length_test)
{
  //...
}

TEST(MyString, validity_test)
{
  //...
}
~~~

Note: the pattern here is to write several tests for a class with the class as the `group_name` and what you are testing as the `test_name` in the `TEST` macro.

Now you are ready to write the test code. UnitC++ provided some helpful macros for writing tests. Here is a list of them.

~~~
TEST_EQUAL(A, B)
TEST_NOT_EQUAL(A, B)
TEST_LESS_THAN(A, B)
TEST_MORE_THAN(A, B)
TEST_APPROX_EQUAL(A, B, TOLERANCE)
TEST_TRUE(A)
TEST_FALSE(A)
TEST_THROWS(FUNCTION, EXCEPTION, ...)
~~~

So here is a filled out version of the above example of a test.
~~~
#include <UnitCpp/Test.h>

TEST(MyString, length_test)
{
  MyString str("This is a string");
  TEST_EQUAL(str.length(), 16);
  TEST_NOT_EQUAL(str.length(), 17);
  TEST_LESS_THAN(str.length(), 20);
  TEST_MORE_THAN(str.length(), 10);
  TEST_APPROX_EQUAL(str.length(), 15, 1.1); // test the length is within 1.1 of 15
}

TEST(MyString, validity_test)
{
  MyString invalid_string;
  TEST_FALSE(invalid_string.valid());

  MyString valid_string("");
  TEST_TRUE(valid_string.valid());

#ifdef UNITCPP_TEST_THROWS_AVAILABLE
  TEST_THROWS([&](){invalid_string.length();}, MyString::InvalidStringException);
#endif // UNITCPP_TEST_THROWS_AVAILABLE

}

~~~

This is obviously a contrived example, there are several tests checking the same thing. i.e. that the length of `"This is a string"` is 16. However it is an example of how the macros are used.

Note the use of `TEST_THROWS`, it is for testing that a certain exception was thrown. It takes a function to call, the exception which should be thrown and the arguments to the function. Note the use of a [lambda function](http://www.cprogramming.com/c++11/c++11-lambda-closures.html), this is because `TEST_THROWS` is expecting a function and you want to call a member function.

In each `TEST` you can use functions from `TestCase`. This means for example, you can call `test_equal<double>(1, some_function())` if you want the values to be compared as `doubles`s not `int`s.

__Running the tests__

So you've written a nice set of tests and now you want to run them. This is done with the `TestRegister` class. This is a singleton that has registered all of the tests you've declared with the `TEST` macro. These are run in the following way.

~~~
#include <UnitCpp/TestRegister.h>

int main()
{
  return TestRegister::test_register().run_tests();
}
~~~

As long as the code with the tests in is linked into the executable `TestRegister::test_register().run_tests()` will run the tests.

You can also call `TestRegister::test_register().run_tests("group_name")` to run all the tests in a specific group.

__Working examples__

In the `Example` folder there is a working example for a further demonstration of some of the capabilities of UnitC++.

## Frequently Asked Questions ##

__UnitC++ doesn't work with my compiler!__

Ok, this isn't actually a commonly asked question. But, if your compiler doesn't work with UnitC++ please let me know! I will fix this as soon as I can. See _How do I report an issue or request a feature_ for how to let me know, thanks.

__How do I request a feature or report an issue__

I am always happy to take a look at an improvement or fix a bug, you just have to let me know about it. The best way to do this is file an issue on my issue tracker. This is located [https://bitbucket.org/davidcorne/unitcpp/issues?status=new&status=open](here) don't be shy, I'm not going to snap at anyone.

__Do you use this?__

I made UnitC++ for my personal use. This means that I use it whenever I need to test anything. 

__How is UnitC++ tested?__

It's tested using UnitC++ of course! I run continuous integration using [drone.io](https://drone.io/bitbucket.org/davidcorne/unitcpp). I currently test it using `g++` and am looking at testing using `clang`. The current state of the build is [![Build Status](https://drone.io/bitbucket.org/davidcorne/unitcpp/status.png)](https://drone.io/bitbucket.org/davidcorne/unitcpp/latest).

__How does it work?__

Each `TEST` does 3 things:

1. It defines a class derived from `TestCase`.
2. It makes a global instance of this class.
3. It lets you provide the body of the overriden function `run()`.

The reason a global object is declared is to call the constructor. In the constructor of `TestCase` it registers itself so `TestRegister` knows which tests to run. This is how as long as the objects are linked against, `TestRegister::test_register().run_tests()` will run them all.

__You say this is a modern library, why are there so many preprocessor macros?__

This is because unfortunately macros are the best way of doing some things. Macros are used for 2 reasons in UnitC++. 

1. For judging compiler support. For the TEST_THROWS functionality we use variadic templates, this was not supported by visual studio until 2013. As pre-2013 visual studio compilers are in very wide use, we decided to include this functionality for those with compiler support, and to not break the build of those without.

2. For generating good error messages in tests. Compare the following message; `Fail: These arguments should be equal` and `Fail: "Maths::sqrt(4.0) should equal 2." utest_Maths.cpp:8`. I know I prefer the second one, and getting the line of code, file name and line number cannot be done without macros.
