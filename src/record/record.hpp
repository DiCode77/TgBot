//
//  record.cpp
//  TgBot
//
//  Created by DiCode77.
//

#ifndef RECORD_HEDAER
#define RECORD_HEDAER

#include <string>
#include <deque>
#include <functional>

#include "structs.hpp"

namespace rq{

enum class bot{
    none,
    preparation,
    launched,
    completed,
    error,
    request_error,
    request_error_code,
    parse_error
};

struct Action{
    std::string                       m_token;
    std::deque<std::function<void()>> m_func;
};

class RecordSet{
    rq::Action m_action;
    rq::StorMe m_tg_me;
    rq::bot    m_bot_status = rq::bot::none;
public:
    virtual ~RecordSet() = default;
    
    void SetToken(const std::string_view &str);
    void SetFunc(const std::function<void()> func);
    void SetTgMe(const StorMe &me);
    void SetBotStatus(const rq::bot &info);
    
    std::string GetToken() const;
    std::deque<std::function<void()>> &GetFunc();
    rq::StorMe GetTgMe();
    rq::bot GetBotStatus() const;
};
};

#endif
