#ifndef _QNJ_BEACON_H_
#define _QNJ_BEACON_H_

#include <string>
#include <iostream>
#include <thread>
#include <iostream>
#include <fstream>
#include "./src/proxy_server/MAIN_proxy_checker.hpp"

void start_qnj_proxy(const std::string& http_addr, const int http_port, const std::string& tcp_addr, const int tcp_port)
{
    std::cout << "QNJ-Beacon has been started" << "\n";
}

#endif