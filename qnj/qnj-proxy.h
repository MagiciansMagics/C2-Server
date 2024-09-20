#ifndef _QNJ_BEACON_H_
#define _QNJ_BEACON_H_

#include "./src/qnj_config.h"
#include "./src/proxy_server/MAIN_proxy_checker.hpp"

void start_http_proxy(const std::string& http_addr, int http_port)
{
    qnj_proxy_set_up_socket_http();
    qnj_proxy_check_http_connection(http_addr, http_port);
}

void start_tcp_proxy(const std::string& tcp_addr, int tcp_port)
{
    qnj_proxy_set_up_socket_tcp();
    qnj_proxy_check_tcp_connection(tcp_addr, tcp_port);
}

void start_qnj_proxy(const std::string& http_addr, int http_port, const std::string& tcp_addr, int tcp_port)
{
    std::thread start_http_server_proxy([&]() { start_http_proxy(http_addr, http_port); });
    sleep(0.7);
    std::thread start_tcp_server_proxy([&]() { start_tcp_proxy(tcp_addr, tcp_port); });
    sleep(0.7);

    start_http_server_proxy.join();
    start_tcp_server_proxy.join();
}

#endif