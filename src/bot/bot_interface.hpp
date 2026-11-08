//
//  bot_interface.cpp
//  TgBot
//
//  Created by DiCode77.
//

#ifndef BOT_INTERFACE_HEADER
#define BOT_INTERFACE_HEADER

#include "record.hpp"
#include "connect.hpp"
#include "parse.hpp"

namespace rq{
class BotInterface : protected rq::RecordSet, protected rq::Request{
public:
    virtual ~BotInterface() = default;
    virtual void Event(std::function<void()>) = 0;
};
};

#endif
