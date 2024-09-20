#include <qnj/qnj-proxy.h>

int main(int argc, char *argv[]) {
    //  void start_qnj_proxy(const std::string& http_ip, const int http_port, const std::string& tcp_ip, const int tcp_port);
    
    //             HTTP ADDR | HTTP PORT | TCP ADDR || TCP PORT

    if (5 != argc)
    {
        std::cout << "Not proper amount of arguments" << std::endl;
        std::cout << "Example usage: <httpserverIP> <httpserverPORT> <tcpserverIP> <tcpserverPORT>" << std::endl;
        exit(1);
    }
    
    int http_port = std::stoi(argv[2]);
    int tcp_port = std::stoi(argv[4]);
    start_qnj_proxy(argv[1], http_port, argv[3], tcp_port);
    return 0;
}