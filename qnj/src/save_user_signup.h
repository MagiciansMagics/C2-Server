#ifndef __SAVE_USER_SIGNUP_H_
#define __SAVE_USER_SIGNUP_H_
#include "./qnj_config.h"
#include "../auto/modules/save_user_signup.hpp"

std::string exract_full_cookie()
{
    return extract_cookie_value();
}

void execute_save_user_save_data(std::string& email, std::string& password)
{
    save_user_signup_data(email, password);
}

#endif