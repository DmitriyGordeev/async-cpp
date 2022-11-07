#include <iostream>
#include <future>

#include "utils.h"
#include "httplib.h"

using std::cout;
using std::string;


const std::string services[] = {
    "https://catfact.ninja/fact",
    "https://api.coindesk.com/v1/bpi/currentprice.json",
    "https://www.boredapi.com/api/activity",
    "https://api.agify.io?name=meelad"
};


std::pair<int, std::string> get(const std::string& url, const std::string& args) {
    httplib::Client cli(url);
    auto r = cli.Get(args);
    return {r->status, r->body};
}

int main() {

    int num_services = sizeof(services) / sizeof(std::string);

    for (int i = 0; i < num_services; i++) {
        auto f = std::async(std::launch::async, &get, );
    }

    return 0;
}


