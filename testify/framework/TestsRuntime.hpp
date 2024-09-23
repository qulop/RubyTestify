#pragma once

#include <string>
#include <vector>
#include <functional>

#include "ITest.hpp"
#include "Utils.hpp"
#include "Timer.hpp"


namespace Testify {
    class TestsRuntime final {
        TESTIFY_DEFINE_SINGLETON(TestsRuntime)

    public:
        using CallbackType = std::function<bool()>;
        using StorageType = std::vector<std::pair<std::string, ITest*>>;

    public:
        void Register(std::string label, ITest* test) {
            m_tests.emplace_back(std::make_pair(
                std::move(label), test));
        }


        static void RunTest(const std::string& label, ITest* test) {
            test->Run();

            fprintf_s(stdout, "[ PASSED ]: %s\n", label.c_str());
        }

        void RunAllTests(int argc, char** argv) {
            if (argc == 1)
                return;        

            auto* firstArgument = argv[1];
            if (std::strcmp(firstArgument, "--run-registered") == 0)
                RunAllRegisteredTests();

            RunFromCommandLine(argc, argv);
        }

        TESTIFY_NODISCARD const StorageType& GetAllTests() const {
            return m_tests;
        }

    private:
        void RunAllRegisteredTests() {
            if (m_tests.empty()) {
                fprintf_s(stdout, "Nothing to test");
                return;
            }

            TestAll(m_tests);
        }

        void TestAll(const StorageType& testsStorage) {
            uint64_t countOfSuccessfulTests = 0;
            StopWatch stopWatch{};

            for (const auto& t : testsStorage) {
                try {
                    RunTest(t.first, t.second);
                    ++countOfSuccessfulTests;
                }
                catch(const std::exception& err) {
                    fprintf_s(stderr, "[ FAILED ]: Failed: %s\n", err.what());
                }
            }
            
            fprintf_s(stdout, "\n\n------Tests Results------\n");
            fprintf_s(stdout, "-- Tests passed: %lld/%zd\n", countOfSuccessfulTests, m_tests.size());
            fprintf_s(stdout, "-- Elapsed time: %lld\n", stopWatch.Elapsed().count());
        }

        void RunFromCommandLine(int argc, char** argv) {

        }

    private:
        StorageType m_tests;
    };


    inline TestsRuntime& getTestsRuntime() {
        return TestsRuntime::GetInstance();
    }
}