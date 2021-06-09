#include "../../utils/utils.h"
#include "../../utils/db_connection.h"
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

int main(int argc, const char *argv[], const char *env[])
{


    Utils utils = Utils();
    DBConnection conn = DBConnection();
    char *header = "/templates/header.html";
    char *footer = "/templates/footer.html";
    char *footer_content = utils.read_file(footer, footer_content);
    char *header_content = utils.read_file(header, header_content);
    printf("Content-type:text/html\r\n\r\n");
    printf(header_content);
    std::map<string, string> form_data = utils.get_post_data();
    bool delete_from_cart_result = conn.delete_from_cart( form_data["correo"], form_data["producto"]);

    cout << footer_content;
    
    free(footer_content);
    free(header_content);

    return 1;
}
