#include <iostream>
#include <cmath>
#include "display.h"
#include <iomanip>

/*
 * THIS IS A SUGGESTED FUNCTION.
 * Name: print_options()
 * Description: Print options to the user
 */
void print_options() {
	std::cout << "What would you like to do?" << std::endl;
	std::cout << "	1. View shop info" << std::endl;
	std::cout << "	2. Add an item to menu" << std::endl;
	std::cout << "	3. Remove an item from menu" << std::endl;
	std::cout << "	4. Search by coffee name" << std::endl;
	std::cout << "	5. Search by price" << std::endl;
	std::cout << "	6. Place an order" << std::endl;
	std::cout << "	7. Log out" << std::endl;
}

/*
 * THIS IS A SUGGESTED FUNCTION.
 * Name: print_selection_error
 * Description: Scolds the user for selecting a bad option
 *		number
 */
void print_selection_error() {
	std::cout << "Error: You must choose one of the 7 options provided"
		<< std::endl;
}

int get_option() {
	int option;
	bool first = true;
	do {
		if (!first) {
			print_selection_error();
		}
		first = false;
		print_options();
		std::cout << "Selection: ";
		std::cin >> option;
	} while (option < 1 || option > 7);

	return option;
}
void display_shop_info(shop& s) { // print shop info
    std::cout << "Address: " << s.get_address() << std::endl;
    std::cout << "Phone: " << s.get_phone() << std::endl;
    std::cout << "The shop revenue is: $" << std::fixed << std::setprecision(2) << s.get_revenue() << std::endl;
    std::cout << "Here is our menu:" << std::endl;
	display_menu(s);

	std::cout << "\n";
	std::cout << "Order info:" << std::endl;
	s.display_orders();
}
void display_menu(shop& s){ // print menu
	const menu& m = s.get_menu();
    for (int i = 0; i < m.get_num_coffees(); ++i) {
        const coffee& c = m.get_coffee(i);
        std::cout << i + 1 << ". " << c.get_name() << std::endl
                  << "Small – " << c.get_small_cost() << std::endl
                  << "Medium – " << c.get_medium_cost() << std::endl
                  << "Large – " << c.get_large_cost() << std::endl;
    }
}
void execute_option(shop& s, int option) {
	if (option == 1) {
		// Display shop info
		display_shop_info(s);
		std::cout << "\n";
		s.display_additional_info();
	} else if (option == 2) { 
		// Guide user through adding a coffee to the menu
		std::string name;
        double small, medium, large;
		
        std::cout << "Enter the name of the new coffee drink (in 1 word): ";
        std::cin >> name;

    	while (true) { // handle invalid input
    		std::cout << "Enter price of small size (8oz): ";
    		std::cin >> small;
    		if (std::cin.fail() || small <= 0) {
        		std::cout << "Invalid input. Please enter a positive number.\n";
        		std::cin.clear(); 
        		std::cin.ignore(); 
    		} else {
        	break;
    		}
		}
		while (true) { // handle invalid input
    		std::cout << "Enter price of medium size (12oz): ";
    		std::cin >> medium;
    		if (std::cin.fail() || medium <= 0) {
        		std::cout << "Invalid input. Please enter a positive number.\n";
        		std::cin.clear();
        		std::cin.ignore(); // Simplified ignoring mechanism
    		} else {
        	break;
    		}
		}		
		while (true) { // handle invalid input
    		std::cout << "Enter price of large size (16oz): ";
    		std::cin >> large;
    		if (std::cin.fail() || large <= 0) {
        		std::cout << "Invalid input. Please enter a positive number.\n";
        		std::cin.clear();
        		std::cin.ignore(); // Consistent usage for simplicity
    		} else {
        		break;
    		}
		}
		if (small > 0 && medium > 0 && large > 0){
			coffee new_coffee(name, small, medium, large);
        	s.get_menu().add_coffee(new_coffee); 
        	s.get_menu().add_coffee_to_file("menu.txt");
            std::cout << "This new drink has been successfully added to the coffee menu!" << std::endl;
		} else {
			std::cout << "Invalid input." << std::endl;
		}
	} else if (option == 3) {
		// Guide user through removing a coffee from the menu
		display_menu(s);
    	int index;
		while (true) { // handle invalid input
    		std::cout << "Which of the drinks above from our menu would you like to remove?\nEnter 1-" << s.get_menu().get_num_coffees() << ": ";
    		std::cin >> index;
    		if (std::cin.fail() || index <= 0) {
        		std::cout << "Invalid input. Please enter a positive number.\n";
        		std::cin.clear();
        		std::cin.ignore(); 
    		} else {
        		break;
    		}
		}
		if (index > 0 && index < s.get_menu().get_num_coffees()){
			s.get_menu().remove_coffee(index - 1);  
    		s.get_menu().delete_coffee_file("menu.txt");  
    		std::cout << "This drink has been successfully removed from the menu!" << std::endl;
		} else {
			std::cout << "Invalid Input" << std::endl;
		}
	} else if (option == 4) {
		// Guide user through searching the menu by coffee name
		std::string coffee_name;
    	std::cout << "Enter the coffee name: ";
    	std::cin >> coffee_name;

    	const coffee* found_coffee = s.get_menu().find_coffee_by_name(coffee_name);
    	if (found_coffee) {
        std::cout << "Results: " << std::endl;
        std::cout << "1. " << found_coffee->get_name() << "\n"
                  << "Small: " << found_coffee->get_small_cost() << "\n"
                  << "Medium: " << found_coffee->get_medium_cost() << "\n"
                  << "Large: " << found_coffee->get_large_cost() << std::endl;
    	} else {
        	std::cout << "Sorry, we don’t have that product at the moment." << std::endl;
    	}
	} else if (option == 5) {
		// Guide user through searching the menu by coffee price
		double budget;
		while (true) { // handle invalid input
    		std::cout << "Enter your budget for one drink, and I will list out our products that are cheaper or equal to your budget: ";
			std::cin >> budget;
    		if (std::cin.fail() || budget <= 0) {
        		std::cout << "Invalid input. Please enter a positive number.\n";
        		std::cin.clear();
        		std::cin.ignore(); 
    		} else {
        		break;
    		}
		}
		if (budget > 0){
			s.get_menu().find_coffees_by_price(budget);
		} else {
			std::cout << "Invalid input" << std::endl;
		}
		
	} else if (option == 6) {
		// Guide user through placing an order
		display_menu(s);
		s.take_order();
	} 
}