#include "../qnj_config.h"

void send_html_page(const std::string& html_content, const std::string& http_code, const std::string& http_ver, int client_socket)
{
    std::string response_header = http_ver + " " + http_code + "\r\n";
    response_header += "Content-Type: text/html\r\n";
    response_header += "Server: QNJ-Cloud\n";
    response_header += "Content-Length: " + std::to_string(html_content.length()) + "\r\n\r\n";

    send(client_socket, response_header.c_str(), response_header.length(), 0);

    send(client_socket, html_content.c_str(), html_content.length(), 0);
}

void test_html(std::string& html_content, const std::string& http_code, const std::string& http_ver, int client_socket)
{
    std::string response_header = http_ver + " " + http_code + "\r\n";
    response_header += "Content-Type: text/html\r\n";
    response_header += "Server: QNJ-Cloud\n";
    response_header += "Content-Length: " + std::to_string(html_content.length()) + "\r\n\r\n";

    send(client_socket, response_header.c_str(), response_header.length(), 0);

    send(client_socket, html_content.c_str(), html_content.length(), 0);
}