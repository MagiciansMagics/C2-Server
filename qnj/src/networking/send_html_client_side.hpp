#ifndef SEND_HTML_CLIENT_SIDE
#define SEND_HTML_CLIENT_SIDE

#include "../qnj_config.h"
#include "./http/HTTP_STATUS.hpp"
#include "../json/save_2http_requests.hpp"

void content_send_file_w_client_side(const std::string& file_path, const std::string& content_type, const std::string& http_code, const std::string& http_ver, int client_socket, std::string& custom_content)
{
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file: " << file_path << std::endl;
        return;
    }

    // Read the content of the file
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string html_content = buffer.str();

    // Append the dynamic content to the HTML content
    std::string dynamic_content = custom_content;
    html_content += dynamic_content;

    // Constructing the response header
    std::string response_header = http_ver + " " + http_code + "\r\n";
    response_header += "Content-Type: ";
    response_header += content_type + "; charset=utf-8\r\n";
    response_header += "Server: QNJ-Cloud\r\n";
    response_header += "X-Powered-By: magic\r\n";
    response_header += "Content-Length: " + std::to_string(html_content.length()) + "\r\n\r\n";

    send(client_socket, response_header.c_str(), response_header.length(), 0);

    // Sending the HTML content
    send(client_socket, html_content.c_str(), html_content.length(), 0);

    // Close the file
    file.close();
    int code = std::stoi(http_code);
    save_http2_requests_data(code);
    code_status(code);
}

#endif