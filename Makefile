# To compile all or separetly
app: src/home/home.cc src/login/login.cc src/registry/register.cc src/comments/comments.cc src/comments/add_comment.cc src/registry/add_user.cc utils/utils.cc src/login/login_response.cc src/add_products/add_product_post.cc src/add_products/add_product.cc src/list_products/list_products.cc src/list_products/view_car.cc
	g++ src/home/home.cc utils/db_connection.cc utils/utils.cc -o home.cgi -std=c++11 -w -lcryptopp -lcgicc `mysql_config --cflags --libs`
	g++ src/login/login.cc utils/db_connection.cc utils/utils.cc -o login.cgi -std=c++11 -w -lcryptopp -lcgicc `mysql_config --cflags --libs`
	g++ src/registry/register.cc utils/db_connection.cc utils/utils.cc -o register.cgi -std=c++11 -w -lcryptopp -lcgicc `mysql_config --cflags --libs`
	g++ src/comments/comments.cc utils/db_connection.cc utils/utils.cc -o comments.cgi -std=c++11 -w -lcryptopp -lcgicc `mysql_config --cflags --libs`
	g++ utils/utils.cc  utils/db_connection.cc src/add_products/add_product.cc -o add_product.cgi -std=c++11 -w -lcryptopp -lcgicc `mysql_config --cflags --libs`
	g++ src/list_products/list_products.cc utils/db_connection.cc utils/utils.cc -o list_products.cgi -std=c++11 -w -lcryptopp -lcgicc `mysql_config --cflags --libs`
	g++ src/list_products/view_car.cc utils/db_connection.cc utils/utils.cc -o view_car.cgi -w -std=c++11 -lcryptopp -lcgicc `mysql_config --cflags --libs`
	g++ src/add_products/add_product_post.cc utils/utils.cc utils/db_connection.cc -o add_product_post.cgi -w `mysql_config --cflags --libs` -std=c++11 -w -lcryptopp -lcgicc
	g++ src/comments/add_comment.cc utils/utils.cc utils/db_connection.cc -o add_comment.cgi -w `mysql_config --cflags --libs` -lcryptopp -std=c++11 -w -lcgicc
	g++ src/registry/add_user.cc utils/utils.cc utils/db_connection.cc -o add_user.cgi -w `mysql_config --cflags --libs` -lcryptopp -std=c++11 -w -lcgicc
	g++ src/login/login_response.cc utils/utils.cc utils/db_connection.cc -o login_response.cgi -w -lcgicc -lcryptopp `mysql_config --cflags --libs` -std=c++11
	g++ src/login/logout_response.cc utils/utils.cc utils/db_connection.cc  -o logout_response.cgi -w -lcryptopp -lcgicc `mysql_config --cflags --libs` -std=c++11

home: src/home/home.cc
	g++ src/home/home.cc utils/utils.cc -o home.cgi -w -lcryptopp -std=c++11

login: src/login/login.cc utils/utils.cc
	g++ src/login/login.cc utils/utils.cc -o login.cgi -w -lcryptopp -std=c++11

login_response: src/login/login_response.cc utils/utils.cc
	g++ src/login/login_response.cc utils/utils.cc utils/db_connection.cc  -o login_response.cgi -w -lcryptopp -lcgicc `mysql_config --cflags --libs` -std=c++11

logout_response: src/login/logout_response.cc utils/utils.cc
	g++ src/login/logout_response.cc utils/utils.cc utils/db_connection.cc  -o logout_response.cgi -w -lcryptopp -lcgicc `mysql_config --cflags --libs` -std=c++11


register: src/registry/register.cc utils/utils.cc
	g++ src/registry/register.cc utils/utils.cc -o register.cgi -w -lcryptopp -std=c++11

comments: src/comments/comments.cc utils/utils.cc
	g++ src/comments/comments.cc utils/utils.cc -o comments.cgi -w -lcryptopp -std=c++11

utils: utils/utils.cc
	g++ utils/utils.cc -o utils.cgi -w  -lcryptopp -std=c++11 -lcgicc

list_products: src/list_products/list_products.cc utils/utils.cc
	g++ src/list_products/list_products.cc utils/utils.cc -o list_products.cgi -w -std=c++11 -lcryptopp
	
view_car: src/list_products/view_car.cc utils/utils.cc
	g++ src/list_products/view_car.cc utils/utils.cc -o view_car.cgi -w -std=c++11 -lcryptopp

add_product:
	g++ utils/utils.cc  utils/db_connection.cc src/add_products/add_product.cc -o add_product.cgi -std=c++11 -w -lcryptopp -lcgicc `mysql_config --cflags --libs`
# To clean all cgi files
clean:
	rm home.cgi login.cgi register.cgi comments.cgi add_comment.cgi add_user.cgi list_products.cgi view_car.cgi add_product.cgi add_product_post.cgi login_response.cgi add_to_car.cgi buy_car.cgi delete_from_car.cgi select_product.cgi empty_car.cgi logout_response.cgi

#rm add_comments
