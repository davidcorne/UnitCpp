# UnitC++ #

UnitC++ is a modern, light weight, header-only c++ library for making unit testing easy. The intention of UnitC++ is to make it really easy to test c++ code in a portable way.

## How to use UnitC++ ##

### How to get UnitC++ ###

__For Users__

UnitC++ has a project page on [SourceForge](https://sourceforge.net/projects/unitcpp/) which has versioned downloads.

__For Developers__

UnitC++ is stored in a mercurial repository centrally at bitbucket. The best way to get it is to clone it onto local disk. Like so.

    cd ~
    hg clone https://davidcorne@bitbucket.org/davidcorne/unitcpp


You can also download/clone it from GitHub at `https://github.com/davidcorne/UnitCpp`.

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

One thing which many people want to do with unit tests is access private members of the class they are testing. This can be done in UnitC++ by use of the `UNITCPP_FRIEND_TEST` macro. This is used like so;

~~~
class Container {
public:
...
private:
  UNITCPP_FRIEND_TEST(Container, internals)
  int m_member;
};

TEST(Container, internals)
{
  Container container;
  TEST_EQUAL(container.m_member, 5);
}
~~~

So you declare the specific test a friend of the class you are testing. The macro is called `UNITCPP_FRIEND_TEST` so it is declared in the same way as a `friend class`. 

Note: If you are running many tests in a loop you may want to only print the results which are failures. This is done using the `stop_printing()` and `restart_printing()` functions. Like this:

~~~
TEST(Test, loop)
{
  std::vector<int> ints;
  stop_printing();
  for (int i = 0; i < 1000; ++i) {
    ints.push_back(i);
    TEST_EQUAL(ints [i], i);
  }
  restart_printing();
  TEST_EQUAL(ints.size(), 1000);
}
~~~

This will only print

~~~
Pass: "ints.size() should equal 1000." utest_README.cpp:15
~~~

Without an additional 1000 lines of 

~~~
Pass: "ints [i] should equal i." utest_README.cpp:12
~~~

__Running the tests with a menu__

So you've written a nice set of tests and now you want to run them. This is done with the `TestRegister` class. This is a singleton that has registered all of the tests you've declared with the `TEST` macro. These are run using the following code.

~~~
//=============================================================================
int main(int argc, char** argv)
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(
    argc,
    argv
  );
}
~~~

This will produce a menu which looks something like this:

~~~
================================================================================
0) All tests.

================================================================================
1) Maths
  2) "Maths:sqrt_results"
  3) "Maths:is_square"
  4) "Maths:sqrt_precondition"

================================================================================
5) MyString
  6) "MyString:length_test"
  7) "MyString:validity_test"

~~~

This gives you the option of running any individual test, any group of tests or all tests.

These numbers can also be give on the command line. e.g. `utest.exe 0` will always run all tests.

__Running the tests without a menu__

If you don't want the menu or command line options and just want an executable which runs all of the tests the you want a test harness which looks like this:


~~~
#include <UnitCpp/TestRegister.h>

int main()
{
  return UnitCpp::TestRegister::test_register().run_tests();
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

It's tested using UnitC++ of course! I run continuous integration using [drone.io](https://drone.io/bitbucket.org/davidcorne/unitcpp). I currently test it with `g++`, `clang` and `cl`. On drone.io I test `g++` and `clang` and I test/develop with `g++` and `cl` on my windows machine using cygwin. The current state of the drone.io build is [![Build Status](https://drone.io/bitbucket.org/davidcorne/unitcpp/status.png)](https://drone.io/bitbucket.org/davidcorne/unitcpp/latest).

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

## Contributing to UnitC++ ##

The GitHub site is a mirror of the mercurial repository. So you should use mercurial and bitbucket. Send me a pull request at [https://davidcorne@bitbucket.org/davidcorne/unitcpp](https://davidcorne@bitbucket.org/davidcorne/unitcpp) and I'll get back to you.
