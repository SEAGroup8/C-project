#include <iostream>
#include "grocery.h"
#include "product.h"
#include "electronics.h"
#include "supermarketinventory.h"

int main() {
    SupermarketInventory inventory;

    inventory.addProduct(std::make_shared<Grocery>("Apple", 1.2, 50));
    inventory.addProduct(std::make_shared<Electronics>("Laptop", 999.99, 10));

    inventory.displayAllProducts();

    inventory.saveInventoryToFile();

    inventory.loadInventoryFromFile();

    return 0;
}
