#include <iostream>
#include <string>
#include <sstream>

void sendRedirect_W_Remove_Cookie(const std::string& location, const std::string& cookieName, const std::string& cookieValue, int client_socket) 
{
    std::string HTTP_RESP_COOKIE_W_LOCATION = "HTTP/1.1 302 Found\r\n";
    HTTP_RESP_COOKIE_W_LOCATION += "Location: " + location + "\r\n";
    HTTP_RESP_COOKIE_W_LOCATION += "Set-Cookie: " + cookieName + "=" + cookieValue + "; Path=/; Expires: January 1, 1999\r\n";
    HTTP_RESP_COOKIE_W_LOCATION += "Server: QNJ-Cloud\n";
    HTTP_RESP_COOKIE_W_LOCATION += "Connection: close\r\n\r\n";
    send(client_socket, HTTP_RESP_COOKIE_W_LOCATION.c_str(), HTTP_RESP_COOKIE_W_LOCATION.size(), 0);
}