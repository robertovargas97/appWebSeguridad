#ifndef DBConnection_H
#define DBConnection_H

#include "config.h"
#include </usr/include/mysql/mysql.h>

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
    DBConnection(string host, string user, string password, string database);
    ~DBConnection();

    vector<string> get_user_info(string email);

private:
    MYSQL *mysql = NULL;
};

#endif
