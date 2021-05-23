#ifndef DBConnection_H
#define DBConnection_H

#include "utils.h"
#include "config.h"
#include "product.h"
#include <mysql/mysql.h>
#include "host_settings.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <stdlib.h>

using namespace std;

class DBConnection
{
public:
    DBConnection();
    ~DBConnection();

    vector<string> get_user_info(string email);
    bool add_comment(string name, string last_name, string email, string comment_type, string comment);
    bool add_product(string name, string price, string description, string category);
    bool add_user(string name, string last_name, string email, string password, string phone_number, string address);
    string get_user_salt(string password);
    bool verify_login(string email, string password, string salt);
    vector<product> get_all_products();
    bool exist_in_cart(string email,int code_product);
    vector<product> get_my_cart(string email);
    bool add_in_cart(string email, int code_product);
    bool delete_from_cart(string email, int code_product);
    bool empty_cart(string email, int code_product);

private:
    MYSQL *mysql = NULL;
};

#endif
