#ifndef SUPERMARKETINVENTORY_H
#define SUPERMARKETINVENTORY_H

#include "inventorymanager.h"
#include <fstream>

class SupermarketInventory : public InventoryManager {
public:
    void addProduct(std::shared_ptr<Product> product) override {
        inventory.push_back(product);
    }

    void displayAllProducts() const override {
        for (const auto& product : inventory) {
            product->displayInfo();
        }
    }

    void saveInventoryToFile() override {
        std::ofstream outFile("inventory.txt");
        if (outFile.is_open()) {
            for (const auto& product : inventory) {
                outFile << product->getName() << " "
                        << product->getPrice() << " "
                        << product->getStock() << std::endl;
            }
            outFile.close();
        }
    }

    void loadInventoryFromFile() override {
        std::ifstream inFile("inventory.txt");
        if (inFile.is_open()) {
            std::string name;
            double price;
            int quantity;
            while (inFile >> name >> price >> quantity) {
                inventory.push_back(std::make_shared<Product>(name, price, quantity));
            }
            inFile.close();
        }
    }
};

#endif // SUPERMARKETINVENTORY_H
