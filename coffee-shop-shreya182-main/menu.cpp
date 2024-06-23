#include "menu.h"
#include <iostream>
#include <fstream>
#include <iomanip>

menu::menu(){
}
// Copy constructor
menu::menu(const menu& other) : num_coffees(other.num_coffees), capacity(other.num_coffees) {
    coffees = new coffee[capacity];
    for (int i = 0; i < num_coffees; i++) {
        coffees[i] = other.coffees[i];
    }
}

// Assignment operator
menu& menu::operator=(const menu& other) {
    if (this != &other) {
        coffee* newCoffees = new coffee[other.capacity];
        for (int i = 0; i < other.num_coffees; i++) {
            newCoffees[i] = other.coffees[i];
        }
        delete[] coffees;
        coffees = newCoffees;
        num_coffees = other.num_coffees;
        capacity = other.capacity;
    }
    return *this;
}

menu::~menu(){
    delete[] coffees;
    coffees = nullptr;
}
void menu::add_coffee(const coffee& c) {
    if (num_coffees >= capacity) {
        int new_capacity = capacity == 0 ? 4 : capacity * 2;
        coffee* new_coffees = new coffee[new_capacity];
        for (int i = 0; i < num_coffees; i++) {
            new_coffees[i] = coffees[i];
        }
        delete[] coffees;
        coffees = new_coffees;
        capacity = new_capacity;
    }
    coffees[num_coffees++] = c;
    latest_coffee = c; // Update the latest coffee
}
void menu::remove_coffee(int index){
    if (index >= 0 && index < num_coffees) {
        for (int i = index; i < num_coffees - 1; i++) {
            coffees[i] = coffees[i + 1];  // Shift coffees down in the array
        }
        num_coffees--;  // reduce count of coffees
    }
}
const coffee* menu::find_coffee_by_name(const std::string& name) const {
    for (int i = 0; i < num_coffees; i++) {
        if (coffees[i].get_name() == name) {
            return &coffees[i];
        }
    }
    return nullptr; // Return nullptr if no coffee is found
}
void menu::find_coffees_by_price(double max_price) const {
    bool found = false;
    std::cout << std::fixed << std::setprecision(2);  // Ensure prices are displayed with two decimal places

    for (int i = 0; i < num_coffees; i++) {
        const coffee& c = coffees[i];
        std::string listings;  // to collect valid price listings for each coffee
        bool listed = false;

        std::cout << i + 1 << ". " << c.get_name() << std::endl;
        // Check each size and append to listings if under budget
        if (c.get_small_cost() <= max_price) {
            std::cout << " Small – $" << c.get_small_cost() << std::endl;
            listed = true;
        }
        if (c.get_medium_cost() <= max_price) {
            std::cout << " Medium – $" << c.get_medium_cost() << std::endl;
            listed = true;
        }
        if (c.get_large_cost() <= max_price) {
            std::cout << " Large – $" << c.get_large_cost() << std::endl;
            listed = true;
        }

        if (listed) {
            found = true;
            std::cout << std::endl;
        }
    }

    if (!found) {
        std::cout << "No coffees found within the budget of $" << max_price << std::endl;
    }
}

void menu::delete_coffee_file(const std::string& filename) const {
    std::ofstream file(filename, std::ios::trunc);  // Open file in truncate mode to overwrite existing data
    if (!file) {
        std::cerr << "Failed to open " << filename << " for writing." << std::endl;
        return;
    }
    // Write the updated number of coffees first
    file << num_coffees << std::endl;

    // Write all remaining coffees to the file
    for (int i = 0; i < num_coffees; ++i) {
        file << coffees[i].get_name() << " "
             << std::fixed << std::setprecision(2) << coffees[i].get_small_cost() << " "
             << std::fixed << std::setprecision(2) << coffees[i].get_medium_cost() << " "
             << std::fixed << std::setprecision(2) << coffees[i].get_large_cost() << std::endl;
    }

    file.close();
}
void menu::add_coffee_to_file(const std::string& filename) const {
    std::ofstream file(filename, std::ios::trunc);  // Open in truncate mode to overwrite
    if (!file) {
        std::cerr << "Failed to open " << filename << " for writing." << std::endl;
        return;
    }
    // Write the number of coffees at the top of the file
    file << num_coffees << std::endl;

    // Loop through all coffees and write their details
    for (int i = 0; i < num_coffees; ++i) {
        const coffee& c = coffees[i];
        file << c.get_name() << " "
             << std::fixed << std::setprecision(2) << c.get_small_cost() << " "
             << std::fixed << std::setprecision(2) << c.get_medium_cost() << " "
             << std::fixed << std::setprecision(2) << c.get_large_cost() << std::endl;
    }

    file.close();
}
void menu::display_menu() const {
    //iterate through coffees and display
    for (int i = 0; i < num_coffees; ++i) {
        std::cout << (i + 1) << ". " << coffees[i].get_name() << std::endl;
    }
}
int menu::find_coffee_index(const std::string& name) const {
    for (int i = 0; i < num_coffees; i++) {
        if (coffees[i].get_name() == name) {
            return i;
        }
    }
    return -1;  // Not found
}

double menu::get_coffee_price(const std::string& name, char size) const {
    int index = find_coffee_index(name);
    if (index != -1) {
        const coffee& c = coffees[index];
        switch (size) {
            case 's': return c.get_small_cost();
            case 'm': return c.get_medium_cost();
            case 'l': return c.get_large_cost();
            default: return 0.0;
        }
    }
    return 0.0;  // Coffee not found or invalid size
}