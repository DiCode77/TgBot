//
//  endpoints.cpp
//  TgBot
//
//  Created by DiCode77.
//

#ifndef ENDPOINTS_HEDER
#define ENDPOINTS_HEDER

#include <unordered_map>
#include <string>
#include <ostream>

namespace rq {
enum class url{
    none,
    api,
    update,
    me
};

class Combine{
    std::unordered_map<rq::url, std::string> m_um_endpoints;
    std::string m_url;
public:
    Combine();
    Combine(const std::string&);
    Combine(const rq::url&);
    Combine(const Combine&);
    Combine(Combine&&);
    
    Combine &Add(const std::string &str);
    Combine &Add(const rq::url &en);
    
    std::string GetUrl() const;
    
    operator std::string() const;
    friend std::ostream& operator << (std::ostream&, const Combine&);
};

}

#endif
