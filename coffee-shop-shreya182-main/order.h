#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <fstream>

class order {
private:
	static int next_order_number;
	int order_number;
	std::string coffee_name;
	char coffee_size = 0;
	int quantity = 0;
	double price;
public:
	/* 
	 * NOTE: THIS IS A REQUIRED FUNCTION. DO NOT ALTER ITS PROTOTYPE.
	 *		YOU MUST IMPLEMENT IT IN `order.cpp` OR SET IT TO `default`.
	 *		THIS FUNCTION IS USED BY THE BIG 3 TESTING SCRIPT.
	 * Name: order (default constructor)
	 * Description: Constructs an order with order_number 0,
	 *		empty coffee name, null (0) coffee size, and 0
	 *		quantity.
	 */
	order();
	// Setter for name
    void set_coffee_name(const std::string& name) { coffee_name = name; }
	// Setter for size
    void set_coffee_size(char size) { coffee_size = size; }
	// Setter for quantity
    void set_quantity(int qty) { quantity = qty; }
	// Setter for price
    void set_price(double p) { price = p; }


	// Getter for order number to iterate
	static int get_next_order_number() { return next_order_number++; }
	// Getter for order number
    int get_order_number () const;
	// Getter for name
    std::string get_coffee_name() const { return coffee_name; }
	// Getter for size
    char get_coffee_size() const { return coffee_size; }
	// Getter for quantity
    int get_quantity() const { return quantity; }
	// Getter for price
    double get_price() const { return price; }

	/*
	 * Name: total_cost
	 * Description: calculates and returns the total cost of an order
	 */
	double total_cost() const;
	/*
	 * Name: write_to_file
	 * Description: write the orders to a file
	 * Parameters:
	 *		out (ostream): The output stream to write to
	 * Post conditions: orders.txt created and populated with orders
	 */
	void write_to_file(std::ostream& out) const;
};

#endif
