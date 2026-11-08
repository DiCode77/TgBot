//
//  connect.cpp
//  TgBot
//
//  Created by DiCode77.
//

#include "connect.hpp"

std::size_t ResponsetoString(void* contents, size_t size, size_t nmemb, void* userp){
    ((std::u32string*)userp)->append((char32_t*)contents, size * nmemb);
    return size *nmemb;
}

void rq::Request::ClearResources(){
    curl_global_cleanup();
}

void rq::Request::ShowRequestLog(const rq::request_status &en, const std::string &str){
    switch (en) {
        case rq::request_status::none:
            std::println("{}", str.empty() ? "Status is undefined!" : str);
            break;
        case rq::request_status::ok:
            std::println("{}", str.empty() ? "The request was successful!" : str);
            break;
        case rq::request_status::easy_init_failed:
            std::println("{}", str.empty() ? "An error occurred while creating the `curl_easy` object!" : str);
            break;
        case rq::request_status::global_init_failed:
            std::println("{}", "", str);
            break;
        case rq::request_status::connection_failed:
            std::println("{}", str.empty() ? "The server is not responding!" : str);
            break;
        default:
            std::println("{}", str.empty() ? "Status unknown!" : str);
            break;
    }
}

std::expected<rq::request_data, rq::request_status> rq::Request::RequestUrl(const std::string &url){
    CURL               *curl    = curl_easy_init();
    CURLcode           response = CURLE_UNSUPPORTED_PROTOCOL;
    std::string        request;
    rq::request_status status   = rq::request_status::none;
    
    if (curl != nullptr){
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ResponsetoString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &request);
            
        response = curl_easy_perform(curl);
        status   = (response != CURLE_OK) ? rq::request_status::connection_failed : rq::request_status::ok;
        
        curl_easy_cleanup(curl);
        if (status == rq::request_status::ok){
            return rq::request_data{
                .code    = static_cast<int>(response),
                .request = request
            };
        }
    }else{
        status = rq::request_status::easy_init_failed;
    }
    return std::unexpected(status);
}
