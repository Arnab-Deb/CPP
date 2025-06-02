
#include <iostream>
#include <fstream>  
#include <vector>
#include <string>

using namespace std;

// Class for Cloth
class Cloth {
public:
    string name;
    string size;
    double price;

    Cloth(string n, string s, double p) : name(n), size(s), price(p) {}
};

// Class for Category
class Category {
public:
    string categoryName;
    vector<Cloth> clothes;

    Category(string name) : categoryName(name) {}

    // Add clothes to the category
    void addCloth(string clothName, string size, double price) {
        clothes.push_back(Cloth(clothName, size, price));
    }

    // Display clothes in the category
    void displayClothes() {
        for (int i = 0; i < clothes.size(); i++) {
            cout << i + 1 << ". " << clothes[i].name << " (Size: " << clothes[i].size << ") - Tk" << clothes[i].price << endl;
        }
    }

    // Get cloth by index
    Cloth getCloth(int index) {
        return clothes[index];
    }

    int getSize() {
        return clothes.size();
    }
};

// Class for the Shopping Cart
class Cart {
public:
    struct CartItem {
        Cloth cloth;
        int quantity;

        CartItem(Cloth c, int q) : cloth(c), quantity(q) {}
    };

    vector<CartItem> cartItems;
    string customerName;
    string customerPhone;
    string customerAddress; 
    string paymentMethod;

    Cart() {}

    // Add cloth to the cart
    void addItem(Cloth cloth, int quantity) {
        cartItems.push_back(CartItem(cloth, quantity));
    }

    // Calculate total price of the cart
      double calculateTotal()
{
    double total = 0;
    for (size_t i = 0; i < cartItems.size(); ++i)
    {
        total += cartItems[i].cloth.price * cartItems[i].quantity;
    }
    return total;
}

    // Generate and display the bill
    void generateBill(string shopName) {
        cout << "\n===== " << shopName << " =====\n";
        cout << "\nCustomer Name: " << customerName << endl;
        cout << "Phone Number: " << customerPhone << endl;
        cout << "Address: " << customerAddress << endl;  // Show customer address
        cout << "Order details:\n";

        // Print order details
        for (int i = 0; i < cartItems.size(); i++) {
            CartItem &item = cartItems[i];
            cout << item.cloth.name << " (Size " << item.cloth.size << ") x"
                 << item.quantity << " - Tk" << item.cloth.price * item.quantity << endl;
        }

        cout << "Total: Tk" << calculateTotal() << endl;
        cout << "Payment Method: " << paymentMethod << endl;
        cout << "==============================\n";

        // Save to file
        saveBillToFile(shopName);
    }

    // Set the payment method
    void setPaymentMethod(string method) {
        paymentMethod = method;
    }

    // Set the customer details
    void setCustomerDetails(string name, string phone, string address) {
        customerName = name;
        customerPhone = phone;
        customerAddress = address;
    }

    // Save the bill to a file
    void saveBillToFile(string shopName) {
        ofstream outFile("CustomerBill.txt");

        if (!outFile) {
            cout << "Error opening file for writing!" << endl;
            return;
        }

        // Write customer details and order to file
        outFile << "===== " << shopName << " =====\n";
        outFile << "Customer Name: " << customerName << endl;
        outFile << "Phone Number: " << customerPhone << endl;
        outFile << "Address: " << customerAddress << endl;
        outFile << "Order details:\n";

        // Write each item in the order
        for (int i = 0; i < cartItems.size(); i++) {
            CartItem &item = cartItems[i];
            outFile << item.cloth.name << " (Size " << item.cloth.size << ") x"
                    << item.quantity << " - Tk" << item.cloth.price * item.quantity << endl;
        }

        outFile << "Total: Tk" << calculateTotal() << endl;
        outFile << "Payment Method: " << paymentMethod << endl;
        outFile << "==============================\n";


outFile.close();  // Close the file after writing

        cout << "Bill saved to CustomerBill.txt\n";
    }
};

// Main function
int main() {
    cout << "Welcome to CLOTH_ME" << endl;
    const string shopName = "Cloth-Me";  // Add shop name feature

    // Men and Women Categories
    Category men("Men");
    Category women("Women");

    // Adding clothes to Men Category
    men.addCloth("Shirt", "M", 1000.00);
    men.addCloth("Shirt", "L", 1000.00);
    men.addCloth("Polo T-Shirt", "M", 800.00);
    men.addCloth("Polo T-Shirt", "L", 800.00);
    men.addCloth("Punjabi", "M", 1200.00);
    men.addCloth("Punjabi", "L", 1200.00);

    // Adding clothes to Women Category
    women.addCloth("Saree", "M", 1500.00);
    women.addCloth("Saree", "L", 1500.00);
    women.addCloth("Shalwar Kameez", "M", 1800.00);
    women.addCloth("Shalwar Kameez", "L", 1800.00);
    women.addCloth("Kurta", "M", 1300.00);
    women.addCloth("Kurta", "L", 1300.00);

    Cart cart;

    int categoryChoice, clothChoice, quantity;
    do {
        cout << "\nSelect Category:\n";
        cout << "1. Men\n";
        cout << "2. Women\n";
        cout << "0. Checkout\n";
        cout << "3. Exit without buying\n";  // Add exit option
        cout << "Enter choice: ";
        cin >> categoryChoice;

        if (categoryChoice == 3) {  // Check for exit condition
            cout << "Thank you for visiting CLOTH_ME! Have a great day!" << endl;
            return 0;  // Exit the program
        }

        if (categoryChoice == 1 || categoryChoice == 2) {
            Category selectedCategory = (categoryChoice == 1) ? men : women;

            selectedCategory.displayClothes();
            cout << "Select Cloth (0 to go back): ";
            cin >> clothChoice;

            if (clothChoice > 0 && clothChoice <= selectedCategory.getSize()) {
                cout << "Enter quantity: ";
                cin >> quantity;

                cart.addItem(selectedCategory.getCloth(clothChoice - 1), quantity);
            }
        }

    } while (categoryChoice != 0);

    // Ask for payment method
    int paymentChoice;
    cout << "\nSelect Payment Method:\n";
    cout << "1. Cash on Delivery\n";
    cout << "2. Online Payment\n";
    cout << "Enter choice: ";
    cin >> paymentChoice;

    if (paymentChoice == 1) {
        cart.setPaymentMethod("Cash on Delivery");
    } else if (paymentChoice == 2) {
        cart.setPaymentMethod("Online Payment");
    } else {
        cout << "Invalid choice! Defaulting to Cash on Delivery.\n";
        cart.setPaymentMethod("Cash on Delivery");
    }

    // Ask for customer name, phone number, and address after checkout
    string customerName, customerPhone, customerAddress;
    cin.ignore();  
    cout << "Enter your name: ";
    getline(cin, customerName);
    cout << "Enter your phone number: ";
    getline(cin, customerPhone);
    cout << "Enter your address: ";
    getline(cin, customerAddress);

    cart.setCustomerDetails(customerName, customerPhone, customerAddress);

    // Generate the final bill
    cart.generateBill(shopName);

    return 0;
}
