//
//  connection.hpp
//  TgBot
//
//  Created by DiCode77.
//

#ifndef CONNECTION_HEADER
#define CONNECTION_HEADER

#include <curl/curl.h>
#include <string>
#include <expected>

namespace rq{
enum class request_status{
    none,
    ok,
    no_easy_init,
    no_global_init,
    no_connection,
};

class Request{
public:
    Request(){}
    void ClearResources();
    std::expected<std::string, rq::request_status> RequestUrl(const std::string&);
};
}

#endif
