#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
using namespace std;

const string ENV[ 26] = {
   "COMSPEC", "DOCUMENT_ROOT", "GATEWAY_INTERFACE",   
   "HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING",             
   "HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION",         
   "HTTP_HOST", "HTTP_USER_AGENT", "PATH",            
   "QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT",      
   "REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME",
   "SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN",      
   "SERVER_NAME","SERVER_PORT","SERVER_PROTOCOL",     
   "SERVER_SIGNATURE","SERVER_SOFTWARE","CONTENT_LENGTH","HTTP_COOKIE" };   

int main () {
   cout << "Content-type:text/html\r\n\r\n";
   cout<<"<!DOCTYPE html>\n";
   cout<<"<html>\n";
   cout<<"<body>\n";
   cout<<"<h1>Login</h1>\n";
   cout<<"<form action="<<"/cgi-bin/Login/Request"<<" method='post' >\n";
   cout<<"  <label for="<<"email"<<">Email:</label>\n";
   cout<<"  <input required type="<<"email"<<" id="<<"email"<<" name="<<"email"<<"><br><br>\n";
   cout<<"  <label for="<<"pwd"<<">Password:</label>\n";
   cout<<"  <input required type="<<"password"<<" id="<<"pwd"<<" name="<<"pwd"<<" minlength="<<"8"<<"><br><br>\n";
   cout<<"  <input value=\"log in\" type="<<"submit"<<">\n";
   cout<<"</form>\n";


   cout<<"<a href="<<"/cgi-bin/Login/Reset"<<"><h3>Forgot Password?</h3></a>\n";

   cout<<"</body>\n";
   cout<<"</html>\n";

   return 0;
}
