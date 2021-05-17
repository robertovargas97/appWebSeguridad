# To compile all or separetly
app: src/home.cc src/login.cc src/register.cc src/comments.cc src/add_comment.cc utils/utils.cc
	g++ src/home.cc utils/utils.cc -o home.cgi -w
	g++ src/login.cc utils/utils.cc -o login.cgi -w 
	g++ src/register.cc utils/utils.cc -o register.cgi -w 
	g++ src/comments.cc utils/utils.cc -o comments.cgi -w 

#g++ src/add_comment.cc utils/utils.cc utils/db_connection.cc -o add_comment.cgi -w `mysql_config --cflags --libs

home: src/home.cc
	g++ src/home.cc utils/utils.cc -o home.cgi -w

login: src/login.cc utils/utils.cc
	g++ src/login.cc utils/utils.cc -o login.cgi -w 

register: src/register.cc utils/utils.cc
	g++ src/register.cc utils/utils.cc -o register.cgi -w 

comments: src/comments.cc utils/utils.cc
	g++ src/comments.cc utils/utils.cc -o comments.cgi -w 


# To clean all cgi files
clean:
	rm home.cgi login.cgi register.cgi comments.cgi

