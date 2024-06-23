/* 
 * Author: Shreya Suresh
 * Description: Coffee Shop simulator with 6 different functions such as add and remove coffees 
 * from menu and place orders.
 */

#include <iostream>
#include "display.h"
#include <fstream>

int main() {
	std::cout << "Welcome to the Coffee++ Cafe!" << std::endl;

	// Construct and initialize a shop object `s`
	shop s;
	// input streams, files to read from
    std::ifstream shopFile("shop_info.txt");
    std::ifstream menuFile("menu.txt");
    if (shopFile.is_open() && menuFile.is_open()) {
        s.populate_from_file(shopFile); // populate shop info
        s.populate_menu_from_file("menu.txt"); // populate menu info
	} else {
        std::cerr << "Failed to open one or more files." << std::endl;
        return 1;
    }

	int option;
	do {
		option = get_option();
		if (option >= 1 && option <= 6) {
			execute_option(s, option);
		} 
	} while (option != 7);
	s.save_orders_to_file();
	return 0;
}