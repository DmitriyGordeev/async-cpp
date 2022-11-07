#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
using std::cout;
using std::string;

#include "doctest.h"
#include "utils.h"


TEST_CASE("parsing response") {
    std::string str = R"({"activity":"Resolve a problem you've been putting off","type":"busywork","participants":1,"price":0,"link":"","key":"9999999","accessibility":0})";
    size_t comma_pos = str.find(',');
    size_t colon_pos = str.find(':');

    std::string activity = str.substr(colon_pos + 2, comma_pos - colon_pos - 3);
    cout << activity << "\n";
    CHECK(activity == "Resolve a problem you've been putting off");
}


TEST_CASE("split url") {

    auto p1 = split_url("https://catfact.ninja/");
    CHECK("catfact.ninja/" == p1.first);
    CHECK("" == p1.second);

    auto p2 = split_url("https://catfact.ninja/arg1");
    CHECK("catfact.ninja" == p2.first);
    CHECK("/arg1" == p2.second);

}
