#include <iostream>
#include "grocery.h"
#include "product.h"
#include "electronics.h"
#include "supermarketinventory.h"

int main() {
    SupermarketInventory inventory;

    try {
        // Add products through terminal input
        std::string name;
        double price;
        int quantity;
        int choice;
        
        std::cout << "Enter product type (1 for Grocery, 2 for Electronics): ";
        std::cin >> choice;

        // Input the product details
        std::cout << "Enter product name: ";
        std::cin.ignore();  // To ignore the newline character from previous input
        std::getline(std::cin, name);

        std::cout << "Enter product price: ";
        std::cin >> price;

        std::cout << "Enter product quantity: ";
        std::cin >> quantity;

        if (choice == 1) {
            // Adding Grocery product
            inventory.addProduct(std::make_shared<Grocery>(name, price, quantity));
        } else if (choice == 2) {
            // Adding Electronics product
            inventory.addProduct(std::make_shared<Electronics>(name, price, quantity));
        } else {
            throw std::invalid_argument("Invalid product type.");
        }

        // Display all products
        inventory.displayAllProducts();

        // Save the inventory to a file
        inventory.saveInventoryToFile();

        // Load the inventory from the file (simulating persistence)
        inventory.loadInventoryFromFile();
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unexpected error occurred." << std::endl;
    }

    return 0;
}
