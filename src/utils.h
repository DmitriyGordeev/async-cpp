#ifndef ASYNC_EXAMPLES_UTILS_H
#define ASYNC_EXAMPLES_UTILS_H

#include <string>
using std::string;


std::pair<std::string, std::string> split_url(const std::string& url) {
    size_t double_slash = url.find("://");
    if (double_slash == string::npos) {
        return {"", ""};
    }

    auto residual = url.substr(double_slash + 3);
    size_t arg_start = residual.find('/');
    if (arg_start == string::npos || arg_start == residual.size() - 1) {
        return {residual, ""};
    }
    auto root_url = residual.substr(0, arg_start);
    auto args = residual.substr(arg_start);

    return {root_url, args};
}


#endif //ASYNC_EXAMPLES_UTILS_H
