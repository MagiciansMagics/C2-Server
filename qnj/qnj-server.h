#ifndef _QNJ_SERVER_H
#define _QNJ_SERVER_H

#include <string>
#include <iostream>
#include <thread>
#include <iostream>
#include <fstream>
#include "./src/server_1/MAIN_server.hpp"
#include "./src/server_1/MAIN_handle_client.hpp"
#include "./src/server_2/TCP_server.hpp"
#include "./src/server_2/TCP_handle_client.hpp"
#include "./config/json/json_config_loader.hpp"

void listen(const std::string& address, const int port)
{
    std::cout << "[+] HTTP Server listening on: " << address << ":" << port << "\n";
    SERVER_MAIN_QNJ();
    BIND_SERVER_QNJ(address, port);
    LISTEN_SERVER_QNJ();
    CLIENTM_main_server_hpp(QNJ_Main_server_socket);
}

void tcp_listen(const std::string& address, const int port)
{
    std::cout << "[+] TCP Server listening on: " << address << ":" << port << "\n";
    QNJ_TCP_MAIN_SOCKET();
    QNJ_TCP_BIND_SOCKET(address, port);
    QNJ_TCP_LISTEN_SOCKET();
    QNJ_TCP_HANDLE_CLIENTS(QNJ_TCP_Main_server_socket);
}

void start_both_servers(const std::string& http_ip, const int http_port, const std::string& tcp_ip, const int tcp_port)
{
    std::thread load_json_config_files([&]() { load_json_configs(); });
    sleep(0.7);
    std::thread http_thread([&]() { listen(http_ip, http_port); });
    sleep(1);
    std::thread tcp_thread([&]() { tcp_listen(tcp_ip, tcp_port); });

    load_json_config_files.join();
    http_thread.join();
    tcp_thread.join();
}

#endif