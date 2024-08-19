#ifndef _ERROR_LOG_HPP_
#define _ERROR_LOG_HPP_

static void qnj_accualy_write_error(const std::string& error_string)
{

}

void qnj_write_error_into_file(const std::string& error_variable)
{
    if (error_variable.size() == 0)
    {
        std::cout << "Look into your error file [ERR_]"
    }
}

#endif