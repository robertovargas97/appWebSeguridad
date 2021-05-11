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

private:
    MYSQL *mysql = NULL;
};

#endif
