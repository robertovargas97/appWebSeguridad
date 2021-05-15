#include "../utils/utils.h"
#include "../utils/db_connection.h"
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

    // DBConnection conn = DBConnection();
    Utils utils = Utils();

    char *header = "/templates/header.html";
    char *navbar = "/templates/navbar.html";
    char *footer = "/templates/footer.html";
    char *header_content = utils.read_file(header, header_content);
    char *navbar_content = utils.read_file(navbar, navbar_content);
    char *footer_content = utils.read_file(footer, footer_content);

    printf("Content-type:text/html\r\n\r\n");
    printf(header_content);
    printf(navbar_content);

    map<string, string> form_data = utils.get_post_data();
    cout << "<h1>" << form_data["name"] << "</h1>" << endl;
    cout << "<h1>" << form_data["last_name"] << "</h1>" << endl;
    cout << "<h1>" << form_data["email"] << "</h1>" << endl;
    cout << "<h1>" << form_data["comment_type"] << "</h1>" << endl;
    cout << "<h1>" << form_data["comment"] << "</h1>" << endl;

    // bool new_comment_result = conn.add_comment(form_data["name"], form_data["last_name"], form_data["email"], form_data["comment_type"], form_data["comment"]);

    // cout << "<h1>" << new_comment_result << "</h1>";
    printf(footer_content);

    free(header_content);
    free(navbar_content);
    free(footer_content);

    return 0;
}
