#include <iostream>
#include <ctime>
#include <string>

std::string CL_PRINT_TIME()
{
    time_t now = time(0);
    struct tm timeinfo;
    char time_buffer[80];
    time(&now);
    localtime_r(&now, &timeinfo);
    strftime(time_buffer, sizeof(time_buffer), "[%d/%b/%Y %T] ", &timeinfo);

    return std::string(time_buffer);
}