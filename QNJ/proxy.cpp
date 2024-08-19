#include <qnj/qnj-proxy.h>

int main(int argc, char *argv[]) {
    //  void start_qnj_proxy(const std::string& http_ip, const int http_port, const std::string& tcp_ip, const int tcp_port);
    
    //             HTTP ADDR | HTTP PORT | TCP ADDR || TCP PORT
    
    start_qnj_proxy("127.0.0.1", 3000, "127.0.0.1", 40000);
    return 0;
}