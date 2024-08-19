#ifndef SAVE_2HTTP_REQUESTS_HPP
#define SAVE_2HTTP_REQUESTS_HPP
#include "../qnj_config.h"
#include "../networking/http/HTTP_STATUS.hpp"

void save_http2_requests_data(int code_status_data)
{
    std::ofstream http_requests_file("/root/qnj-server/save_request_http.log", std::ios::app);

    std::string both_http_request = code_status(code_status_data) + "\n";

    http_requests_file << both_http_request;

    http_requests_file.close();
}
#endif