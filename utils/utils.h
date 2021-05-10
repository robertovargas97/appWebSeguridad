#ifndef Utils_H
#define Utils_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>

#define PATH_MAX 4096

using namespace std;

class Utils
{
public:
    Utils();
    ~Utils();
    char *read_file(char *file_name, char *file_content);
    vector<string> split(string text, string delimiter);
};

#endif
