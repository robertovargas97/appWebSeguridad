#ifndef Utils_H
#define Utils_H

#include <chrono>
#include <fstream>
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
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <regex>

#define PATH_MAX 4096
#define LOGS_PATH "app_logs.txt"
#define ERROR_LOGS_PATH "app_error_logs.txt"

using namespace std;
using namespace CryptoPP;
using namespace cgicc;

class Utils
{
public:
    Utils();
    ~Utils();
    char *read_file(char *file_name, char *file_content);
    vector<string> split(string text, string delimiter);
    std::map<string, string> get_post_data();
    string create_salt();
    string create_hash_sha2(string password, string salt);
    string replace_pattern(string text, string pattern, string new_value);
    std::map<string, string> get_cookies();
    void get_navbar(bool is_signed);
    void log_app_action(string action, string result, string user, string description="");
    string mask_card_number(string card_number);
    bool verify_card(string card_number);
    bool is_valid_visa_card_no(string card_number);
    bool is_valid_masterCard_no(string card_number);
    bool is_valid_amex_card_no(string card_number);
    bool verify_card_no_type(string card_number, string type);
    char* get_date();
};

#endif
