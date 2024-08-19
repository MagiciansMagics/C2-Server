#ifndef _REPLACE_CHARACTERS_HPP_
#define _REPLACE_CHARACTERS_HPP_
#include <iostream>
#include <string>
#include <cstring>

void replace_char(std::string& str, const std::string& from, const std::string& to) 
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

#endif