#ifndef Utils_H
#define Utils_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>        
#include <unistd.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <regex>
#include <map>
#include <cryptopp/sha.h>
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>

#define PATH_MAX 4096

using namespace std;
using namespace CryptoPP;

class Utils
{
public:
    Utils();
    ~Utils();
    char *read_file(char *file_name, char *file_content);
    vector<string> split(string text, string delimiter);
    map<string, string> get_post_data();
    string create_salt();
    string create_hash_sha2(string password, string salt);
    string replace_pattern(string text, string pattern, string new_value);
};

#endif
