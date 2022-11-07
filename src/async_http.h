#ifndef ASYNC_EXAMPLES_ASYNC_HTTP_H
#define ASYNC_EXAMPLES_ASYNC_HTTP_H

#include <string>

class async_http {
public:
    static void async_get(const std::string& url, const std::string& path);
};


#endif //ASYNC_EXAMPLES_ASYNC_HTTP_H
