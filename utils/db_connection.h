#ifndef DBConnection_H
#define DBConnection_H

#include "utils.h"
#include "config.h"
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

using namespace std;

class DBConnection
{
public:
    DBConnection();
    ~DBConnection();

    vector<string> get_user_info(string email);
    bool add_comment(string name, string last_name, string email, string comment_type, string comment);
    bool add_user(string name, string last_name, string email, string password, string phone_number, string address);
    string get_user_salt(string password);
    bool verify_login(string email, string password, string salt);

private:
    MYSQL *mysql = NULL;
};

#endif
