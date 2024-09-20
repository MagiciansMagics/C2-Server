#ifndef _MAIN_PROXY_SERVER_HTTP_HANDLE_HPP_
#define _MAIN_PROXY_SERVER_HTTP_HANDLE_HPP_

#include "../qnj_config.h"
#include "./MAIN_proxy_server_http_handle.h"
#include "./MAIN_proxy_server_http.h"
#include "../networking/send_html_files.hpp"
#include <algorithm>  // for std::transform
#include <iostream>   // for std::cerr, std::cout
#include <cstring>    // for memset
#include <sys/socket.h> // for recv, close

void handleClient()
{
    size_t client_request_size = CLIENT_REQUEST_BUFFER;
    qnj_pool_t* pool = qnj_create_pool(client_request_size);
    char* buffer = static_cast<char*>(qnj_palloc(pool, 8192));  // Use a buffer of 8KB

    if (!buffer)
    {
        std::cerr << "Allocating for buffer failed" << std::endl;
        qnj_destroy_pool(pool);
        close(qnj_proxy_server_client_socket);
        return;
    }

    ssize_t bytes_received = recv(qnj_proxy_server_client_socket, buffer, 8192, 0);  // Adjusted buffer size

    if (bytes_received < 0)
    {
        std::cerr << "[ERROR] Error receiving data from client" << std::endl;
        qnj_destroy_pool(pool);
        close(qnj_proxy_server_client_socket);
        return;
    }
    else if (bytes_received == 0)
    {
        std::cerr << "[INFO] Client disconnected" << std::endl;
        qnj_destroy_pool(pool);
        close(qnj_proxy_server_client_socket);
        return;
    }
    else
    {
        std::string requestHeaders(buffer, bytes_received);

        size_t method_pos = requestHeaders.find(" ");
        if (method_pos != std::string::npos)
        {
            std::string method = requestHeaders.substr(0, method_pos);
            std::transform(method.begin(), method.end(), method.begin(), ::toupper);

            if (method == "GET" || method == "POST")
            {
                size_t start_pos = requestHeaders.find(method) + method.length() + 1;
                size_t end_pos = requestHeaders.find("HTTP") - 1;
                if (end_pos == std::string::npos) {
                    std::cerr << "[ERROR] Malformed HTTP request" << std::endl;
                    qnj_destroy_pool(pool);
                    close(qnj_proxy_server_client_socket);
                    return;
                }

                std::string path = requestHeaders.substr(start_pos, end_pos - start_pos);
                
                if (path == "/")
                {
                    send_html_file("/home/magician/Desktop/QNJ/web-gui/proxy.html", "text/html", "503 Service Unavailable", "HTTP/1.1", qnj_proxy_server_client_socket);
                }
                else if (path == "/QNJ-Cloud/assets/png/home-white.png" || path == "/QNJ-Cloud/assets/png/home-white.png/")
                {
                    send_html_file("/home/magician/Desktop/QNJ/QNJ-Cloud/assets/png/home-white.png", "image/png", "200 OK", "HTTP/1.1", qnj_proxy_server_client_socket);
                }
                else
                {
                    send_html_file("/home/magician/Desktop/QNJ/web-gui/404.html", "text/html", "404 Not Found", "HTTP/1.1", qnj_proxy_server_client_socket);
                }
            }
        }
    }

    // Clean up memory pool only after all memory allocations are done
    qnj_destroy_pool(pool);
    close(qnj_proxy_server_client_socket);
}

void qnj_proxy_http_server_handle_client_socket()
{
    while (true)
    {
        struct sockaddr_in client_address;
        socklen_t client_address_size = sizeof(client_address);
        qnj_proxy_server_client_socket = accept(qnj_http_server_socket, (struct sockaddr*)&client_address, &client_address_size);

        if (qnj_proxy_server_client_socket < 0)
        {
            std::cerr << "[ERROR] Failed accepting client in HTTP proxy server2" << std::endl;
            close(qnj_proxy_server_client_socket);
            continue;  // Instead of returning, we continue listening for new clients
        }
        else
        {
            handleClient();
        }
    }
}

#endif