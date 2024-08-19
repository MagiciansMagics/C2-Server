#include "../qnj_config.h"

void save_http_requests_data(std::string& first_part_http_database, std::string& second_part_http_database)
{
    std::ofstream http_requests_file("/root/qnj-server/save_request_http.log", std::ios::app);

    std::string both_http_request = first_part_http_database + second_part_http_database;

    http_requests_file << both_http_request;

    http_requests_file.close();
}