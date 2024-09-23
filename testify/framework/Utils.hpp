#pragma once

#include "Exceptions.hpp"


#define TESTIFY_DEFINE_SINGLETON(ClassName) private:                                                \
                                                ClassName(void) = default;                          \
                                                                                                    \
                                            public:                                                 \
                                                ClassName(const ClassName&) = delete;               \
                                                ClassName(ClassName&&) = delete;                    \
                                                ClassName& operator=(const ClassName&) = delete;    \
                                                ClassName& operator=(ClassName&&) = delete;         \
                                                                                                    \
                                                static ClassName& GetInstance(void) {               \
                                                    static ClassName tmp;                           \
                                                    return tmp;                                     \
                                                }                                                   \



#define TESTIFY_NODISCARD   [[nodiscard]]

#define interface           struct


namespace Testify {
    template<typename ExceptionType=AssertionError>
    void throwIfFalse(bool expr, const char* msg) {
        if (!expr)
            ExceptionType{ msg };
    }
}