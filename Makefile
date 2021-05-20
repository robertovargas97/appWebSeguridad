# To compile all or separetly
app: src/home.cc src/login.cc src/register.cc src/comments.cc src/add_comment.cc src/add_user.cc utils/utils.cc src/add_product_post.cc src/add_product.cc src/list_products.cc src/view_car.cc
	g++ src/home.cc utils/utils.cc -o home.cgi -w
	g++ src/login.cc utils/utils.cc -o login.cgi -w 
	g++ src/register.cc utils/utils.cc -o register.cgi -w 
	g++ src/comments.cc utils/utils.cc -o comments.cgi -w 
	g++ utils/utils.cc src/list_products.cc -o list_products.cgi -w 
	g++ utils/utils.cc src/add_product.cc -o add_product.cgi -w 
	g++ utils/utils.cc src/view_car.cc -o view_car.cgi -w 
	g++ src/add_product_post.cc utils/utils.cc utils/db_connection.cc -o add_product_post.cgi -w `mysql_config --cflags --libs` -w
	g++ src/add_comment.cc utils/utils.cc utils/db_connection.cc -o add_comment.cgi -w `mysql_config --cflags --libs` -w
	g++ src/add_user.cc utils/utils.cc utils/db_connection.cc -o add_user.cgi -w `mysql_config --cflags --libs` -w

home: src/home.cc
	g++ src/home.cc utils/utils.cc -o home.cgi -w

login: src/login.cc utils/utils.cc
	g++ src/login.cc utils/utils.cc -o login.cgi -w 

register: src/register.cc utils/utils.cc
	g++ src/register.cc utils/utils.cc -o register.cgi -w 

comments: src/comments.cc utils/utils.cc
	g++ src/comments.cc utils/utils.cc -o comments.cgi -w 

list_products: src/list_products.cc utils/utils.cc
	g++ src/list_products.cc utils/utils.cc -o list_products.cgi -w 
	
view_car: src/view_car.cc utils/utils.cc
	g++ src/view_car.cc utils/utils.cc -o view_car.cgi -w 

# To clean all cgi files
clean:
	rm home.cgi login.cgi register.cgi comments.cgi add_comment.cgi add_user.cgi list_products.cgi view_car.cgi

#rm add_comments
