#ifndef _MAIN_PROXY_SERVER_HTTP_HPP_
#define _MAIN_PROXY_SERVER_HTTP_HPP_

#include "./MAIN_proxy_server_http.h"

void qnj_http_proxy_server_setup()
{
    qnj_http_server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (qnj_http_server_socket == -1)
    {
        std::cout << "[ERR_PROXY_SERVER_HTTP_SOCKET]" << std::endl;
        perror("");
        close(qnj_http_server_socket);
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(qnj_http_server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        std::cerr << "[ERR_PROXY_SERVER_SETSOCKOPT] Failed to set socket options" << std::endl;
        perror("Setsockopt failed");
        close(qnj_http_server_socket);
        exit(EXIT_FAILURE);
    }
}

void qnj_http_proxy_server_bind(const std::string http_addr)
{
    if (!qnj_bind_server(qnj_http_server_socket, http_addr))
    {
        std::cout << "[ERR_PROXY_SERVER_HTTP_BIND]" << std::endl;
        perror("");
        close(qnj_http_server_socket);
    }

    std::cout << "Binding http proxy server was successful" << std::endl;
}

void qnj_http_proxy_server_listen()
{
    if (listen(qnj_http_server_socket, 5) == -1)
    {
        std::cout << "[ERR_PROXY_SERVER_HTTP_LISTEN]" << std::endl;
        perror("");
        close(qnj_http_server_socket);
        exit(EXIT_FAILURE);
    }
}

#endif