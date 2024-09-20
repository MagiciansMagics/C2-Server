#ifndef _MAIN_BEACON_CHECKER_HPP_
#define _MAIN_BEACON_CHECKER_HPP_
#include "../qnj_config.h"
#include "./MAIN_proxy_server_http.hpp"
#include "./MAIN_proxy_server_http_handle.hpp"
#include "./MAIN_proxy_checker.h"
#include "../proxy_server_redirect/MAIN_proxy_server_redirect.hpp"

void qnj_proxy_set_up_socket_http()
{
    QNJ_proxy_client_server_socket_http = socket(AF_INET, SOCK_STREAM, 0);

    if (QNJ_proxy_client_server_socket_http == -1)
    {
        std::cout << "QNJ Proxy server socket failed" << std::endl;
    }
}

bool qnj_proxy_set_check_server_alive(int target_socket, const std::string& addr, int port)
{

    if (target_socket >= 0) 
    {
        close(target_socket);
        std::cout << "Closed existing connection." << std::endl;
    }

    // Create a new socket
    target_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (target_socket < 0) 
    {
        perror("Socket creation failed");
        return false;
    }
    client_address.sin_addr.s_addr = inet_addr(addr.c_str());
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(port);

    // Connect to remote serve

    char buffer[buffer_max];

    std::string user_header = 
    "GET / HTTP/1.1\r\n"
    "User-Agent: MyCustomClient/1.0\r\n"
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"
    "Accept-Language: en-US,en;q=0.5\r\n"
    "Accept-Encoding: gzip, deflate, br\r\n"
    "Connection: keep-alive\r\n"
    "Upgrade-Insecure-Requests: 1\r\n"
    "\r\n";

    if (connect(target_socket, (struct sockaddr *)&client_address, sizeof(client_address)) < 0)
    {
        return false;
    }

    if (send(target_socket, user_header.c_str(), user_header.length(), 0) < 0)
    {
        std::cerr << "Failed to send data.\n";
        return false;
    }

    // Receive the response in chunks
    std::string recv_header;
    int recv_len;

    recv_len = recv(target_socket, buffer, buffer_max - 1, 0);
    if (recv_len < 0)
    {
        std::cerr << "Failed to receive data.\n";
        return false;
    }
    else if (recv_len == 0)
    {
        std::cout << "Connection closed by the server.\n";
        return false;
    }
    else
    {
        buffer[recv_len] = '\0'; // Null-terminate the received data
        recv_header += std::string(buffer, recv_len);
    }

    // Now check if "Server: QNJ-Cloud" is in the header

    if (recv_header.find("Server: QNJ-Cloud") != std::string::npos)
    {
        return true;
    }

    // Return false if the specific server string is not found
    return false;
}

void qnj_proxy_server_start_http(const std::string& http_addr) {
    qnj_http_proxy_server_setup();
    qnj_http_proxy_server_bind(http_addr);
    qnj_http_proxy_server_listen();
    qnj_proxy_http_server_handle_client_socket();
}

void qnj_proxy_check_http_connection(const std::string& http_addr, int http_port) {
    bool if_back_already_started = false;

    while (1) {
        if (qnj_proxy_set_check_server_alive(QNJ_proxy_client_server_socket_http, http_addr, http_port)) {
            std::cout << "Connection was successful to HTTP server at " << http_addr << ":" << http_port << std::endl;

            // Trigger terminate for backup server if it's running
            if (if_back_already_started) 
            {
                std::cout << "Main server is back online. Terminating backup server." << std::endl;
            }

            sleep(5);
        } 
        else 
        {
            if (!if_back_already_started) 
            {
                std::cout << "Starting backup server..." << std::endl;

                // Start the backup server as a detached thread

                std::thread([&]() {
                    qnj_proxy_server_start_http(http_addr);
                }).detach();


                std::thread([&]() {
                    qnj_proxy_server_redirect_to_backup_server(http_addr, http_port);
                }).detach();

                if_back_already_started = true;
            }

            std::cout << "Trying again" << std::endl;

            sleep(5);
        }
    }
}

void qnj_proxy_check_tcp_connection(const std::string tcp_addr, int tcp_port)
{
    if (qnj_proxy_set_check_server_alive(QNJ_proxy_client_server_socket_tcp, tcp_addr, tcp_port) == true)
    {
        std::cout << "Connection was successful to tcp server" << std::endl;
    }
    else if (qnj_proxy_set_check_server_alive(QNJ_proxy_client_server_socket_tcp, tcp_addr, tcp_port) == false)
    {
        std::cout << "Connection failed to tcp server" << std::endl;
    }
}

void qnj_proxy_set_up_socket_tcp()
{
    QNJ_proxy_client_server_socket_tcp = socket(AF_INET, SOCK_STREAM, 0);

    if (QNJ_proxy_client_server_socket_tcp == -1)
    {
        std::cout << "QNJ Proxy server socket failed" << std::endl;
    }
}

#endif