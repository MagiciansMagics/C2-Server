#ifndef _GET_LOGIN_CREDENTIALS_HPP_
#define _GET_LOGIN_CREDENTIALS_HPP_

#include <iostream>
#include <fstream>
#include <string>

bool get_username(const std::string& username, const std::string& file_path)
{
    std::ifstream MyReadFile(file_path);
    std::string myText;
    while (getline (MyReadFile, myText)) {
        if (myText == username) {
            MyReadFile.close();
            return true;
        }
    }
    MyReadFile.close();
    std::cout << username << "\n";

    return false;
}

bool get_password(const std::string& password, const std::string& file_path)
{
    std::ifstream MyReadFile(file_path);
    std::string myText;
    while (getline (MyReadFile, myText)) {
        if (myText == password) {
            MyReadFile.close();
            return true;
        }
    }
    MyReadFile.close();
    std::cout << password << "\n";

    return false;
}

bool get_cookies_from_file(const std::string& userIdCookieValue, const std::string& file_path) 
{
    std::ifstream MyReadFile(file_path);
    std::string myText;
    while (getline (MyReadFile, myText)) {
        if (myText == userIdCookieValue) {
            MyReadFile.close();
            return true;
        }
    }
    MyReadFile.close();
    std::cout << userIdCookieValue << "\n";

    return false;
}

#endif