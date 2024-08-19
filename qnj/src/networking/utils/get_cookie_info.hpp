#ifndef GET_COOKIE_INFO_HPP
#define GET_COOKIE_INFO_HPP

#include <string>
#include <iostream>

std::string get_cookie(const std::string& cookie_name, const std::string& cookie_data) 
{
    size_t cookie_start = cookie_data.find("Cookie: ");
    if (cookie_start != std::string::npos) 
    {
        cookie_start += std::string("Cookie: ").length();
        size_t cookie_end = cookie_data.find("\r\n", cookie_start);
        if (cookie_end != std::string::npos) 
        {
            std::string cookies = cookie_data.substr(cookie_start, cookie_end - cookie_start);
            size_t pos = 0;
            while ((pos = cookies.find(cookie_name, pos)) != std::string::npos) {
                std::string::size_type value_start = cookies.find("=", pos) + 1;
                if (value_start != std::string::npos && value_start < cookie_end) {
                    std::string::size_type value_end = cookies.find(";", value_start);
                    if (value_end == std::string::npos) {
                        value_end = cookie_end;
                    }
                    std::string cookie_value = cookies.substr(value_start, value_end - value_start);
                    return cookie_value;
                }
                pos = cookies.find(";", pos);
                if (pos != std::string::npos)
                    ++pos;
            }
        }
    }
    return "";
}

#endif