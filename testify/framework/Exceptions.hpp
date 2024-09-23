#pragma once

#include <exception>


namespace Testify {
    class AssertionError : public std::exception {
        using Super = std::exception;
    public:
        AssertionError(const char* msg) noexcept :
            Super(msg)
        {}
    };


    class SegfaultError : public std::exception {
        using Super = std::exception;
    public:
        SegfaultError() noexcept :
            Super("Segmentation Fault was occured.")
        {}
    };

    class AbortCalledError : public std::exception {
        using Super = std::exception;
    public:
        AbortCalledError(const char* msg) noexcept :
            Super(msg)
        {}
    };
}