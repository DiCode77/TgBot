//
//  parse.cpp
//  TgBot
//
//  Created by DiCode77.
//

#ifndef PARSE_HEADER
#define PARSE_HEADER

#include <expected>
#include <nlohmann/json.hpp>

#include "structs.hpp"

namespace rq{

enum class parse_status{
    none,
    ok,
    failed,
    error,
    error_parse
};

struct tg_status{
    bool        status     = false;
    std::size_t error_code = 0;
    std::string description;
};

class Parse{
    using Json   = nlohmann::json;
    using Json_t = Json::basic_json::value_type;
    
    Json  m_json;
    rq::parse_status m_status;
public:
    Parse() : m_status(rq::parse_status::none){}
    Parse(const std::string &str) : Parse(){
        this->ParseData(str);
    }
    
    void ParseData(const std::string &str);
    std::expected<bool, rq::parse_status> IsOk(const Json &json);
    std::expected<rq::TgMe, rq::parse_status> GetParseMe();
    std::expected<rq::TgUpdates, rq::parse_status> GetParseUpdates();
    
private:
    void set_status(const rq::parse_status &ps);
    rq::parse_status get_status() const;
};
};

#endif
