#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
using std::cout;

#include "doctest.h"


TEST_CASE("parsing response") {
    std::string str = R"({"activity":"Resolve a problem you've been putting off","type":"busywork","participants":1,"price":0,"link":"","key":"9999999","accessibility":0})";
    size_t comma_pos = str.find(',');
    size_t colon_pos = str.find(':');

    std::string activity = str.substr(colon_pos + 2, comma_pos - colon_pos - 3);
    cout << activity << "\n";
    CHECK(activity == "Resolve a problem you've been putting off");
}
