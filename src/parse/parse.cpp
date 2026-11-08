#include "parse.hpp"

void rq::Parse::ParseData(const std::string &str){
    if (!str.empty()){
        if (!this->m_json.empty()){
            this->m_json.clear();
        }
        try{
            this->m_json = Json::parse(str);
            this->set_status(rq::parse_status::ok);
        }catch (...){
            this->set_status(rq::parse_status::error_parse);
        }
    }else{
        this->set_status(rq::parse_status::error);
    }
}

std::expected<bool, rq::parse_status> rq::Parse::IsOk(const Json &json){
    if (this->get_status() == rq::parse_status::ok){
        if (this->m_json.contains("ok")){
            return this->m_json["ok"].get<bool>();
        }else{
            return std::unexpected(rq::parse_status::failed);
        }
    }
    return std::unexpected(this->get_status());
}

std::expected<rq::TgMe, rq::parse_status> rq::Parse::GetParseMe(){
    auto is_ok = this->IsOk(this->m_json);
    if (is_ok.has_value()){
        if (is_ok.value()){
            if (this->m_json.contains("result")){
                Json result = this->m_json["result"];
                return rq::TgMe{
                    .is_status = true,
                    .me = {
                        .is_ok      = true,
                        .id         = result.contains("id")         ? result["id"].get<std::size_t>()         : 0,
                        .is_bot     = result.contains("is_bot")     ? result["is_bot"].get<bool>()            : false,
                        .first_name = result.contains("first_name") ? result["first_name"].get<std::string>() : "unknown",
                        .user_name  = result.contains("username")   ? result["username"].get<std::string>()   : "unknown"
                    }
                };
            }else{
                return std::unexpected(rq::parse_status::failed);
            }
        }else{
            return rq::TgMe{
                .is_status = false,
                .error = {
                    .is_ok       = this->m_json.contains("ok")          ? this->m_json["ok"].get<bool>()                 : false,
                    .error_code  = this->m_json.contains("error_code")  ? this->m_json["error_code"].get<int>()          : -1,
                    .description = this->m_json.contains("description") ? this->m_json["description"].get<std::string>() : "unknown",
                }
            };
        }
    }
    return std::unexpected(is_ok.error());
}

std::expected<rq::TgUpdates, rq::parse_status> rq::Parse::GetParseUpdates(){
    auto is_ok = this->IsOk(this->m_json);
    if (is_ok.has_value()){
        if (is_ok.value()){
            if (this->m_json.contains("result")){
                Json result = this->m_json["result"];
                return rq::TgUpdates{
                    .result = rq::StorUpdates{
                    }
                };
            }
        }else{
            return rq::TgUpdates{
                .result = std::unexpected(rq::TgError{
                })
            };
        }
    }
    return std::unexpected(is_ok.error());
}

void rq::Parse::set_status(const rq::parse_status &ps){
    this->m_status = ps;
}

rq::parse_status rq::Parse::get_status() const{
    return this->m_status;
}
