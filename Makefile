# To compile all or separetly
app: src/home.cc src/login.cc src/register.cc src/comments.cc src/add_comment.cc src/add_user.cc utils/utils.cc src/login_response.cc src/add_product_post.cc src/add_product.cc src/list_products.cc src/view_car.cc
	g++ src/home.cc utils/utils.cc -o home.cgi -std=++11 -w -lcrypto++
	g++ src/login.cc utils/utils.cc -o login.cgi -std=++11 -w -lcrypto++
	g++ src/register.cc utils/utils.cc -o register.cgi -std=++11 -w -lcrypto++
	g++ src/comments.cc utils/utils.cc -o comments.cgi -std=++11 -w -lcrypto++
	g++ utils/utils.cc src/add_product.cc -o add_product.cgi -std=++11 -w -lcrypto++
	g++ src/list_products.cc utils/utils.cc -o list_products.cgi -std=++11 -w -lcrypto++
	g++ src/view_car.cc utils/utils.cc -o view_car.cgi -w -std=++11 -lcrypto++
	g++ src/add_product_post.cc utils/utils.cc utils/db_connection.cc -o add_product_post.cgi -w `mysql_config --cflags --libs` -std=++11 -w -lcrypto++
	g++ src/add_comment.cc utils/utils.cc utils/db_connection.cc -o add_comment.cgi -w `mysql_config --cflags --libs` -lcrypto++ -std=++11 -w
	g++ src/add_user.cc utils/utils.cc utils/db_connection.cc -o add_user.cgi -w `mysql_config --cflags --libs` -lcrypto++ -std=++11 -w
	g++ src/login_response.cc utils/utils.cc utils/db_connection.cc -o login_response.cgi -w -lcrypto++ `mysql_config --cflags --libs` -std=++11

home: src/home.cc
	g++ src/home.cc utils/utils.cc -o home.cgi -w -lcrypto++ -std=++11

login: src/login.cc utils/utils.cc
	g++ src/login.cc utils/utils.cc -o login.cgi -w -lcrypto++ -std=++11

login_response: src/login_response.cc utils/utils.cc
	g++ src/login_response.cc utils/utils.cc utils/db_connection.cc  -o login_response.cgi -w -lcrypto++ `mysql_config --cflags --libs` -std=++11

register: src/register.cc utils/utils.cc
	g++ src/register.cc utils/utils.cc -o register.cgi -w -lcrypto++ -std=++11

comments: src/comments.cc utils/utils.cc
	g++ src/comments.cc utils/utils.cc -o comments.cgi -w -lcrypto++ -std=++11

utils: utils/utils.cc
	g++ utils/utils.cc -o utils.cgi -w  -lcrypto++ -std=++11

list_products: src/list_products.cc utils/utils.cc
	g++ src/list_products.cc utils/utils.cc -o list_products.cgi -w -std=++11
	
view_car: src/view_car.cc utils/utils.cc
	g++ src/view_car.cc utils/utils.cc -o view_car.cgi -w -std=++11

# To clean all cgi files
clean:
	rm home.cgi login.cgi register.cgi comments.cgi add_comment.cgi add_user.cgi list_products.cgi view_car.cgi

#rm add_comments
