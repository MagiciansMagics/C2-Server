#include <iostream>
#include <fstream>
#include <string>
#include <random>

std::string generate_random_cookie(int length)
{
    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::mt19937 rng(std::random_device{}()); // random number generator
    std::uniform_int_distribution<std::string::size_type> dist(0, chars.length() - 1);

    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result.push_back(chars[dist(rng)]);
    }
    return result;
}

std::string save_user_signup_data(const std::string& username, const std::string& password)
{
    std::ofstream username_file("/root/qnj-server/general_username.log", std::ios::app);
    std::ofstream password_file("/root/qnj-server/general_password.log", std::ios::app);
    std::ofstream cookies_file("/root/qnj-server/general_cookie.log", std::ios::app);

    std::string generated_cookie = generate_random_cookie(100);

    username_file << username << "\n";
    password_file << password << "\n";
    cookies_file << generated_cookie << "\n";

    cookies_file.close();
    username_file.close();
    password_file.close();

    return generated_cookie;

    std::cout << "Data has been written to the file." << std::endl;
}

std::string extract_cookie_value()
{
    std::string current_cookie = save_user_signup_data("", "");

    return current_cookie;
}