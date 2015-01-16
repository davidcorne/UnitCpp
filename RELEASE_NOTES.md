# Release Notes #

This is a note of what features have changed in each version. In each version tests, examples and documentation will also change but this is not reflected here.

## 1.0.0 ##

- Everything is new.

## 1.1.0 ##

- Menus added to TestRegister.

## 1.1.1 ##

- Visual studio W4 fixed (could not generate some assignment operators.)
- Added RELEASE_NOTES.md.

## 1.2.0 ##

- A new macro `UNITCPP_FRIEND_TEST` added for testing class internals.

## 1.3.0 ##

- The TEST_X macros have been made variadic so custom user text can be added. e.g. `TEST_EQUAL(15, size, "Wrong size.");`

## 1.3.1 ##

- Fix a bug with variadic user text only working for one argument.

## 1.3.2 ##

- Fix a bug with TEST_TRUE(pointer).

## 1.3.3 ##

- Add and fix an issue with templates and macro expansion (https://bitbucket.org/davidcorne/unitcpp/issue/3/test-macros-fail-with-some-arguments)

## 1.3.4 ##

- Fix an issue with non-copyably types in `TEST_TRUE/TEST_FALSE`. See [Issue 4](https://bitbucket.org/davidcorne/unitcpp/issue/4/allow-test_true-test_false-to-work-with).

## 1.4.0 ##

- Change from a Creative Commons licence, to an MIT licence. This is on the advice of [this](https://wiki.creativecommons.org/Frequently_Asked_Questions#Can_I_apply_a_Creative_Commons_license_to_software.3F).
