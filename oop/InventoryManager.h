#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <vector>
#include <memory>
#include "product.h"

class InventoryManager {
protected:
    std::vector<std::shared_ptr<Product>> inventory;

public:
    virtual void addProduct(std::shared_ptr<Product> product) = 0;
    virtual void displayAllProducts() const = 0;
    virtual void saveInventoryToFile() = 0;
    virtual void loadInventoryFromFile() = 0;
};

#endif
