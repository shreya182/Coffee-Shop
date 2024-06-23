#include "coffee.h"
#include <string>
#include <fstream>


coffee::coffee(){

}
double coffee::get_small_cost() const{ // get small cost
    return small_cost; 
}
double coffee::get_medium_cost() const{ // get medium cost
    return medium_cost; 
}

double coffee::get_large_cost() const{ // get large cost
    return large_cost; 
}

std::string coffee::get_name() const{ // get name
    return name; 
}
