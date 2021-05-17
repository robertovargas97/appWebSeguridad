#ifndef Utils_H
#define Utils_H

#include "db_connection.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <map>

#define PATH_MAX 4096

using namespace std;

class Utils
{
public:
    Utils();
    ~Utils();
    char *read_file(char *file_name, char *file_content);
    vector<string> split(string text, string delimiter);
    map<string, string> get_post_data();
};

#endif
