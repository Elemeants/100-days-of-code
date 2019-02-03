#include <stdio.h>
#include <iostream>
#include <exception>
#include "list.hpp"

#ifndef TEST_ELEMENTS
#define TEST_ELEMENTS 1000
#endif

#if BENCH_TEST
#include <chrono> 
#endif 

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
    void TestFunction(
        std::function<bool(void)> function,
        const char* test_name
    ) {
        printf("   - %-17s|", test_name);
        try {
            #if BENCH_TEST
            auto start = std::chrono::system_clock::now();
            #endif
            if (!function()) {
                throw "";
            }
            printf("%9s ", "[PASSED]");
            #if BENCH_TEST
            auto end = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "| " << elapsed.count() << "us"; 
            #endif
            printf("\n");
        }catch(...) {
            printf("%9s\n", "[FAILED]");
            throw new Exceptions::UnitTestFailException(test_name);
        }
    }

    struct List_test {
    private:
        static void List_pop()
        {
            TestFunction(
                []() -> bool {
                    const int nElements = TEST_ELEMENTS;
                    List<int> testList = List<int>(nElements);
                    for (int i = 0; i < nElements; i++) {
                        if (testList.pop() != 0)
                            return false;
                    }
                    return true;
                }, "pop()"
            );
        }
        static void List_popFront()
        {
            TestFunction(
                []() -> bool {
                    const int nElements = TEST_ELEMENTS;
                    List<int> testList = List<int>(nElements);
                    for (int i = 0; i < nElements; i++) {
                        if (testList.pop_front() != 0)
                            return false;
                    }
                    return true;
                }, "pop_front()"
            );
        }
        static void List_push()
        {
            TestFunction(
                []() -> bool {
                    const int nElements = TEST_ELEMENTS;
                    List<int> testList = List<int>();
                    for (int i = 0; i < nElements; i++) {
                        testList.push(i);
                    }
                    for (int i = (nElements - 1), x = 0; i >= 1; i--, x++) {
                        if (testList[x] != i)
                            return false;
                    }
                    return true;
                }, "push()"
            );
        }
        static void List_pushBack()
        {
            TestFunction(
                []() -> bool {
                    const int nElements = TEST_ELEMENTS;
                    List<int> testList = List<int>();
                    for (int i = 0; i < nElements; i++) {
                        testList.push_back(i);
                    }
                    for (int i = 0; i < nElements; i++) {
                        if (testList[i] != i)
                            return false;
                    }
                    return true;
                }, "push_back()"
            );
        }
        static void List_clear()
        {
            TestFunction(
                []() -> bool {
                    const int nElements = TEST_ELEMENTS;
                    List<int> testList = List<int>(nElements);
                    testList.clear();
                    return (testList.length() == 0);
                }, "clear()"
            );
        }
        static void List_forEach() 
        {
            TestFunction(
                []() -> bool {
                    const int nElements = TEST_ELEMENTS;
                    List<int> testList = List<int>(nElements);
                    bool isWorking = true;
                    int nObjects = 0;
                    testList.forEach([&](int index, int &val) -> void {
                        isWorking = isWorking == false ? 
                            isWorking 
                            : (index == nObjects && val == 0);
                        nObjects++;
                    });
                    return isWorking;
                }, "forEach()"
            );
        }
        static void List_map() 
        {
            TestFunction(
                []() -> bool {
                    const int nElements = TEST_ELEMENTS;
                    List<unsigned char> testList = List<unsigned char>();
                    for (int i = 0; i < nElements; i++) {
                        testList.push_back((unsigned char)i%128);
                    }
                    List<int> resList = testList
                        .map<int>([](unsigned char &val) -> int {
                            return (int)val;
                        });
                    testList.~List();
                    for (int i = 0; i < nElements; i++) {
                        if (resList[i] != i%128)
                            return false;
                    }
                    return true;
                }, "map()"
            );
        }
    public:
        static const char* Test_List() {
            try {
                #if BENCH_TEST
                printf("\n -------------- TESTING LIST --------------\n");
                printf("   - %-17s|%8s  | %-4s n(%i)\n", "FUNCION", "STATUS", "TIME", TEST_ELEMENTS);
                printf(" ------------------------------------------\n");
                #else
                printf("\n ---------- TESTING LIST ----------\n");
                printf("   - %-17s|%8s\n", "FUNCION", "STATUS");
                printf(" ----------------------------------\n");
                #endif 
                // List of test functions
                List_test::List_pop();
                List_test::List_popFront();
                List_test::List_push();
                List_test::List_pushBack();
                List_test::List_clear();
                List_test::List_forEach();
                List_test::List_map();
            } catch(Exceptions::UnitTestFailException* e) {
                printf("\n");
                return "TEST: FAILED";
            }
            printf("\n");
            return "TEST: PASSED";
        }
    };
}

int main() {
    printf(" %s \n", UnitTest::List_test::Test_List());
    return 0;
}