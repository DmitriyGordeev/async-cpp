#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <future>
using std::cout;


//int factorial(int number) { return number <= 1 ? number : factorial(number - 1) * number; }

//TEST_CASE("testing the factorial function") {
//    CHECK(factorial(1) == 1);
//    CHECK(factorial(2) == 2);
//    CHECK(factorial(3) == 6);
//    CHECK(factorial(10) == 3628800);
//}


int foo(int a) {
    cout << "foo() starts\n";
    for (int i = 0; i < 100000; i++)
        for (int j = 0; j < 100000; j++)
            a = j + 2;
    cout << "foo() ends\n";
    return a + 2;
}


TEST_CASE("simple async usage") {

    auto* arr = new std::future<int>[2];
    arr[0] = std::async(std::launch::async, &foo, 5);
    arr[1] = std::async(std::launch::async, &foo, 8);

    cout << "main() line 1\n";

    int b = 10;
    for (int i = 0; i < 100000; i++)
        for(int j = 0; j < 25000; j++)
            b = 10;

    cout << "main() line 2\n";


    // This is example how we can wait for all futures to be finished
    // blocked until all of them finished
    bool all_ready = false;
    while(!all_ready) {
        bool ready = true;
        for (int i = 0; i < 2; i++) {
            bool future_ready =
                    arr[i].valid() &&
                    arr[i].wait_for(std::chrono::seconds(0)) == std::future_status::ready;
            ready = ready && future_ready;
        }
        all_ready = ready;
    }

    CHECK(all_ready == true);

    cout << "allReady = " << all_ready << "\n";

    int value1 = arr[0].get();        // blocks until future is done
    int value2 = arr[1].get();

    cout << "main() value1 = " << value1 << "\n";
    cout << "main() value2 = " << value2 << "\n";

    delete[] arr;
}