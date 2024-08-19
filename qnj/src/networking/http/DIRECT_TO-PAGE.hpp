#include <string>
#include <sstream>

void sendRedirect(const std::string& location, int client_socket) 
{
    std::string HTTP_RESP_LOCATION_DIRECT = "HTTP/1.1 302 Found\r\n";
    HTTP_RESP_LOCATION_DIRECT += "Location: " + location + "\r\n";
    HTTP_RESP_LOCATION_DIRECT += "Server: QNJ-Cloud\n";
    HTTP_RESP_LOCATION_DIRECT += "Connection: close\r\n\r\n";
    send(client_socket, HTTP_RESP_LOCATION_DIRECT.c_str(), HTTP_RESP_LOCATION_DIRECT.size(), 0);
}