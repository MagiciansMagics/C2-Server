#include "./src/json/save_client_data-0x00.hpp"

int main()
{
    std::string first_name = "John";
    std::string last_name = "Doe";
    std::string age = "30";
    std::string gender = "Male";
    std::string email = "john.doe@example.com";
    std::string phonenumber = "1234567890";
    std::string country = "USA";
    std::string city = "New York";
    std::string children_amount = "2";
    std::string material_status = "Married";
    std::string user_mugshot_pic = "mugshot.jpg";
    save_client_data_0x00(first_name, last_name, age, gender, email, phonenumber, country, city, children_amount, material_status, user_mugshot_pic);

    return 0;
}