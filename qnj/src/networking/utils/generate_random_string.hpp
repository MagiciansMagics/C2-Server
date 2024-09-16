#ifndef _GENERATE_RANDOM_STRING_HPP_
#define _GENERATE_RANDOM_STRING_HPP_
#include "../send_html_client_side.hpp"

std::string generate_random_string(int length)
{
    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::mt19937 rng(std::random_device{}()); // random number generator
    std::uniform_int_distribution<std::string::size_type> dist(0, chars.length() - 1);

    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result.push_back(chars[dist(rng)]);
    }
    return result;
}
#endif