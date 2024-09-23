#pragma once

#include "ITest.hpp"
#include "TestsRuntime.hpp"
#include "Asserts.hpp"

#include "Utils.hpp"
#include "Exceptions.hpp"


#define TESTIFY_TESTS_SUITE                                     namespace Testify::UnitTests
#define TESTIFY_REGISTER_TEST(label, test)                      Testify::TestsRuntime::GetInstance().Register(label, test)


#define TESTIFY_DEFINE_TEST(label, test)                        \
    void _##test##Test();                                       \
                                                                \
    class test##Test : public Testify::ITest {                  \
    public:                                                     \
        test##Test() {                                          \
            TESTIFY_REGISTER_TEST(label, this);                 \
        }                                                       \
                                                                \
        std::string GetName() const override {                  \
            return label;                                       \
        }                                                       \
                                                                \
        void Run() override {                                   \
            _##test##Test();                                    \
        }                                                       \
    };                                                          \
    static test##Test sg_##test##Test##Instance;                \
                                                                \
    void _##test##Test()  


#define TESTIFY_RUN_ALL_TESTS()                                 \
    int main(int argc, char** argv) {                           \
        Testify::getTestsRuntime().RunAllTests(argc, argv);     \
                                                                \
        return 0;                                               \
    }
