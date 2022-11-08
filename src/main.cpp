#include <iostream>
#include <future>
#include <memory>
#include "utils.h"
#include "httplib.h"

using std::cout;
using std::string;


/** This program is just a quick cheat-sheet of using std::async */


const std::string services[] = {
    "http://catfact.ninja/fact",
    "http://api.coindesk.com/v1/bpi/currentprice.json",
    "http://www.boredapi.com/api/activity"
//    "http://api.agify.io?name=meelad"
};


std::pair<int, std::string> get(const std::string& url, const std::string& args) {

    cout << "get(): url = " << url << ", args = " << args << "\n";

    httplib::Client cli(url);
    auto r = cli.Get(args);
    return {200, ""};
//    return {r->status, r->body};
}


int main() {

    int num_services = sizeof(services) / sizeof(std::string);

    // create array holding future objects
//    std::shared_ptr<std::future<std::pair<int, string>>[]> futures(new std::future<std::pair<int, string>>[num_services]);

//    std::shared_ptr<std::future<void>[]> futures(new std::future<void>[num_services]);
//    std::shared_ptr<std::future<void>[]> thens(new std::future<void>[num_services]);

    auto futures = new std::future<void>[num_services];

    // spawn futures starting underlying task
    // and collect into array
    for (int i = 0; i < num_services; i++) {
        auto p = split_url(services[i]);    // p.first = root url, p.second = GET args
        cout << "url = " << p.first << ", args = " << p.second << "\n";

        futures[i] = std::async(std::launch::async, [&p]() -> void {
            auto response = get(p.first, p.second);
//            if (response.first < 200 || response.first >= 300) {
//                // todo: unsuccessful request
//            }

            cout << "Something\n";

//            thens[i] = std::async(std::launch::async, [response]() -> void {
////                cout << "then():" << "\n";
//                cout << response.second << "\n";
//            });
        });
    }


    // Wait until all thens are finished:
    bool all_ready = false;
    while(!all_ready) {
        bool ready = true;
        for (int i = 0; i < num_services; i++) {
            bool b1 = futures[i].valid();
            bool b2 = futures[i].wait_for(std::chrono::seconds(0)) == std::future_status::ready;
            bool future_ready = b1 && b2;
            ready = ready && future_ready;
        }
        all_ready = ready;
    }





    cout << "futures has passed\n";

//    // Wait until all thens are finished:
//    all_ready = false;
//    while(!all_ready) {
//        bool ready = true;
//        for (int i = 0; i < num_services; i++) {
//            bool future_ready =
//                    thens[i].valid() &&
//                    thens[i].wait_for(std::chrono::seconds(0)) == std::future_status::ready;
//
//            ready = ready && future_ready;
//        }
//        all_ready = ready;
//    }


    cout << "All futures are finished\n";

    delete[] futures;
    return 0;
}


