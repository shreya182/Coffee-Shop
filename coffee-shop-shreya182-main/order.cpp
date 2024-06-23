#include "order.h"
#include <iostream>
#include <fstream>

int order::next_order_number = -9;

order::order(){
        order_number = get_next_order_number();
}
double order::total_cost() const { //calculate total cost
        return quantity * price;
}
int order::get_order_number() const{ //get order number
        return order_number; 
}
void order::write_to_file(std::ostream& out) const { //write to order file
        out << order_number << " " << coffee_name << " " << coffee_size << " " << quantity << std::endl;
}