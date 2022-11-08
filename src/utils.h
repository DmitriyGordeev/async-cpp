#ifndef ASYNC_EXAMPLES_UTILS_H
#define ASYNC_EXAMPLES_UTILS_H

#include <string>
using std::string;

#include "httplib.h"

/**
 * Splits url into root and arguments
 * e.g. url = "https://catfact.ninja/arg1" -> output ("catfact.ninja", "/arg1")
 * @param url
 * @return
 */
std::pair<std::string, std::string> split_url(const std::string& url) {
    size_t double_slash = url.find("://");
    if (double_slash == string::npos) {
        return {"", ""};
    }

    auto residual = url.substr(double_slash + 3);
    size_t arg_start = residual.find('/');
    if (arg_start == string::npos || arg_start == residual.size() - 1) {
        arg_start = residual.find('?');
        if (arg_start == string::npos || arg_start == residual.size() - 1)
            return {residual, ""};
    }
    auto root_url = residual.substr(0, arg_start);
    auto args = residual.substr(arg_start);

    return {root_url, args};
}


/**
 * This function is a simple wrapper around http GET request
 * @param url
 * @param args
 * @return pair = status code(int), response body (string)
 */
std::pair<int, std::string> get(const std::string& url, const std::string& args) {
    httplib::Client cli(url);
    auto r = cli.Get(args);
    return {r->status, r->body};
}




#endif //ASYNC_EXAMPLES_UTILS_H
