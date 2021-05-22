
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <stdlib.h>

using namespace std;

class product
{
public:
    product();
    product(
    int my_code_product,
	string my_name,
	string my_price,
	string my_description,
	string my_category
    );
    ~product();
    double get_price();
    string get_name();
    string get_category();
    string get_description();
    int get_code_product();
    bool get_in_cart();
    string get_correo();
    int get_id_product_cart();
    void set_price(string my_price);
    void set_name(string my_name);
    void set_category(string my_category);
    void set_description(string my_description);
    void set_code_product(int my_code_product);
    void set_corero(string my_correo);
    void set_id_product_cart( int id);
    void set_in_cart(bool in);

private:    	
	int code_product;
	string name;
	string price;
	string description;
	string category;
	bool in_cart;
	int id_product_cart;
	string correo;
    
};




   
