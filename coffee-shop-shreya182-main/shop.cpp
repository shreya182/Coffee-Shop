#include "shop.h"
#include <iostream>
#include <fstream>
#include <iomanip>

shop::shop(){
    orders = new order[10];  // Start with an initial capacity
    coffee_revenue = new double[m.get_num_coffees()];
    coffee_order_count = new int[m.get_num_coffees()];
}
shop::shop(const shop& other) : m(other.m), phone(other.phone), address(other.address), revenue(other.revenue), num_orders(other.num_orders), orders(new order[other.num_orders]) {
    for (int i = 0; i < num_orders; ++i) { //copy constructor
        orders[i] = other.orders[i];
    }
}

shop& shop::operator=(const shop& other) { // Copy assignment operator
    if (this != &other) {
        menu newMenu = other.m;  // Use copy assignment of menu
        order* newOrders = new order[other.num_orders];
        for (int i = 0; i < other.num_orders; i++) {
            newOrders[i] = other.orders[i];
        }
        delete[] orders;  // Free old orders
        orders = newOrders;
        phone = other.phone;
        address = other.address;
        revenue = other.revenue;
        num_orders = other.num_orders;
        m = newMenu;  // Assign the new menu
    }
    return *this;
}

shop::~shop(){ // deconstructor
    delete[] orders;
    orders = nullptr;
    delete[] coffee_revenue;
    coffee_revenue = nullptr;
    delete[] coffee_order_count;
    coffee_order_count = nullptr;
}
void shop::add_coffee_to_menu(const coffee& c){
    m.add_coffee(c);
}
void shop::remove_coffee_menu(int index){
    m.remove_coffee(index);
}
void shop::add_order(const order& o){
    if (num_orders == 10){
        resize_orders();
    }
    orders[num_orders++] = o;
    update_revenue(o.total_cost());
}
void shop::display_orders() const { 
    if (num_orders == 0) {
        std::cout << "(No orders to display)" << std::endl;
        return;
    }

    //iterate through orders and output
    for (int i = 0; i < num_orders; ++i) {
        const order& ord = orders[i];
        std::cout << ord.get_order_number() << " " << ord.get_coffee_name()
                  << " " << ord.get_coffee_size() << " " << ord.get_quantity() << std::endl;
    }
}
void shop::resize_orders() {
    //double size and copy to new array
    int new_capacity = 10 * 2;
    order* new_orders = new order[new_capacity];
    for (int i = 0; i < num_orders; ++i) {
        new_orders[i] = orders[i];
    }
    delete[] orders;
    orders = new_orders;
    new_capacity = 10;
}
void shop::update_revenue(double amount) { 
    revenue += amount;
}
void shop::save_orders_to_file() const {
    std::ofstream file("orders.txt");
    if (!file) {
        std::cerr << "Failed to open orders.txt for writing." << std::endl;
        return;
    }
    //write orders to orders.txt
    file << num_orders << std::endl;  
    for (int i = 0; i < num_orders; ++i) {
        orders[i].write_to_file(file);
    }
}
void shop::take_order() {
    menu& m = get_menu();
    int index, quantity;
    char size;
    // getting user input

    while (true) {
    	std::cout << "Select a coffee by number: ";
        std::cin >> index;
    	if (std::cin.fail() || index <= 0) {
        	std::cout << "Invalid input. Please enter a positive number.\n";
        	std::cin.clear();
        	std::cin.ignore(); 
    	} else {
        	break;
    	}
	}

    coffee selected_coffee = m.get_coffee(index - 1); 
    while (true) { // handle invalid input
    	std::cout << "Enter size (s, m, l): ";
        std::cin >> size;
    	if (std::cin.fail() || size != 's' && size!= 'm' && size != 'l') {
        	std::cout << "Invalid input. Please enter s, m, or l.\n";
        	std::cin.clear();
        	std::cin.ignore(); 
    	} else {
        	break;
    	}
	}
    while (true) { // handle invalid input
    	std::cout << "Enter quantity: ";
        std::cin >> quantity;
    	if (std::cin.fail() || quantity <= 0) {
        	std::cout << "Invalid input. Please enter a positive number.\n";
        	std::cin.clear();
        	std::cin.ignore(); 
    	} else {
        	break;
    	}
    }

    double cost = 0;
    // calculate cost of order
    if (size == 's' && index <= m.get_num_coffees() && index > 0 && quantity > 0){
        cost = selected_coffee.get_small_cost() * quantity;
    } else if (size == 'm' && index <= m.get_num_coffees() && index > 0 && quantity > 0){
        cost = selected_coffee.get_medium_cost() * quantity;
    } else if (size == 'l' && index <= m.get_num_coffees() && index > 0 && quantity > 0){
        cost = selected_coffee.get_large_cost() * quantity;
    } else {
        std::cout << "Invalid input" << std::endl;
    }
    
    if (cost != 0){
        std::cout << "Total cost is: $" << std::fixed << std::setprecision(2) << cost << "\nConfirm order (1-yes, 0-no): ";
        int confirm;
        std::cin >> confirm;

        if (confirm == 1) { // place order
            order new_order;
            new_order.set_coffee_name(selected_coffee.get_name());
            new_order.set_coffee_size(size);
            new_order.set_quantity(quantity);
            new_order.set_price(cost / quantity);
            add_order(new_order);
            std::cout << "Order placed successfully. Your order number is: " << new_order.get_order_number() << "\n";
        } else {
            std::cout << "Invalid input. Order canceled.\n";
        }
    }
}
void shop::populate_from_file(std::ifstream& file){
    std::getline(file, phone);
    std::getline(file, address);
    file.close();
}
void shop::populate_menu_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    int numCoffees = 0;
    file >> numCoffees; // Read the number of coffees at the start of the file

    std::string name;
    double small, medium, large;

    // Read each coffee entry from the file
    for (int i = 0; i < numCoffees; i++) {
        if (file >> name >> small >> medium >> large) {
            coffee new_coffee(name, small, medium, large);
            m.add_coffee(new_coffee);
        } else {
            std::cerr << "Error reading coffee data for coffee number " << i + 1 << std::endl;
            break;
        }
    }

    if (file.bad()) {
        std::cerr << "An error occurred while reading the file." << std::endl;
    } else if (!file.eof()) {
        std::cerr << "Not all data could be read, and the end of the file was not reached." << std::endl;
    }
    file.close();
}
void shop::display_additional_info() const { //find best seller and 3 popular drinks
    if (num_orders == 0) {
        std::cout << "No statistics to show yet" << std::endl;
        std::cout << "\n";
        return;
    }
    int* orderCounts = new int[m.get_num_coffees()]();
    double* revenueCounts = new double[m.get_num_coffees()]();
    //iterate through orders and populate arrays
    for (int i = 0; i < num_orders; ++i) {
        int index = m.find_coffee_index(orders[i].get_coffee_name());
        if (index != -1) {
            double price = m.get_coffee_price(orders[i].get_coffee_name(), orders[i].get_coffee_size());
            orderCounts[index] += orders[i].get_quantity();
            revenueCounts[index] += orders[i].get_quantity() * price;
        }
    }

    //determine best seller
    int bestSellerIndex = 0;
    for (int i = 1; i < m.get_num_coffees(); ++i) {
        if (revenueCounts[i] > revenueCounts[bestSellerIndex]) {
            bestSellerIndex = i;
        }
    }

    std::cout << "Best Seller: " << m.get_coffee(bestSellerIndex).get_name()
              << " with revenue $" << std::fixed << std::setprecision(2)
              << revenueCounts[bestSellerIndex] << std::endl;

    std::cout << "Top 3 Popular Drinks: " << std::endl;
    //determine 3 most popular drinks
    for (int j = 0; j < 3 && j < m.get_num_coffees(); ++j) {
        int maxIndex = -1;
        for (int i = 0; i < m.get_num_coffees(); ++i) {
            if (maxIndex == -1 || orderCounts[i] > orderCounts[maxIndex]) {
                maxIndex = i;
            }
        }
        if (maxIndex != -1) {
            std::cout << j + 1 << ". " << m.get_coffee(maxIndex).get_name()
                      << " ordered " << orderCounts[maxIndex] << " times" << std::endl;
            orderCounts[maxIndex] = -1;
        }
    }
}

void shop::save_menu() const {
    m.add_coffee_to_file("menu.txt");  
}

std::string shop::get_phone() const {
    return phone;
}

std::string shop::get_address() const {
    return address;
}

double shop::get_revenue() const {
    return revenue;
}
menu& shop::get_menu() {
    return m;
}
