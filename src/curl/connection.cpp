//
//  connection.cpp
//  TgBot
//
//  Created by DiCode77.
//

#include "connection.hpp"

std::size_t ResponsetoString(void* contents, size_t size, size_t nmemb, void* userp){
    ((std::u32string*)userp)->append((char32_t*)contents, size * nmemb);
    return size *nmemb;
}

void rq::Request::ClearResources(){
    curl_global_cleanup();
}

std::expected<std::string, rq::request_status> rq::Request::RequestUrl(const std::string &url){
    CURL              *curl     = curl_easy_init();
    CURLcode           response = curl_global_init(CURL_GLOBAL_ALL);
    std::string        request;
    rq::request_status status   = rq::request_status::none;
    
    if (curl != nullptr){
        if (response == CURLE_OK){
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ResponsetoString);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &request);
            
            response = curl_easy_perform(curl);
            status   = (response != CURLE_OK) ? rq::request_status::no_connection : rq::request_status::ok;
        }else{
            status = rq::request_status::no_global_init;
        }
        
        curl_easy_cleanup(curl);
        if (status == rq::request_status::ok){
            return request;
        }
    }else{
        status = rq::request_status::no_easy_init;
    }
    return std::unexpected(status);
}
