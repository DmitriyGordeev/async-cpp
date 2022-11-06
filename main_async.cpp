#include <iostream>
#include <future>


using std::cout;


int foo(int a) {
    cout << "foo() starts\n";
    for (int i = 0; i < 100000; i++)
        for (int j = 0; j < 100000; j++)
            a = j + 2;
    cout << "foo() ends\n";
    return a + 2;
}


int main() {

    auto* arr = new std::future<int>[2];

//    std::future<int> f1 = std::async(std::launch::async, &foo, 5);
//    std::future<int> f2 = std::async(std::launch::async, &foo, 8);

    arr[0] = std::async(std::launch::async, &foo, 5);
    arr[1] = std::async(std::launch::async, &foo, 8);

    cout << "main() line 1\n";

    int b = 10;
    for (int i = 0; i < 100000; i++)
        for(int j = 0; j < 25000; j++)
            b = 10;

    cout << "main() line 2\n";


    // This is example how we can wait for all futures to be finished
    bool allReady = false;
    while(!allReady) {
        bool ready = true;
        for (int i = 0; i < 2; i++) {
            bool currentReady = arr[i].valid() && arr[i].wait_for(std::chrono::seconds(0)) == std::future_status::ready;
            ready = ready && currentReady;
        }
        allReady = ready;
    }

    cout << "allReady = " << allReady << "\n";

    int value1 = arr[0].get();        // blocks until future is done
    int value2 = arr[1].get();

    cout << "main() value1 = " << value1 << "\n";
    cout << "main() value2 = " << value2 << "\n";

    delete[] arr;
    return 0;
}


