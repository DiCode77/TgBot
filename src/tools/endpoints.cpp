//
//  endpoints.cpp
//  TgBot
//
//  Created by DiCode77.
//

#include "endpoints.hpp"

rq::Combine::Combine(){
    this->m_um_endpoints = {
        { rq::url::api,    "https://api.telegram.org/" },
        { rq::url::update, "/getUpdates" },
        { rq::url::me,     "/getMe" }
    };
}

rq::Combine::Combine(const std::string &str) : Combine(){
    this->m_url.assign(str);
}

rq::Combine::Combine(const rq::url &en) : Combine(){
    this->Add(en);
}

rq::Combine::Combine(const Combine &cme) : Combine(){
    this->m_url.assign(cme.m_url);
}

rq::Combine::Combine(Combine &&r_cme) : Combine(){
    this->m_url.assign(std::move(r_cme.m_url));
}

rq::Combine &rq::Combine::Add(const std::string &str){
    this->m_url.append(str);
    return *this;
}

rq::Combine &rq::Combine::Add(const rq::url &en){
    if (auto it = this->m_um_endpoints.find(en); it != this->m_um_endpoints.end()){
        this->m_url.append(it->second);
    }
    return *this;
}

std::string rq::Combine::GetUrl() const{
    return this->m_url;
}

rq::Combine::operator std::string() const{
    return this->m_url;
}

std::ostream& rq::operator << (std::ostream &out, const rq::Combine &in){
    return (out << in.m_url.c_str());
}
