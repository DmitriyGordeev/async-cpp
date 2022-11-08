#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <future>
#include <chrono>
using std::cout;

#include "doctest.h"
#include "utils.h"


TEST_CASE("simple http request example with cpp-httplib") {
    httplib::Client cli("http://www.boredapi.com");
    auto res = cli.Get("/api/activity");

    CHECK_FALSE(res == nullptr);
    WARN((res->status >= 200 && res->status < 300));
    CHECK(res->body.size() > 0);

    cout << res->status << "\n";
    cout << res->body << "\n";
}



TEST_CASE("simple http GET wrapped into async") {
    auto f =
            std::async(std::launch::async, &get, "http://www.boredapi.com", "/api/activity");

    cout << "some code can be here\n";

    auto r = f.get();       // waiting for future to be finished
    cout << "status code " << r.first << "\n";
    cout << "body:\n" << r.second << "\n";
    CHECK(r.first == 200);
}