#include "product.h"

using namespace std;

product::product(){
	in_cart= false;
	id_product_cart= -1;
	correo = "";
};

product::product(
    int my_code_product,
	string my_name,
	string my_price,
	string my_description,
	string my_category    ){
	
	code_product = my_code_product;
	name = my_name;
	price = my_price ;
	description = my_description ;
	category =  my_category ;
	
	in_cart= false;
	id_product_cart= -1;
	correo = "";
};

product::~product()
{

};

double product::get_price(){
 return  atof(price.c_str());
};
string product::get_name(){
	return name;
};
string product::get_category(){
 	return category;
};
string product::get_description(){
	return description;
};
int product::get_code_product(){
	return code_product;
};
    bool product::get_in_cart(){
    	return in_cart;
    };
    int product::get_id_product_cart(){
    	return id_product_cart;
    };
    string product::get_correo(){
     return correo;
    };

void product::set_price( string my_price){
	price= my_price;
};
void product::set_name(string my_name){
	name= my_name;
};
void product::set_category(string my_category){
 	category= my_category;
};
void  product::set_description(string my_description){
	description =  my_description;
};
void product::set_code_product(int my_code_product){
	code_product = my_code_product;
};
    void product::set_corero(string my_correo){
     correo= my_correo;
   };
    void product::set_id_product_cart( int id){
    	id_product_cart=id;
    };
    void product::set_in_cart(bool in){
     		in_cart = in;
    };

