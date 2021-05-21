# To compile all or separetly
app: src/home.cc src/login.cc src/register.cc src/comments.cc src/add_comment.cc src/add_user.cc utils/utils.cc src/login_response.cc src/add_product_post.cc src/add_product.cc src/list_products.cc src/view_car.cc
	g++ src/home.cc utils/utils.cc -o home.cgi -w -lcrypto++
	g++ src/login.cc utils/utils.cc -o login.cgi -w -lcrypto++
	g++ src/register.cc utils/utils.cc -o register.cgi -w -lcrypto++
	g++ src/comments.cc utils/utils.cc -o comments.cgi -w -lcrypto++
	g++ utils/utils.cc src/add_product.cc -o add_product.cgi -w -lcrypto++
	g++ src/list_products.cc utils/utils.cc -o list_products.cgi -w -lcrypto++
	g++ src/view_car.cc utils/utils.cc -o view_car.cgi -w -lcrypto++
	g++ src/add_product_post.cc utils/utils.cc utils/db_connection.cc -o add_product_post.cgi -w `mysql_config --cflags --libs` -w -lcrypto++
	g++ src/add_comment.cc utils/utils.cc utils/db_connection.cc -o add_comment.cgi -w `mysql_config --cflags --libs` -lcrypto++ -w
	g++ src/add_user.cc utils/utils.cc utils/db_connection.cc -o add_user.cgi -w `mysql_config --cflags --libs` -lcrypto++ -w
	g++ src/login_response.cc utils/utils.cc utils/db_connection.cc -o login_response.cgi -w -lcrypto++ `mysql_config --cflags --libs`

home: src/home.cc
	g++ src/home.cc utils/utils.cc -o home.cgi -w -lcrypto++

login: src/login.cc utils/utils.cc
	g++ src/login.cc utils/utils.cc -o login.cgi -w -lcrypto++

login_response: src/login_response.cc utils/utils.cc
	g++ src/login_response.cc utils/utils.cc utils/db_connection.cc  -o login_response.cgi -w -lcrypto++ `mysql_config --cflags --libs`

register: src/register.cc utils/utils.cc
	g++ src/register.cc utils/utils.cc -o register.cgi -w -lcrypto++

comments: src/comments.cc utils/utils.cc
	g++ src/comments.cc utils/utils.cc -o comments.cgi -w -lcrypto++

utils: utils/utils.cc
	g++ utils/utils.cc -o utils.cgi -w  -lcrypto++

list_products: src/list_products.cc utils/utils.cc
	g++ src/list_products.cc utils/utils.cc -o list_products.cgi -w 
	
view_car: src/view_car.cc utils/utils.cc
	g++ src/view_car.cc utils/utils.cc -o view_car.cgi -w 

# To clean all cgi files
clean:
	rm home.cgi login.cgi register.cgi comments.cgi add_comment.cgi add_user.cgi list_products.cgi view_car.cgi

#rm add_comments
