#include "../qnj_config.h"

using namespace std;

void save_user_address_public(std::string& user_addr) 
{
    ofstream MyFile("/root/qnj-server/user_public_address.log", ios::app);

    if (user_addr == "")
    {
        MyFile << "";
    }
    else if (user_addr.empty())
    {
        MyFile << "";
    }
    else
    {
        MyFile << user_addr << "\n";
    }

    MyFile.close();
}