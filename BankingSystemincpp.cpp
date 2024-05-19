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
    bank.addCustomer("John Doe", 1);
    bank.addAccount(1, 101, 1000.0);

    int choice, accountNumber;
    double amount;

    while (true) {
        std::cout << "\nBanking System Menu:\n";
        std::cout << "1. Deposit Money\n";
        std::cout << "2. Withdraw Money\n";
        std::cout << "3. Show Account Details\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
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
            case 2:
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
            case 3:
                std::cout << "Enter account number: ";
                std::cin >> accountNumber;
                if (Account* acc = bank.findAccount(accountNumber)) {
                    acc->printAccountDetails();
                } else {
                    std::cout << "Account not found.\n";
                }
                break;
            case 4:
                std::cout << "Exiting program.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
