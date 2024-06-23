#ifndef COFFEE_H
#define COFFEE_H

#include <string>

class coffee {
private:
    std::string name;
    double small_cost;
    double medium_cost;
    double large_cost;

public:
    // Default constructor
    coffee();
    // Parameterized constructor
    coffee(const std::string& name, double small, double medium, double large)
        : name(name), small_cost(small), medium_cost(medium), large_cost(large) {}

    // Getter for name
    std::string get_name() const;
    // Getter for small size cost
    double get_small_cost() const;
    // Getter for medium size cost
    double get_medium_cost() const;
    // Getter for large size cost
    double get_large_cost() const;
    
};

#endif 

