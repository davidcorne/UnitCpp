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
