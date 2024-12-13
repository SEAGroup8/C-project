#ifndef GROCERY_H
#define GROCERY_H

#include "product.h"

class Grocery : public Product {
public:
    Grocery(std::string name, double p, int qty) : Product(name, p, qty) {}

    void displayInfo() const override {
        std::cout << "Grocery - " << productName << ", Price: $" << price << ", Stock: " << stockQuantity << std::endl;
    }

    double calculateDiscount() const override {
        return price * 0.10; // 10% discount on groceries
    }
};

#endif // GROCERY_H
