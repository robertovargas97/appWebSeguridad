#include "../utils/utils.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

const string ENV[26] = {
    "COMSPEC", "DOCUMENT_ROOT", "GATEWAY_INTERFACE",
    "HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING",
    "HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION",
    "HTTP_HOST", "HTTP_USER_AGENT", "PATH",
    "QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT",
    "REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME",
    "SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN",
    "SERVER_NAME", "SERVER_PORT", "SERVER_PROTOCOL",
    "SERVER_SIGNATURE", "SERVER_SOFTWARE", "CONTENT_LENGTH", "HTTP_COOKIE"};

int main(int argc, char const *argv[])
{

    Utils file_reader = Utils();
    //char *header = "/templates/header.html";
    char *navbar = "/templates/navbar.html";
    char *add_product = "/templates/add_product.html";
    char *footer = "/templates/footer.html";
    //char *header_content = file_reader.read_file(header, header_content);
    char *navbar_content = file_reader.read_file(navbar, navbar_content);
    char *add_product_content = file_reader.read_file(add_product, add_product_content);
    char *footer_content = file_reader.read_file(footer, footer_content);

    printf("Content-type:text/html\r\n\r\n");
    //printf(header_content);
    printf(navbar_content);
    printf(add_product_content);
    printf(footer_content);

    //free(header_content);
    free(navbar_content);
    free(add_product_content);
    free(footer_content);
    return 0;
}
