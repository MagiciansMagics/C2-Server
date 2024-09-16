#ifndef _TCP_HANDLE_CLIENT_H_
#define _TCP_HANDLE_CLIENT_H_

#define MAX_BUFFER 2048

int CLIENT_TOTAL_AMOUNT = 0, CLIENT_OFFLINE_AMOUNT = 0, CLIENT_ONLINE_AMOUNT = 0;
int TCP_CLIENT_SOCKET;
std::vector<int> QNJ_TCP_CLIENT_SOCKET;
char buffer[MAX_BUFFER] = {0};
ssize_t bytes_received;
int client_int_num = 0;
std::vector<std::string> client_id_array;
std::vector<int> client_number_id;
int client_num_am_id = 0;
std::string returned_client_data_string;
std::map<std::string, std::string> client_status_map;
std::string returned_client_vector_data;
std::mutex client_mutex;
std::string client_string_data_full;
std::string file_path;
std::string paths_file_path_ssuser;

#endif