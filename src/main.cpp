#include <iostream>
#include <future>
#include <memory>
#include "utils.h"
#include "httplib.h"

using std::cout;
using std::string;


/** This program is just a quick cheat-sheet of using std::async */


const std::pair<string, string> services[] = {
        {"http://catfact.ninja", "/fact"},
        {"http://api.coindesk.com", "/v1/bpi/currentprice.json"},
        {"http://www.boredapi.com", "/api/activity"}
};


std::pair<int, std::string> get(const std::string& url, const std::string& args) {
    httplib::Client cli(url);
    auto r = cli.Get(args);
    return {r->status, r->body};
}


int main() {

    int num_services = sizeof(services) / sizeof(std::pair<string, string>);
    auto futures = new std::future<void>[num_services];
    auto thens = new std::future<void>[num_services];

    // spawn futures starting underlying task
    // and collect into array
    for (int i = 0; i < num_services; i++) {
        auto s = services[i];

        // TODO: how to catch exception inside async task ?

        futures[i] = std::async(std::launch::async, [s, &thens, i]() -> void {
            auto r = get(s.first, s.second);

            thens[i] = std::async(std::launch::async, [r]() -> void {
                std::this_thread::sleep_for(std::chrono::seconds(10));
                cout << "------------\n";
                cout << r.first << ", " << r.second << "\n";
            });
        });
    }


    cout << "main() about to end\n";


//    bool all_ready = false;
//    while(!all_ready) {
//        bool ready = true;
//        for (int i = 0; i < 2; i++) {
//            bool future_ready =
//                    thens[i].valid() &&
//                    thens[i].wait_for(std::chrono::seconds(0)) == std::future_status::ready;
//            ready = ready && future_ready;
//        }
//        all_ready = ready;
//    }


    delete[] futures;
    cout << "after delete[] futures\n";
    delete[] thens;
    cout << "after delete[] thens\n";
    return 0;
}


