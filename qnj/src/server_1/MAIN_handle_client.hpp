#ifndef MAIN_HANDLE_CLIENT_HPP
#define MAIN_HANDLE_CLIENT_HPP

#include "../qnj_config.h"
#include "./MAIN_handle_client.h"
#include "../memory/qnj_alloc.hpp"
#include "../memory/qnj_memory_pool.hpp"
#include "../memory/qnj_memcpy.hpp"
#include "./paths.hpp"
#include "../time_util.h"
#include "../networking/send_html_files.hpp"
#include "../networking/utils/get_cookie_info.hpp"
#include "../json/make_database_json.hpp"
#include "../json/save_user_public_addr.hpp"
#include "../json/save_user_remote_addr.hpp"
#include "../json/save_http_requests.hpp"

#define CLIENT_REQUEST_BUFFER 2048

std::string getHeader(const std::string& headerName, const std::string& requestHeaders) {
    std::string headerValue;
    size_t pos = requestHeaders.find(headerName + ": ");
    if (pos != std::string::npos) {
        size_t end = requestHeaders.find("\r\n", pos);
        headerValue = requestHeaders.substr(pos + headerName.length() + 2, end - pos - headerName.length() - 2);
    }
    return headerValue;
}

void handleClient(int client_socket, struct sockaddr_in client_address) {
    size_t client_request_size = 8192;

    qnj_pool_t* pool = qnj_create_pool(client_request_size);
    char* buffer = static_cast<char*>(qnj_palloc(pool, 2048));

    if (!buffer)
    {
        std::cout << "Allocating for buffer failed" << std::endl;
        qnj_destroy_pool(pool);
        return;
    }
    
    ssize_t bytes_received = recv(client_socket, buffer, CLIENT_REQUEST_BUFFER, 0);
    if (bytes_received < 0)
    {
        std::cerr << "[ERROR] Error receiving data from client" << std::endl;
        qnj_destroy_pool(pool);
        close(client_socket);
        return;
    }
    else if (bytes_received == 0)
    {
        std::cerr << "[INFO] Client disconnected" << std::endl;
        qnj_destroy_pool(pool);
        close(client_socket);
        return;
    }
    else
    {
        std::string requestHeaders(buffer);
        size_t method_pos = requestHeaders.find(" ");
        if (method_pos != std::string::npos)
        {
            std::string method = requestHeaders.substr(0, method_pos);
            std::transform(method.begin(), method.end(), method.begin(), ::toupper);
            if (method == "GET" || method == "POST")
            {
                size_t http_version_start = requestHeaders.find("HTTP/") + 5; // Find the start position of HTTP version
                size_t http_version_end = requestHeaders.find("\r\n", http_version_start); // Find the end position of HTTP version
                std::string http_version = requestHeaders.substr(http_version_start, http_version_end - http_version_start);
                std::string first_part_http_data = std::string(inet_ntoa(client_address.sin_addr)) + " - - " + execute_get_time() + "\"" + method + "";

                size_t start_pos = requestHeaders.find(method) + method.length() + 1; // Move past method and one space
                size_t end_pos = requestHeaders.find("HTTP") - 1;
                std::string path = requestHeaders.substr(start_pos, end_pos - start_pos);
                std::string second_part_http_data = " " + path + " HTTP/" + http_version + "\" ";

                save_http_requests_data(first_part_http_data, second_part_http_data);

                request_amount += 1;
                std::string time_variable = execute_get_time();
                save_server_data_json(request_amount);
                
                std::string xForwardedFor = getHeader("X-Forwarded-For", requestHeaders);
                std::string Remote_address = inet_ntoa(client_address.sin_addr);

                save_user_address_remote(Remote_address);

                save_user_address_public(xForwardedFor);

                userIdCookieValue = get_cookie("session_id", requestHeaders);
                data0x00UserIdCookieValue = get_cookie("session_data_0x00", requestHeaders);

                path_handler(method, path, client_socket, userIdCookieValue, data0x00UserIdCookieValue, requestHeaders);
            }
            else
            {
                std::cout << "Unsupported method" << std::endl;
            }
        }
    }

    qnj_destroy_pool(pool);
    close(client_socket);
}

void CLIENTM_main_server_hpp(int QNJ_Main_server_socket) {
    fd_set master_set, working_set;
    FD_ZERO(&master_set);
    FD_SET(QNJ_Main_server_socket, &master_set);
    int max_sd = QNJ_Main_server_socket;

    std::map<int, sockaddr_in> client_addresses;

    while (true) {
        qnj_memcpy(&working_set, &master_set, sizeof(master_set));

        int activity = select(max_sd + 1, &working_set, nullptr, nullptr, nullptr);
        if (activity < 0 && errno != EINTR) {
            std::cerr << "[ERROR] Select error" << std::endl;
            break;
        }

        for (int i = 0; i <= max_sd; ++i) {
            if (FD_ISSET(i, &working_set)) {
                if (i == QNJ_Main_server_socket) {
                    struct sockaddr_in client_address;
                    socklen_t client_address_size = sizeof(client_address);
                    int client_socket = accept(QNJ_Main_server_socket, (struct sockaddr*)&client_address, &client_address_size);
                    if (client_socket < 0) {
                        std::cerr << "[ERROR] Failed to accept client connection" << std::endl;
                        continue;
                    }

                    FD_SET(client_socket, &master_set);
                    if (client_socket > max_sd) max_sd = client_socket;

                    client_addresses[client_socket] = client_address;
                } 
                else 
                {
                    handleClient(i, client_addresses[i]);
                    FD_CLR(i, &master_set);
                    close(i);
                    client_addresses.erase(i);
                }
            }
        }
    }
}

#endif