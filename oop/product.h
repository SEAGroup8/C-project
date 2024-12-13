#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>

class Product {
protected:
    std::string productName;
    double price;
    int stockQuantity;

public:
    Product(std::string name, double p, int qty) 
        : productName(name), price(p), stockQuantity(qty) {}

    virtual ~Product() {}

    virtual void displayInfo() const {
        std::cout << "Product: " << productName << ", Price: $" << price << ", Stock: " << stockQuantity << std::endl;
    }

    virtual double calculateDiscount() const = 0; // Abstract method

    std::string getName() const { return productName; }
    double getPrice() const { return price; }
    int getStock() const { return stockQuantity; }
};

#endif
