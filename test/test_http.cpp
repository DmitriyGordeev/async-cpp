#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
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
