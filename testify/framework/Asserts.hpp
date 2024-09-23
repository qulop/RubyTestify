#pragma once

#include <algorithm>

#include "Utils.hpp"
// #ifdef RUBY_LINUX_USED
//     #include <csignal>
//     #include <csetjmp>
// #endif


namespace Testify {
    namespace Details::Asserts {
        template<typename Tx, typename Ty>
        void compareAssert(Tx&& exp, Ty&& act,
                           const char* strExpected, const char* strActual, bool equalOp=true) {
            bool condition = (equalOp) == (exp == act);
            if (condition)
                return;

            auto* equalitySign = (equalOp) ? "==" : "!=";
            auto msg = std::format("\"{} {} {}\": expected {}, but got {}",
                strExpected, equalitySign, strActual,
                std::forward<Tx>(exp), std::forward<Ty>(act));

            throw AssertionError{ msg.c_str() };
        }
    }


    template<typename Tx, typename Cont>
    void assertContains(Tx&& tx, Cont&& cont) {
        constexpr bool res = std::ranges::contains(cont.begin(), cont.end(), tx);
        if constexpr (!res) {
            throw AssertionError{ 
                std::format("{} doesn't contains in the specified container", tx).c_str() 
            };
        }
    }
}

//#if defined(RUBY_WIN32_USED)
//    #define RUBY_NO_SEGFAULTS_BEGIN_IMPL()    __try {
//    #define RUBY_NO_SEGFAULTS_END_IMPL()            \
//        }                                           \
//        __except(EXCEPTION_EXECUTE_HANDLER) {       \
//            throw SegfaultError{};                  \
//        }
//#elif defined(RUBY_LINUX_USED)
//    #define RUBY_NO_SEGFAULTS_BEGIN_IMPL() \
//        if (segsetjmp(Testify::Details::Asserst::jmpBuf, 1) == 0) { \
//            signal(SIGSEGV, si)
//    #define RUBY_NO_SEGFAULTS_END_IMPL()      \
//        }                                           \
//        __except(EXCEPTION_EXECUTE_HANDLER) {       \
//            throw SegfaultError{};                  \
//        }
//#endif



#define TESTIFY_ASSERT_EQ(exp, act)          \
    Testify::Details::Asserts::compareAssert(exp, act, #exp, #act);
#define TESTIFY_ASSERT_NEQ(exp, act)         \
    Testify::Details::Asserts::compareAssert(exp, act, #exp, #act, false);

#define TESTIFY_ASSERT_TRUE(cond)            \
    Testify::throwIfFalse(cond, "The condition doesn't evaluate to false");
#define TESTIFY_ASSERT_FALSE(cond)           \
    Testify::throwIfFalse(!cond, "The condition doesn't evaluate to false");

//#define TESTIFY_NO_SEGFAULTS_BEGIN()  RUBY_NO_SEGFAULTS_BEGIN_IMPL()
//#define TESTIFY_NO_SEGFAULTS_END()  RUBY_NO_SEGFAULTS_END_IMPL()

#define TESTIFY_ASSERT_IS_INSTANCE(Tx, Ty)   \
    Testify::throwIfFalse(std::is_base_of_v<Tx, Ty>, "Two types isn't equal")

#define TESTIFY_ASSERT_CONTAINS(target, cont)        \
    Testify::assertContains(target, cont)

#define TESTIFY_ASSERT_MUST_ABORT(exp)   exp
