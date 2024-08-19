#ifndef __SIGNUP_SAVE_DATA_H_
#define __SIGNUP_SAVE_DATA_H_
#include "../save_user_signup.h"
#include <string>

void last_execute_save_data_singup(std::string& email, std::string& password)
{
    execute_save_user_save_data(email, password);
}

#endif