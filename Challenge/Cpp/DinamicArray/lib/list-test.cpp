#include <stdio.h>
#include <iostream>
#include <exception>
#include "list.hpp"

namespace Exceptions {
    struct UnitTestFailException : public std::exception
    {
    private:
        const char* error_log;
    public:
        UnitTestFailException(const char* error_log): error_log((char*)error_log) { }
        UnitTestFailException(): error_log("UnitTestFailException") { }
        char const* what() const throw()
        {
            return error_log;
        }
    };
}

namespace UnitTest {
    struct List_test {
    private:
        static void List_pop(List<int> &testList, int expected_length)
        {
            std::cout << "Testing List.pop() ";
            testList.pop();
            if (testList.length() != expected_length) {
                std::cout << std::endl;
                throw new Exceptions::UnitTestFailException("TEST: @LIST_POP FAILED");
            }
            std::cout << "[PASSED]" << std::endl;
        }
        static void List_push(List<int> &testList, int expected_length)
        {
            std::cout << "Testing List.push() ";
            testList.push(20);
            if(testList.length() != expected_length) {
                std::cout << "[FAILED]" << std::endl;
                throw new Exceptions::UnitTestFailException("TEST: @LIST_PUSH FAILED, length error");
            }
            if(testList[0] != 20) {
                std::cout << "[FAILED]" << std::endl;
                throw new Exceptions::UnitTestFailException("TEST: @LIST_PUSH FAILED, not equal error");
            }
            std::cout << "[PASSED]" << std::endl;
        }
        static void List_clear(List<int> &testList)
        {
            std::cout << "Testing List.clear() ";
            testList.clear();
            if(testList.length() != 0) {
                std::cout << "[FAILED]" << std::endl;
                throw new Exceptions::UnitTestFailException("TEST: @LIST_CLEAR FAILED");
            }
            std::cout << "[PASSED]" << std::endl;
        }
    public:
        static const char* Test_List() {
            try {
                List<int> testList = List<int>(2);
                List_test::List_pop(testList, testList.length() - 1);
                List_test::List_push(testList, testList.length() + 1);
                List_test::List_clear(testList);
            } catch(std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
            return "TEST: @LIST PASSED!!";
        }
    };
}

int main() {
    printf(" %s \n", UnitTest::List_test::Test_List());
    return 0;
}