#pragma once

#include "Utils.hpp"

#include <string>


namespace Testify {
    interface ITest {
        virtual void Run() = 0;
        TESTIFY_NODISCARD virtual std::string GetName() const = 0;

        virtual ~ITest() = default;
    };
}