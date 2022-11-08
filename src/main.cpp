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

    // spawn futures starting underlying task
    // and collect into array
    for (int i = 0; i < num_services; i++) {
        auto s = services[i];

        // TODO: how to catch exception inside async task ?

        futures[i] = std::async(std::launch::async, [s]() -> void {
            auto r = get(s.first, s.second);
        });
    }



//    for (int i = 0; i < num_services; i++) {
//        futures[i].get();
//    }


    delete[] futures;
    return 0;
}


