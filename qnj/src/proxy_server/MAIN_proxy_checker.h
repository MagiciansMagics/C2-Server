#ifndef _MAIN_PROXY_CHEKER_H_
#define _MAIN_PROXY_CHEKER_H_

int QNJ_proxy_client_server_socket_http, QNJ_proxy_client_server_socket_tcp, QNJ_proxy_client_connection_tcp, QNJ_proxy_client_connection_http;
struct sockaddr_in client_address;
struct hostent *he;
struct in_addr **addr_list;
std::vector<pid_t> worker_pids;
void qnj_proxy_server_start_http(const std::string& http_addr, int port);
int qnj_bind_proxy_server_port = 7000;
#define buffer_max 2048

#endif