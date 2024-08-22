#ifndef SEND_HTML_FILES_HPP
#define SEND_HTML_FILES_HPP

#include "../qnj_config.h"
#include "./http/HTTP_STATUS.hpp"
#include "../json/save_2http_requests.hpp"
#include "../memory/qnj_memory_pool.h"
#include "../memory/qnj_alloc.hpp"
#include "./html_page.h"

constexpr char SERVER_NAME[] = "QNJ-Cloud";
constexpr char POWERED_BY[] = "magic";
// Function to send data through socket with error handling
void send_with_error_handling(int socket, const char* data, size_t size) {
    ssize_t sent_bytes = send(socket, data, size, 0);
    if (sent_bytes < 0) {
        std::cerr << "Error occurred while sending data through socket." << std::endl;
    }
}

// Function to send HTTP response header
void send_response_header(int socket, const std::string& header) {
    send_with_error_handling(socket, header.c_str(), header.size());
}

void send_html_file(const std::string& file_path, const std::string& content_type, const std::string& http_code, const std::string& http_ver, int client_socket) {
    // Define response headers
    
    std::string response_header = http_ver + " " + http_code + "\r\n";
    response_header += "Content-Type: " + content_type + "; charset=utf-8\r\n";
    response_header += "Server: " + std::string(SERVER_NAME) + "\r\n";
    response_header += "X-Powered-By: " + std::string(POWERED_BY) + "\r\n";

    // Open the file
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        const std::string EMPTY_RESPONSE = "<html><body><h1>204 No content</h1></body></html>";
        response_header += "Content-Length: " + std::to_string(EMPTY_RESPONSE.length()) + "\r\n\r\n";
        send_response_header(client_socket, "HTTP/1.1 204 No Content\r\n" + response_header);
        send_with_error_handling(client_socket, EMPTY_RESPONSE.c_str(), EMPTY_RESPONSE.length());
        code_status(204);
        save_http2_requests_data(204);
        return;
    }

    // Read the content of the file
    file.seekg(0, std::ios::end);
    size_t content_length = file.tellg();
    file.seekg(0, std::ios::beg);

    // Allocate memory for file content from memory pool
    char* html_content = static_cast<char*>(qnj_alloc(content_length));
    if (html_content == nullptr) {
        // Memory allocation failed, fall back to standard allocation
        html_content = static_cast<char*>(qnj_alloc(content_length));
        if (html_content == nullptr) {
            std::cerr << "Failed to allocate memory for file content." << std::endl;
            return;
        }
    }

    // Read file content into allocated memory
    file.read(html_content, content_length);

    // Add Content-Length to the response header
    response_header += "Content-Length: " + std::to_string(content_length) + "\r\n\r\n";
    send_response_header(client_socket, response_header);

    // Send the file content
    send_with_error_handling(client_socket, html_content, content_length);
    page_views += 1;

    // Deallocate memory (either from pool or standard allocation)
    qnj_free(html_content);

    // Close the file
    file.close();

    // Log HTTP request data
    int code = std::stoi(http_code);
    save_http2_requests_data(code);
    code_status(code);
}
#endif