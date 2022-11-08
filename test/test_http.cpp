#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <future>
#include <chrono>
using std::cout;

#include "doctest.h"
#include "httplib.h"



TEST_CASE("simple http request example with cpp-httplib") {
    httplib::Client cli("http://www.boredapi.com");
    auto res = cli.Get("/api/activity");

    CHECK_FALSE(res == nullptr);
    WARN((res->status >= 200 && res->status < 300));
    CHECK(res->body.size() > 0);

    cout << res->status << "\n";
    cout << res->body << "\n";
}



std::pair<int, std::string> GET(const std::string url, const std::string& args) {
    httplib::Client cli(url);
    auto r = cli.Get(args);
    return {r->status, r->body};
}


TEST_CASE("simple http GET wrapped into async") {
    auto f =
            std::async(std::launch::async, &GET, "http://www.boredapi.com", "/api/activity");

    cout << "ready = " << (f.wait_for(std::chrono::seconds(0)) == std::future_status::ready) << "\n";

    auto r = f.get();

    cout << r.first << "\n";
    cout << r.second << "\n";

    CHECK(r.first == 200);
}