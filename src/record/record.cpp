#include "record.hpp"

void rq::RecordSet::SetToken(const std::string_view &str){
    this->m_action.m_token.assign(str);
}

void rq::RecordSet::SetFunc(const std::function<void()> func){
    this->m_action.m_func.push_back(std::move(func));
}

void rq::RecordSet::SetTgMe(const rq::StorMe &me){
    this->m_tg_me = me;
}

void rq::RecordSet::SetBotStatus(const rq::bot &info){
    this->m_bot_status = info;
}

std::string rq::RecordSet::GetToken() const{
    return this->m_action.m_token;
}

std::deque<std::function<void()>> &rq::RecordSet::GetFunc(){
    return this->m_action.m_func;
}

rq::StorMe rq::RecordSet::GetTgMe(){
    return this->m_tg_me;
}

rq::bot rq::RecordSet::GetBotStatus() const{
    return this->m_bot_status;
}
