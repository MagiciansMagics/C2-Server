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

#define CLIENT_REQUEST_BUFFER 8192

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
    char* buffer = static_cast<char*>(qnj_palloc(pool, 8192));

    if (!buffer)
    {
        std::cout << "Allocating for buffer failed" << std::endl;
        qnj_destroy_pool(pool);
        close(client_socket);
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
            std::string userAgent = getHeader("User-Agent", requestHeaders);
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
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        std::cerr << "[ERROR] Failed to create epoll instance" << std::endl;
        return;
    }

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = QNJ_Main_server_socket;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, QNJ_Main_server_socket, &event) == -1) {
        std::cerr << "[ERROR] Failed to add server socket to epoll" << std::endl;
        close(epoll_fd);
        return;
    }

    std::map<int, sockaddr_in> client_addresses;

    while (true) {
        struct epoll_event events[10];
        int event_count = epoll_wait(epoll_fd, events, 10, -1);
        if (event_count < 0) {
            std::cerr << "[ERROR] epoll_wait error" << std::endl;
            break;
        }

        for (int i = 0; i < event_count; ++i) {
            if (events[i].data.fd == QNJ_Main_server_socket) {
                addNewClient(QNJ_Main_server_socket, epoll_fd, client_addresses);
            } else {
                handleClient(events[i].data.fd, client_addresses[events[i].data.fd]);
                close(events[i].data.fd);
                epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, nullptr);
                client_addresses.erase(events[i].data.fd);
            }
        }
    }

    close(epoll_fd);
}

void addNewClient(int server_socket, int epoll_fd, std::map<int, sockaddr_in>& client_addresses) {
    struct sockaddr_in client_address;
    socklen_t client_address_size = sizeof(client_address);
    int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);
    if (client_socket < 0) {
        std::cerr << "[ERROR] Failed to accept client connection" << std::endl;
        return;
    }

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = client_socket;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket, &event) == -1) {
        std::cerr << "[ERROR] Failed to add client socket to epoll" << std::endl;
        close(client_socket);
        return;
    }

    client_addresses[client_socket] = client_address;
}

#endif