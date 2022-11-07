#include "async_http.h"
#include "httplib.h"
#include <future>


void async_http::async_get(const std::string& root, const std::string& path) {
    httplib::Client cli(root);
    auto res = cli.Get(path);
}