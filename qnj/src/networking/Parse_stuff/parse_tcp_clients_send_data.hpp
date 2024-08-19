#ifndef PARSE_TCP_CLIENTS_SEND_DATA_HPP
#define PARSE_TCP_CLIENTS_SEND_DATA_HPP
#include <iostream>
#include <string>
#include <sstream>

void parseClientData(const std::string& data, std::string& ip, std::string& os, std::string& osRelease, std::string& architecture) {
    size_t firstDelim = data.find('&');
    if (firstDelim != std::string::npos) 
    {
        ip = data.substr(0, firstDelim);

        size_t secondDelim = data.find('&', firstDelim + 1);
        if (secondDelim != std::string::npos) 
        {
            os = data.substr(firstDelim + 1, secondDelim - firstDelim - 1);

            size_t thirdDelim = data.find('&', secondDelim + 1);
            if (thirdDelim != std::string::npos) 
            {
                osRelease = data.substr(secondDelim + 1, thirdDelim - secondDelim - 1);
                architecture = data.substr(thirdDelim + 1);
            } 
            else 
            {
                osRelease = data.substr(secondDelim + 1);
            }
        }
    }
}
#endif