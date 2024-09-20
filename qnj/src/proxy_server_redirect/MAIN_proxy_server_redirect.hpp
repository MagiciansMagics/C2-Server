#ifndef _MAIN_PROXY_SERVER_REDIRECT_HPP_
#define _MAIN_PROXY_SERVER_REDIRECT_HPP_

#include "../qnj_config.h"
#include "./MAIN_proxy_server_redirect.h"
#include "../proxy_server/MAIN_proxy_server_http_handle.h"
#include "./proxy_server_redirect_handle.hpp"

void qnj_proxy_server_redirect_to_backup_server(const std::string& http_addr, int http_port)
{
    std::cout << "Starting proxy redirecting server" << std::endl;

    qnj_proxy_server_redirect_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (qnj_proxy_server_redirect_socket < 0)
    {
        std::cerr << "[ERR_PROXY_REDIRECT_SOCKET_FAILED]" << std::endl;
        perror("socket error");
        exit(1);
    }

    int opt = 1;
    
    // Enable SO_REUSEADDR
    if (setsockopt(qnj_proxy_server_redirect_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        std::cerr << "[ERR_PROXY_SERVER_SETSOCKOPT] Failed to set SO_REUSEADDR" << std::endl;
        perror("Setsockopt SO_REUSEADDR failed");
        close(qnj_proxy_server_redirect_socket);
        exit(EXIT_FAILURE);
    }

    // Enable SO_REUSEPORT
    if (setsockopt(qnj_proxy_server_redirect_socket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0)
    {
        std::cerr << "[ERR_PROXY_SERVER_SETSOCKOPT] Failed to set SO_REUSEPORT" << std::endl;
        perror("Setsockopt SO_REUSEPORT failed");
        close(qnj_proxy_server_redirect_socket);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    std::memset(&server_address, 0, sizeof(server_address)); // Clear the structure
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(http_addr.c_str());
    server_address.sin_port = htons(http_port);

    if (bind(qnj_proxy_server_redirect_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        std::cerr << "[ERR_PROXY_REDIRECT_BIND_FAILED]" << std::endl;
        std::cerr << "Bind failed: " << strerror(errno) << std::endl;
        perror("bind error");
        close(qnj_proxy_server_redirect_socket);
        exit(1);
    }

    if (listen(qnj_proxy_server_redirect_socket, 5) < 0)
    {
        std::cerr << "[ERR_PROXY_REDIRECT_LISTEN_FAILED]" << std::endl;
        perror("listen error");
        close(qnj_proxy_server_redirect_socket);
        exit(1);
    }

    std::cout << "Proxy redirecting server started successfully" << std::endl;
    qnj_proxy_server_redirect_handle_setup(http_addr);
}

#endif