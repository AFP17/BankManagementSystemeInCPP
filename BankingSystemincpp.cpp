#include <iostream>
#include <vector>
#include <string>

// Customer class
class Customer {
public:
    std::string name;
    int customerID;

    Customer(std::string n, int id) : name(n), customerID(id) {}
};

// Account class
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
        for (size_t i = 0; i < transactions.size(); i++) {
            std::cout << transactions[i] << "\n";
        }
    }
};

// BankingServices class
class BankingServices {
public:
    std::vector<Customer> customers;
    std::vector<Account> accounts;

    void addCustomer(std::string name, int customerID) {
        Customer newCustomer(name, customerID);
        customers.push_back(newCustomer);
    }

    void addAccount(int customerID, int accountNumber, double initialBalance) {
        Account newAccount(accountNumber, initialBalance);
        accounts.push_back(newAccount);
        std::cout << "Account created successfully for customer ID " << customerID << ".\n";
    }

    Account* findAccount(int accountNumber) {
        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i].accountNumber == accountNumber) {
                return &accounts[i];
            }
        }
        return nullptr;
    }
};

int main() {
    BankingServices bank;
    bank.addCustomer("John Doe", 1);  // Example initial customer

    int choice, accountNumber, customerID;
    double initialBalance, amount;  // Declare 'amount' here to use in deposit and withdrawal

    while (true) {
        std::cout << "\nBanking System Menu:\n";
        std::cout << "1. Create Account\n";
        std::cout << "2. Deposit Money\n";
        std::cout << "3. Withdraw Money\n";
        std::cout << "4. Show Account Details\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter customer ID: ";
                std::cin >> customerID;
                std::cout << "Enter new account number: ";
                std::cin >> accountNumber;
                std::cout << "Enter initial balance: ";
                std::cin >> initialBalance;
                bank.addAccount(customerID, accountNumber, initialBalance);
                break;
            case 2:
                std::cout << "Enter account number: ";
                std::cin >> accountNumber;
                std::cout << "Enter amount to deposit: ";
                std::cin >> amount;
                if (Account* acc = bank.findAccount(accountNumber)) {
                    acc->deposit(amount);
                } else {
                    std::cout << "Account not found.\n";
                }
                break;
            case 3:
                std::cout << "Enter account number: ";
                std::cin >> accountNumber;
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amount;
                if (Account* acc = bank.findAccount(accountNumber)) {
                    acc->withdraw(amount);
                } else {
                    std::cout << "Account not found.\n";
                }
                break;
            case 4:
                std::cout << "Enter account number: ";
                std::cin >> accountNumber;
                if (Account* acc = bank.findAccount(accountNumber)) {
                    acc->printAccountDetails();
                } else {
                    std::cout << "Account not found.\n";
                }
                break;
            case 5:
                std::cout << "Exiting program.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
