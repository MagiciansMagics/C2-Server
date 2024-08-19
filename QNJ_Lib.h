#ifndef __QNJ_LIB_H__
#define __QNJ_LIB_H__
#include <string>
#include "lib-nodius/main_server.hpp"

class nodius_server;

void start(std::string& address, int port);

void get(const std::string& web_path);

void send(const std::string& data);

#endif
