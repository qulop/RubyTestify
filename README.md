# Testify - header only microframework
___
### Overview

All library is contained in a single header - `Testify.hpp`, so you do not need to think about many dependencies and build process.

__
### Requirements
Library has only one requirement - compiler with support C++23.

___
### Examples


1) Definition of a simple test
```cpp
#include <Testify.hpp>


TESTIFY_TESTS_SUITE {
    constexpr int add(int a, int b) {
        return a + b;
    }

    TESTIFY_DEFINE_TEST(TestLabel, nameOfTestFunction) {
        TESTIFY_ASSERT_EQ(2, add(1, 1))
    }
}
```