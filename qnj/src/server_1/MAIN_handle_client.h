#ifndef _MAIN_HANDLE_CLIENT_H_
#define _MAIN_HANDLE_CLIENT_H_

void addNewClient(int server_socket, int epoll_fd, std::map<int, sockaddr_in>& client_addresses);
std::string userIdCookieValue;
std::string data0x00UserIdCookieValue;
int request_amount;

#endif