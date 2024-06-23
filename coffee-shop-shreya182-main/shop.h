#ifndef SHOP_H
#define SHOP_H

#include <string>

#include "menu.h"
#include "order.h"

class shop {
private:
	menu m;

	std::string phone;
	std::string address;
	double revenue = 0;

	// Number of orders
	int num_orders = 0;

	// Base address of order array (nullptr if array is empty)
	order* orders = nullptr;
	
	double* coffee_revenue = nullptr;
	int* coffee_order_count = nullptr;


public:
	/*
	 * NOTE: THIS IS A REQUIRED FUNCTION. DO NOT ALTER ITS PROTOTYPE.
	 *		YOU MUST IMPLEMENT IT IN `shop.cpp` OR SET IT TO `default`.
	 *		THIS FUNCTION IS USED BY THE BIG 3 TESTING SCRIPT.
	 * Name: shop (default constructor)
	 * Description: Constructs a shop with a defaultly-constructed menu,
	 *		an empty phone number and address, 0 revenue, and no orders.
	 */
	shop();
	shop(const shop& other);
	shop& operator=(const shop& other);
	~shop();

	/*
	 * NOTE: THIS IS A REQUIRED FUNCTION. DO NOT ALTER ITS PROTOTYPE.
	 *		YOU MUST IMPLEMENT IT IN `shop.cpp`. THIS FUNCTION IS USED
	 *		BY THE BIG 3 TESTING SCRIPT.
	 * Name: add_coffee_to_menu
	 * Description: Adds a coffee to the shop's menu
	 * Parameters:
	 *		c (const coffee&): The coffee to add to the shop's menu
	 * Post conditions: Coffee added to menu
	 */
	void add_coffee_to_menu(const coffee& c);

	/*
	 * NOTE: THIS IS A REQUIRED FUNCTION. DO NOT ALTER ITS PROTOTYPE.
	 *		YOU MUST IMPLEMENT IT IN `shop.cpp`. THIS FUNCTION IS USED
	 *		BY THE BIG 3 TESTING SCRIPT.
	 * Name: add_order
	 * Description: Adds an order to the order array
	 * Parameters:
	 *		o (const order&): The order to add to the array
	 * Post conditions: Order added to array (array may need to be
	 *		reallocated, and num_orders should be incremented by 1)
	 */
	void add_order(const order& o);
	/*
	 * Name: resize_orders
	 * Description: allocate a bigger array for additonal orders
	 * Post conditions: new bigger array created
	 */
	void resize_orders();
	/*
	 * Name: update_revenue
	 * Description: Update the shop revenue amount
	 * Parameters:
	 *		amount (double): The revenue of the shop to be updated
	 */
	void update_revenue(double amount);
	/*
	 * Name: save_orders_to_file
	 * Description: Write to the orders file
	 */
	void save_orders_to_file() const;
	/*
	 * Name: display_orders
	 * Description: Display orders for option 1 to terminal
	 */
	void display_orders() const;
	/*
	 * Name: take_order
	 * Description: Get users order and place order
	 * Post conditions: Order placed
	 */
	void take_order();
	/*
	 * Name: remove_coffee_menu
	 * Description: calls the menu class remove coffee function
	 * Parameters:
	 *		index (int): index of coffee to remove
	 * Post conditions: Coffee removed from menu
	 */
	void remove_coffee_menu(int index);
	/*
	 * Name: populate_from_file
	 * Description: store values from shop_info.txt into variables to use elsewhere
	 * Parameters:
	 *		file (ifstream): the file stream to read in from
	 */
	void populate_from_file(std::ifstream& file);/*
	 * Name: populate_menu_from_file
	 * Description: store values from menu.txt into variables to use elsewhere
	 * Parameters:
	 *		filename (string): The name of the file to read in from
	 */
	void populate_menu_from_file(const std::string& filename);
	/*
	 * Name: save_menu
	 * Description: calls add_coffee_to_file to update the menu.txt
	 * Post conditions: Menu.txt updated to include new coffee
	 */
	void save_menu() const;
	/*
	 * Name: display_additional_info
	 * Description: find and display the best seller and top 3 popular drinks
	 */
	void display_additional_info() const;
	// Getter for phone number
    std::string get_phone() const;

    // Getter for address
    std::string get_address() const;

    // Getter for revenue
    double get_revenue() const;

	//Getter for menu
	menu& get_menu();
};

#endif