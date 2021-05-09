#ifndef Utils_H
#define Utils_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <dir.h>

using namespace std;

class Utils
{
public:
    Utils();
    ~Utils();
    char *read_file(char *file_name, char *file_content);
};

#endif
