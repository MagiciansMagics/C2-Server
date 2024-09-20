#ifndef _PROXY_SERVER_REDIRECT_HANDLE_HPP_
#define _PROXY_SERVER_REDIRECT_HANDLE_HPP_

#include "./MAIN_proxy_server_redirect.h"
#include "../proxy_server/MAIN_proxy_checker.h"
#include "../networking/http/DIRECT_TO-PAGE.hpp"
#include "../networking/send_html_files.hpp"

void handleClient_Redirect(const std::string& addr)
{
    size_t client_request_size = CLIENT_REQUEST_BUFFER;
    qnj_pool_t* pool = qnj_create_pool(client_request_size);
    char* buffer = static_cast<char*>(qnj_palloc(pool, 8192));  // Use a buffer of 8KB

    if (!buffer)
    {
        std::cerr << "Allocating for buffer failed" << std::endl;
        qnj_destroy_pool(pool);
        close(qnj_proxy_server_redirect_socket_client);
        return;
    }

    ssize_t bytes_received = recv(qnj_proxy_server_redirect_socket_client, buffer, 8192, 0);  // Adjusted buffer size

    if (bytes_received < 0)
    {
        std::cerr << "[ERROR] Error receiving data from client" << std::endl;
        qnj_destroy_pool(pool);
        close(qnj_proxy_server_redirect_socket_client);
        return;
    }
    else if (bytes_received == 0)
    {
        std::cerr << "[INFO] Client disconnected" << std::endl;
        qnj_destroy_pool(pool);
        close(qnj_proxy_server_redirect_socket_client);
        return;
    }
    else
    {
        std::string full_addr = "http://" + addr + ":" + std::to_string(qnj_bind_proxy_server_port);
        std::string requestHeaders(buffer, bytes_received);

        size_t method_pos = requestHeaders.find(" ");
        if (method_pos != std::string::npos)
        {
            std::string method = requestHeaders.substr(0, method_pos);
            std::transform(method.begin(), method.end(), method.begin(), ::toupper);

            if (method == "GET" || method == "POST")
            {
                size_t start_pos = requestHeaders.find(method) + method.length() + 1;
                size_t end_pos = requestHeaders.find(" HTTP");
                if (end_pos == std::string::npos) {
                    std::cerr << "[ERROR] Malformed HTTP request" << std::endl;
                    qnj_destroy_pool(pool);
                    close(qnj_proxy_server_redirect_socket_client);
                    return;
                }

                std::string path = requestHeaders.substr(start_pos, end_pos - start_pos);
                
                std::string HTTP_RESP_LOCATION_DIRECT = "HTTP/1.1 302 Found\r\n";
                HTTP_RESP_LOCATION_DIRECT += "Location: " + full_addr + "\r\n";
                HTTP_RESP_LOCATION_DIRECT += "Server: QNJ-Proxy\n";
                HTTP_RESP_LOCATION_DIRECT += "Connection: close\r\n\r\n";
                send(qnj_proxy_server_redirect_socket_client, HTTP_RESP_LOCATION_DIRECT.c_str(), HTTP_RESP_LOCATION_DIRECT.size(), 0);
            }
        }
    }

    qnj_destroy_pool(pool);
    close(qnj_proxy_server_redirect_socket_client);
}

void qnj_proxy_server_redirect_handle_setup(const std::string& addr)
{
    std::cout << "Reached redirect handling" << std::endl;
    struct sockaddr_in client_address;
    socklen_t client_address_size = sizeof(client_address);
    while (true)
    {
        qnj_proxy_server_redirect_socket_client = accept(qnj_proxy_server_redirect_socket, (struct sockaddr*)&client_address, &client_address_size);

        if (qnj_proxy_server_redirect_socket_client < 0)
        {
            std::cerr << "[ERROR] Failed accepting client in HTTP proxy server" << std::endl;
            continue;  // Instead of returning, we continue listening for new clients
        }
        else
        {
            std::thread magic([&] { handleClient_Redirect(addr); });
            magic.detach();
        }
    }
}

#endif