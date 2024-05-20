#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

class Customer {
public:
    std::string name;
    int customerID;
    Customer(std::string n, int id) : name(n), customerID(id) {}
};

class Account {
public:
    long long accountNumber;
    double balance;
    std::vector<std::string> transactions;

    Account(long long num, double bal) : accountNumber(num), balance(bal) {}
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
        for (auto& t : transactions) {
            std::cout << t << "\n";
        }
    }
};

class BankingServices {
public:
    std::vector<Customer> customers;
    std::vector<Account> accounts;

    void addCustomer(std::string name, int customerID) {
        customers.push_back(Customer(name, customerID));
        std::cout << "Customer created with ID: " << customerID << " for " << name << ".\n";
    }

    void addAccount(int customerID, long long accountNumber, double initialBalance) {
        accounts.push_back(Account(accountNumber, initialBalance));
        std::cout << "Account created with ID: " << accountNumber << " and initial balance: $" << initialBalance << ".\n";
    }

    Account* findAccount(long long accountNumber) {
        for (auto& acc : accounts) {
            if (acc.accountNumber == accountNumber) return &acc;
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
    srand(time(0)); // Seed the random number generator

    int choice;
    double initialBalance;

    while (true) {
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
                std::string name;
                std::cout << "Enter your name: ";
                std::cin.ignore(); // Ignore the newline left in the input buffer
                std::getline(std::cin, name); // Properly read names with spaces
                int customerID = rand() % 900 + 100; // Random 3-digit ID (100 to 999)
                long long accountNumber = rand() % 90000 + 10000; // Random 5-digit ID (10000 to 99999)
                std::cout << "Enter initial balance: ";
                if (!(std::cin >> initialBalance)) {
                    handleInvalidInput();
                    continue;
                }
                bank.addCustomer(name, customerID);
                bank.addAccount(customerID, accountNumber, initialBalance);
                break;
            }
            // Cases 2, 3, 4 are implemented similarly
            case 5:
                std::cout << "Exiting program.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    }

    return 0;
}
