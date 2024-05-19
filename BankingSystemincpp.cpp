#include <iostream>
#include <vector>
#include <string>
#include <limits>

// Cross-platform function to clear the screen
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

class Customer {
public:
    std::string name;
    int customerID;
    Customer(std::string n, int id) : name(n), customerID(id) {}
};

class Account {
public:
    int accountNumber;
    double balance;
    std::vector<std::string> transactions;

    Account(int num, double bal) : accountNumber(num), balance(bal) {}
    void deposit(double amount) {
        balance += amount;
        transactions.push_back("Deposited: $" + std::to_string(amount));
        std::cout << "Deposited $" << amount << " successfully.\n";
    }
    void withdraw(double amount) {
        if (amount > balance) {
            std::cout << "Insufficient funds for withdrawal.\n";
            return;
        }
        balance -= amount;
        transactions.push_back("Withdrew: $" + std::to_string(amount));
        std::cout << "Withdrew $" << amount << " successfully.\n";
    }
    void printAccountDetails() {
        std::cout << "Account Number: " << accountNumber << "\n";
        std::cout << "Balance: $" << balance << "\n";
        std::cout << "Transactions:\n";
        for (std::vector<std::string>::iterator it = transactions.begin(); it != transactions.end(); ++it) {
            std::cout << *it << "\n";
        }
    }
};

class BankingServices {
public:
    std::vector<Customer> customers;
    std::vector<Account> accounts;
    void addCustomer(std::string name, int customerID) {
        customers.push_back(Customer(name, customerID));
    }
    void addAccount(int customerID, int accountNumber, double initialBalance) {
        accounts.push_back(Account(accountNumber, initialBalance));
        std::cout << "Account created successfully for customer ID " << customerID << ".\n";
    }
    Account* findAccount(int accountNumber) {
        for (std::vector<Account>::iterator it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->accountNumber == accountNumber) return &(*it);
        }
        return nullptr;
    }
};

void handleInvalidInput() {
    std::cin.clear(); // Clear error flag
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore incorrect input
    std::cout << "Invalid input. Please enter a valid number.\n";
}

int main() {
    BankingServices bank;
    bank.addCustomer("John Doe", 1);  // Example initial customer

    int choice; // Used in switch statement, needed throughout program
    // Declare other variables as needed within the switch cases to avoid unused variable warnings

    while (true) {
        clearScreen();
        std::cout << "\nBanking System Menu:\n";
        std::cout << "1. Create Account\n";
        std::cout << "2. Deposit Money\n";
        std::cout << "3. Withdraw Money\n";
        std::cout << "4. Show Account Details\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (!std::cin) {
            handleInvalidInput();
            continue;
        }

        switch (choice) {
            case 1: {
                int customerID;
                int accountNumber;
                double initialBalance;
                std::cout << "Enter customer ID: ";
                if (!(std::cin >> customerID)) {
                    handleInvalidInput();
                    continue;
                }
                std::cout << "Enter new account number: ";
                if (!(std::cin >> accountNumber)) {
                    handleInvalidInput();
                    continue;
                }
                std::cout << "Enter initial balance: ";
                if (!(std::cin >> initialBalance)) {
                    handleInvalidInput();
                    continue;
                }
                bank.addAccount(customerID, accountNumber, initialBalance);
                break;
            }
            case 2:
                // similar changes for cases 2, 3, 4
                break;
        }

        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}
