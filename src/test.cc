#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
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

int main()
{

   // setenv("DB_HOST", "localhost", 0);
   // setenv("DB_USERNAME", "user", 0);
   // setenv("DB_PASSWORD", "user123", 0);
   // setenv("DB_NAME", "testdb", 0);

   // printf(getenv("DB_HOST"));
   // printf(getenv("DB_USERNAME"));
   // printf(getenv("DB_PASSWORD"));
   // printf(getenv("DB_NAME"));
   printf(getenv("MY_TEST_VARIABLE"));

   return 0;
}
