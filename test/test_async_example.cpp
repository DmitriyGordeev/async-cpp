#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <chrono>
#include <thread>

#include <iostream>
#include <future>
using std::cout;


int foo(int a) {
    cout << "foo() starts\n";

    // assume some code is running in meantime
    std::this_thread::sleep_for(std::chrono::seconds(5));

    cout << "foo() ends\n";

    return a + 2;
}


TEST_CASE("simple async usage") {

    cout << "------- TEST1 ------- \n";

    // Create two async tasks and run them (saving into array arr)
    auto* arr = new std::future<int>[2];
    arr[0] = std::async(std::launch::async, &foo, 5);
    arr[1] = std::async(std::launch::async, &foo, 8);

    cout << "started 2 async tasks\n";

    // assume some code is running in meantime
    std::this_thread::sleep_for(std::chrono::seconds(3));

    cout << "sleep ends\n";


    // This is example how we can wait for all futures to be finished
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

    cout << "all_ready = " << all_ready << "\n";

    int value1 = arr[0].get();        // blocks until future is done
    int value2 = arr[1].get();

    cout << "value1 = " << value1 << "\n";
    cout << "value2 = " << value2 << "\n";

    delete[] arr;
}



TEST_CASE("then") {

    cout << "------- TEST2 ------- \n";

    auto l = []() -> std::future<void> {
        cout << "lambda starts\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        cout << "lambda wait has finished\n";

        // possible then() implementation
        // we create future inside another future and return it
        auto then = std::async(std::launch::async, []() -> void {
            cout << "inner lambda starts\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            cout << "inner lambda ends\n";
        });

        cout << "lambda ends\n";
        return then;
    };


    auto f = std::async(std::launch::async, l);

    cout << "Some code in a meantime\n";

    auto innerf = f.get();

    cout << "another code\n";

    innerf.get();

    cout << "TEST ENDS\n";
}