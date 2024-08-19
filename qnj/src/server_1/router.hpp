#ifndef ROUTER_HPP
#define ROUTER_HPP

#include "../qnj_config.h"
#include "./MAIN_handle_client.hpp"
#include "../time_util.h"
#include "./paths.hpp"
#include "../networking/send_html_files.hpp"
#include "../networking/utils/get_cookie_info.hpp"
#include "../json/make_database_json.hpp"
#include "../json/save_user_public_addr.hpp"
#include "../json/save_user_remote_addr.hpp"
#include "../json/save_http_requests.hpp"

std::string userIdCookieValue;
std::string data0x00UserIdCookieValue;
int request_amount = 0;

class Router {
public:
    static void parseRequest(int client_socket, struct sockaddr_in client_address, const char* buffer, std::string& requestHeaders) {
        std::string request(buffer);
        size_t method_pos = request.find(" ");
        if (method_pos != std::string::npos) {
            std::string method = request.substr(0, method_pos); // Extract the method substring
            std::transform(method.begin(), method.end(), method.begin(), ::toupper);
            if (method == "GET" || method == "POST") {
                size_t http_version_start = request.find("HTTP/") + 5; // Find the start position of HTTP version
                size_t http_version_end = request.find("\r\n", http_version_start); // Find the end position of HTTP version
                std::string http_version = request.substr(http_version_start, http_version_end - http_version_start);
                std::string first_part_http_data = std::string(inet_ntoa(client_address.sin_addr)) + " - - " + execute_get_time() + "\"" + method + "";

                size_t start_pos = request.find(method) + method.length() + 1; // Move past method and one space
                size_t end_pos = request.find("HTTP") - 1;
                std::string path = request.substr(start_pos, end_pos - start_pos);
                std::string second_part_http_data = " " + path + " HTTP/" + http_version + "\" ";

                save_http_requests_data(first_part_http_data, second_part_http_data);

                request_amount += 1;
                std::string time_variable = execute_get_time();
                save_server_data_json(request_amount);
                
                std::string xForwardedFor = getHeader("X-Forwarded-For", requestHeaders);
                std::string Remote_address = inet_ntoa(client_address.sin_addr);

                save_user_address_remote(Remote_address);

                save_user_address_public(xForwardedFor);

                userIdCookieValue = get_cookie("session_id", request); // Store the returned session id
                data0x00UserIdCookieValue = get_cookie("session_data_0x00", request);

                routeRequest(client_socket, method, path, data0x00UserIdCookieValue, userIdCookieValue, requestHeaders); // Route the request. ##### userIdCookieValue = cookie_value just returned value

            } 
            else 
            {
                std::cout << "[*] Unsupported method: " << method << std::endl;
            }
        } 
        else 
        {
            std::cout << "[*] Invalid HTTP request" << std::endl;
        }
    }

private:
    static void routeRequest(int client_socket, const std::string& method, const std::string& path, std::string& data0x00UserIdCookieValue, std::string& userIdCookieValue, std::string& requestHeaders) 
    {
        path_handler(method, path, client_socket, userIdCookieValue, data0x00UserIdCookieValue, requestHeaders);
    }

    static 
};

#endif