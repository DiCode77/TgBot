//
//  tg_bot.cpp
//  TgBot
//
//  Created by DiCode77.
//

#ifndef TG_BOT_HEADER
#define TG_BOT_HEADER

#include <string>
#include <functional>
#include <deque>

#include "bot_interface.hpp"

#include <future>
#include <thread>
#include <mutex>

#include <iostream>

#include "combine.hpp"

namespace rq{

enum class error_code{
    seccess,         // 200
    inncorect_key,   // 402
    repeat_request,  // 303
    invalid_request, // 400
    unauthorized,    // 401
    prohibited,      // 403
    not_found,       // 404
    not_accepted,    // 406
    exceeded,        // 420
    server_error     // 500
};

class TgBot final : private rq::BotInterface{
public:
    TgBot(){}
    TgBot(const char *str){
        this->SetToken(str);
    }
    TgBot(const std::string &str) : TgBot(str.c_str()){}
    
    void Event(std::function<void()>) override;
    
    bool Run();
    
private:
    std::expected<rq::StorMe, rq::bot> get_tg_me(const std::string&);
    std::expected<bool, rq::bot> get_updates(std::mutex&, const std::string&, std::deque<rq::TgUpdates>&);
    
};
};

#endif
