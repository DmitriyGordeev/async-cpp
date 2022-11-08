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
    "http://www.boredapi.com/api/activity",
    "http://api.agify.io?name=meelad"
};


std::pair<int, std::string> get(const std::string& url, const std::string& args) {
    httplib::Client cli(url);
    auto r = cli.Get(args);
    return {r->status, r->body};
}

int main() {

    int num_services = sizeof(services) / sizeof(std::string);

    // create array holding future objects
    std::shared_ptr<std::future<std::pair<int, string>>[]> futures(new std::future<std::pair<int, string>>[num_services]);


    // spawn futures starting underlying task
    // and collect into array
    for (int i = 0; i < num_services; i++) {
        auto p = split_url(services[i]);    // p.first = root url, p.second = GET args
        cout << "url: " << p.first << ", args: " << p.second << "\n";
        futures[i] = std::async(std::launch::async, &get, p.first, p.second);
    }

    // TODO: wait until all are finished

    // TOOD: implement then() somehow ?






//    delete[] futures;
    return 0;
}


