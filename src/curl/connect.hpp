//
//  connect.hpp
//  TgBot
//
//  Created by DiCode77.
//

#ifndef CONNECT_HEADER
#define CONNECT_HEADER

#include <curl/curl.h>
#include <string>
#include <expected>
#include <print>

namespace rq{
enum class request_status{
    none,
    ok,
  //  ok_failed, // ?
    easy_init_failed,
    global_init_failed,
    connection_failed,
    connection_time_out,
};


struct request_data{
    int         code = {};
    std::string request;
};

class Request{
public:
    Request(){}
    void ClearResources();
    void ShowRequestLog(const rq::request_status&, const std::string& = "");
    std::expected<rq::request_data, rq::request_status> RequestUrl(const std::string&);
};
}

#endif
