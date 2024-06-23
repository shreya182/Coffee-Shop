#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "coffee.h"

class menu {
private:
	// Number of coffees in menu
	int num_coffees = 0;
	int capacity = 0;
	coffee latest_coffee;

	// Base address of coffee array (nullptr if array is empty)
	coffee* coffees = nullptr;
public:
	/*
	 * NOTE: THIS IS A REQUIRED FUNCTION. DO NOT ALTER ITS PROTOTYPE.
	 *		YOU MUST IMPLEMENT IT IN `menu.cpp` OR SET IT TO `default`.
	 *		THIS FUNCTION IS USED BY THE BIG 3 TESTING SCRIPT.
	 * Name: menu (default constructor)
	 * Description: Constructs a menu with an empty coffee array
	 */
	menu();
	menu(const menu& other); // Copy constructor
    menu& operator=(const menu& other); // Copy assignment operator
	~menu();
	/*
	 * NOTE: THIS IS A REQUIRED FUNCTION. DO NOT ALTER ITS PROTOTYPE.
	 *		YOU MUST IMPLEMENT IT IN `menu.cpp`. THIS FUNCTION IS USED
	 *		BY THE BIG 3 TESTING SCRIPT.
	 * Name: add_coffee
	 * Description: Adds a coffee to the coffee array
	 * Parameters:
	 *		c (const coffee&): The coffee to add to the array
	 * Post conditions: Coffee added to array (array may need to be
	 *		reallocated, and num_coffees should be incremented by 1)
	 */
	void add_coffee(const coffee& c);
	/*
	 * Name: remove_coffee
	 * Description: Removes a coffee from the coffee array
	 * Parameters:
	 *		index (int): The index of the coffee to remove
	 * Post conditions: Coffee removed from array (array may need to be
	 *		reallocated, and num_coffees should be decremented by 1)
	 */
	void remove_coffee(int index);
	/*
	 * Name: delete_coffe_file
	 * Description: Update menu.txt by removing coffee
	 * Parameters:
	 *		filename (string): The name of the file to write to
	 * Post conditions: Menu.txt updated to no longer include removed coffee
	 */
	void delete_coffee_file(const std::string& filename) const;
	/*
	 * Name: find_coffee_by_name
	 * Description: Search for coffee in array
	 * Parameters:
	 *		name (string): The name of coffee to search for
	 */
	const coffee* find_coffee_by_name(const std::string& name) const;
	/*
	 * Name: find_coffees_by_price
	 * Description: Search for coffees within budget
	 * Parameters:
	 *		max_price (double): The user's budget to find coffees for
	 */
	void find_coffees_by_price(double max_price) const;
	/*
	 * Name: add_coffee_to_file
	 * Description: Update menu.txt by adding coffee
	 * Parameters:
	 *		filename (string): The name of the file to write to
	 * Post conditions: Menu.txt updated to include added coffee
	 */
	void add_coffee_to_file(const std::string& filename) const;
	/*
	 * Name: display_menu
	 * Description: display the full menu to the terminal
	 */
	void display_menu() const;
	/*
	 * Name: get_num_coffees
	 * Description: getter to get number of coffees
	 */
	int get_num_coffees() const{ return num_coffees; }
	/*
	 * Name: get_coffee
	 * Description: getter to get coffee
	 * Parameters:
	 *		index (int): The index of the coffee trying to get
	 */
    const coffee& get_coffee(int index) const{
    if (index < 0 || index >= num_coffees) {
            throw std::out_of_range("Index out of range");
        }
    return coffees[index];
}
	int find_coffee_index(const std::string& name) const;
	double get_coffee_price(const std::string& name, char size) const;
};

#endif