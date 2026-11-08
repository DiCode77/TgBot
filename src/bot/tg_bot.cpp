//
//  tg_bot.cpp
//  TgBot
//
//  Created by DiCode77.
//

#include "tg_bot.hpp"

void rq::TgBot::Event(std::function<void()> func){
    this->SetFunc(func);
}

bool rq::TgBot::Run(){
    auto res = this->get_tg_me(this->GetToken());
    
    if (res.has_value()){
        this->SetBotStatus(rq::bot::preparation);
        this->SetTgMe(res.value());
    
        std::println("{}", "Bot Initialized!");
        
        std::deque<rq::TgUpdates> tg_updates;
        
        std::mutex mutex;
        std::condition_variable co_var;
        std::future<std::expected<bool, rq::bot>> future = std::async(std::launch::async, &rq::TgBot::get_updates, this, std::ref(mutex), this->GetToken(), std::ref(tg_updates));
        
        while (true){
           ///
        }
        
    }else{
        std::println("{}", "The bot has not been initialized");
    }
}

std::expected<rq::StorMe, rq::bot> rq::TgBot::get_tg_me(const std::string &token){
    std::expected<rq::request_data, rq::request_status> res_me = std::unexpected(rq::request_status::none);
    bool is_connect = true;
    
    while(!res_me.has_value()){
        res_me = this->RequestUrl(rq::Combine(rq::url::api).Add(token).Add(rq::url::me));
        if (!res_me.has_value()){
            is_connect = false;
            this->ShowRequestLog(res_me.error());
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        }else{
            if (is_connect == true){
                this->ShowRequestLog(rq::request_status::ok);
            }else{
                this->ShowRequestLog(rq::request_status::ok, "The connection to the server has been restored!");
            }
        }
    }

    if (res_me.has_value()){
        auto res_parse = rq::Parse(res_me.value().request).GetParseMe();
        
        if (res_parse.has_value()){
            if (res_parse.value().is_status){
                return res_parse.value().me;
            }else{
                return std::unexpected(rq::bot::request_error_code);
            }
        }else{
            return std::unexpected(rq::bot::parse_error);
        }
    }
    return std::unexpected(rq::bot::request_error);
}

std::expected<bool, rq::bot> rq::TgBot::get_updates(std::mutex &mutex, const std::string &token, std::deque<rq::TgUpdates> &tg_updates){
    std::expected<rq::request_data, rq::request_status> res_get_upd = this->RequestUrl(rq::Combine(rq::url::api).Add(token).Add(rq::url::update));
    
    if (res_get_upd.has_value()){
        if (res_get_upd.value().code == 0){
            while (true) {
                ///
            }
        }else{
            return std::unexpected(rq::bot::request_error_code);
        }
    }else{
        return std::unexpected(rq::bot::request_error);
    }
    
    return true;
}
