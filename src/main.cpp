#include <iostream>
#include <future>
#include <memory>
#include "utils.h"


using std::cout;
using std::string;


/** This program is just a quick cheat-sheet of using std::async */


const std::pair<string, string> services[] = {
        {"http://catfact.ninja", "/fact"},
        {"http://api.coindesk.com", "/v1/bpi/currentprice.json"},
        {"http://www.boredapi.com", "/api/activity"}
};



int main() {

    int num_services = sizeof(services) / sizeof(std::pair<string, string>);
//    auto futures = new std::future<void>[num_services];
//    auto thens = new std::future<void>[num_services];

    std::shared_ptr<std::future<void>[]> futures(new std::future<void>[num_services]);
    std::shared_ptr<std::future<void>[]> thens(new std::future<void>[num_services]);

    // spawn futures with underlying GET request and another future 'then'
    // and collect into array
    for (int i = 0; i < num_services; i++) {
        auto s = services[i];

        // TODO: how to catch exception inside async task ?

        futures[i] = std::async(std::launch::async, [s, &thens, i]() -> void {

            // perform GET request
            auto r = get(s.first, s.second);

            // and then start another task (like .then(() => { ... }) in js)
            thens[i] = std::async(std::launch::async, [r]() -> void {
                // some long-running task
                std::this_thread::sleep_for(std::chrono::seconds(10));

                // printing results
                cout << "------------\n";
                cout << "status: " << r.first << "\n";
                cout << "body:" << r.second << "\n";
            });
        });
    }


    cout << "Other stuff can be calculated here while futures are running\n";


    // Waiting for all the futures to be finished
    // todo: is there more elegant way ?
    bool all_ready = false;
    while(!all_ready) {
        bool ready = true;
        for (int i = 0; i < num_services; i++) {
            bool future_ready =
                    thens[i].valid() &&
                    thens[i].wait_for(std::chrono::seconds(0)) == std::future_status::ready;
            ready = ready && future_ready;
        }
        all_ready = ready;
    }


//    delete[] futures;
//    delete[] thens;
    return 0;
}


