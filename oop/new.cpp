#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <sstream>

// Abstract Product class
class Product {
protected:
    std::string productName;
    double price;
    int stockQuantity;

public:
    // Constructor
    Product(std::string name, double p, int qty) 
        : productName(name), price(p), stockQuantity(qty) {}

    virtual ~Product() {}

    // function for displaying product info
    virtual void displayInfo() const {
        std::cout << "Product: " << productName << ", Price: $" << price << ", Stock: " << stockQuantity << std::endl;
    }

    // Abstract method to calculate discount
    virtual double calculateDiscount() const = 0;

    // Getters
    std::string getName() const { return productName; }
    double getPrice() const { return price; }
    int getStock() const { return stockQuantity; }

    // Setters
    void setName(const std::string& name) { productName = name; }
    void setPrice(double p) { price = p; }
    void setStock(int qty) { stockQuantity = qty; }
};

// Electronics class inheriting from Product
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

// Grocery class inheriting from Product
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

// InventoryManager class (abstract)
class InventoryManager {
protected:
    std::vector<std::shared_ptr<Product>> inventory;

public:
    virtual void addProduct(std::shared_ptr<Product> product) = 0;
    virtual void displayAllProducts() const = 0;
    virtual void saveInventoryToFile() = 0;
    virtual void loadInventoryFromFile() = 0;
};

// SupermarketInventory class inheriting from InventoryManager
class SupermarketInventory : public InventoryManager {
public:
    void addProduct(std::shared_ptr<Product> product) override {
        inventory.push_back(product);
    }

    void displayAllProducts() const override {
        for (const auto& product : inventory) {
            product->displayInfo();
            std::cout << "Discount: $" << product->calculateDiscount() << std::endl;
        }
    }

    void saveInventoryToFile() override {
        try {
            std::ofstream outFile("inventory.txt");
            if (!outFile.is_open()) {
                throw std::ios_base::failure("Failed to open file for saving inventory.");
            }

            for (const auto& product : inventory) {
                // Save product type as well (Electronics or Grocery)
                if (dynamic_cast<Electronics*>(product.get())) {
                    outFile << "Electronics ";
                } else if (dynamic_cast<Grocery*>(product.get())) {
                    outFile << "Grocery ";
                }

                outFile << product->getName() << " "
                        << product->getPrice() << " "
                        << product->getStock() << std::endl;
            }

            outFile.close();
            std::cout << "Inventory saved successfully." << std::endl;
        } catch (const std::ios_base::failure& e) {
            std::cerr << "Error saving inventory: " << e.what() << std::endl;
        }
    }

    void loadInventoryFromFile() override {
        try {
            std::ifstream inFile("inventory.txt");
            if (!inFile.is_open()) {
                throw std::ios_base::failure("Failed to open file for loading inventory.");
            }

            std::string type, name;
            double price;
            int quantity;

            while (inFile >> type >> name >> price >> quantity) {
                // Determine the product type
                if (type == "Electronics") {
                    inventory.push_back(std::make_shared<Electronics>(name, price, quantity));
                } else if (type == "Grocery") {
                    inventory.push_back(std::make_shared<Grocery>(name, price, quantity));
                }
            }

            inFile.close();
            std::cout << "Inventory loaded successfully." << std::endl;
        } catch (const std::ios_base::failure& e) {
            std::cerr << "Error loading inventory: " << e.what() << std::endl;
        }
    }
};

// Main function
int main() {
    SupermarketInventory inventory;

    try {
        // Manual product entry
        std::string type, name;
        double price;
        int quantity;
        char choice;

        do {
            std::cout << "Enter product type (Electronics or Grocery): ";
            std::cin >> type;
            std::cin.ignore(); // Clear the input buffer

            std::cout << "Enter product name: ";
            std::getline(std::cin, name);

            std::cout << "Enter product price: ";
            std::cin >> price;

            std::cout << "Enter product quantity: ";
            std::cin >> quantity;

            if (type == "Electronics") {
                inventory.addProduct(std::make_shared<Electronics>(name, price, quantity));
            } else if (type == "Grocery") {
                inventory.addProduct(std::make_shared<Grocery>(name, price, quantity));
            } else {
                std::cout << "Invalid product type. Please enter 'Electronics' or 'Grocery'.\n";
                continue;
            }

            std::cout << "Do you want to add another product? (y/n): ";
            std::cin >> choice;
            std::cin.ignore(); // Clear the buffer

        } while (choice == 'y' || choice == 'Y');

        // Display all products and their information
        inventory.displayAllProducts();

        // Saving the inventory to a file
        inventory.saveInventoryToFile();

        // Loading the inventory from a file
        inventory.loadInventoryFromFile();
    } catch (const std::ios_base::failure& e) {
        std::cerr << "File operation error: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    }

    return 0;
}
