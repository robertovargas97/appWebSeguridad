#ifndef DBConnection_H
#define DBConnection_H

#include "utils.h"
#include "config.h"
#include "product.h"
#include <mysql/mysql.h>
#include "host_settings.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>
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

    string exist_in_cart(string email, string code_product);
    string get_user_salt(string password);
    vector<string> get_user_info(string email);
    vector<vector<string> > get_all_products();
    vector<vector<string> > get_my_cart(string email);
    vector<vector<string> > search_product(string product);
    bool add_comment(string name, string last_name, string email, string comment_type, string comment);
    bool add_product(string name, string price, string description, string category);
    bool add_user(string name, string last_name, string email, string secret, string phone_number, string address, string salt);
    bool verify_login(string email, string password, string salt);
    bool verify_session(string email, string password);
    bool add_to_cart(string email, string code_product);
    bool delete_from_cart(string email, string code_product);
    bool buy_cart(string email);
    bool empty_cart(string email, string code_product);
    bool erase_product(string codigoProducto);
    bool erase_products(string correo, vector<vector<string> > cart_list);  
    bool add_receipt(string receipt_no, string user_name, string user_email, string card_no, string products_list, string total);                                      

private:
    MYSQL *mysql = NULL;
    Utils utils = Utils();
};

#endif
