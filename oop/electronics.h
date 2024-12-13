#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "product.h"

class Electronics : public Product {
public:
    Electronics(std::string name, double p, int qty) : Product(name, p, qty) {}

    void displayInfo() const override {
        std::cout << "Electronics - " << productName << ", Price: $" << price << ", Stock: " << stockQuantity << std::endl;
    }

    double calculateDiscount() const override {
        return price * 0.15; // 15% discount on electronics
    }
};

#endif
