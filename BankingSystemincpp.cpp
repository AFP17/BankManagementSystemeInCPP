#include <iostream>
#include <vector>
#include <string>

// Customer class
class Customer {
public:
    std::string name;
    int customerID;
    Customer(std::string name, int customerID) : name(name), customerID(customerID) {}
};

// Account class
class Account {
public:
    int accountNumber;
    double balance;
    std::vector<std::string> transactions;

    Account(int accountNumber, double balance) : accountNumber(accountNumber), balance(balance) {}

    void deposit(double amount) {
        balance += amount;
        transactions.push_back("Deposited: " + std::to_string(amount));
    }

    void withdraw(double amount) {
        if (amount > balance) {
            std::cout << "Insufficient funds\n";
            return;
        }
        balance -= amount;
        transactions.push_back("Withdrew: " + std::to_string(amount));
    }
};

// Transaction class
class Transaction {
public:
    int accountNumber;
    std::string type;
    double amount;
    std::string date;

    Transaction(int accNo, std::string type, double amount, std::string date)
        : accountNumber(accNo), type(type), amount(amount), date(date) {}
};

// BankingServices class
class BankingServices {
    std::vector<Customer> customers;
    std::vector<Account> accounts;

public:
    void addCustomer(std::string name, int customerID) {
        customers.push_back(Customer(name, customerID));
    }

    void addAccount(int customerID, int accountNumber, double initialBalance) {
        accounts.push_back(Account(accountNumber, initialBalance));
    }

    void showAccountDetails(int accountNumber) {
        for (const auto& acc : accounts) {
            if (acc.accountNumber == accountNumber) {
                std::cout << "Account Number: " << acc.accountNumber << "\nBalance: " << acc.balance << "\n";
                for (const auto& tran : acc.transactions) {
                    std::cout << tran << "\n";
                }
            }
        }
    }

    void transfer(int fromAcc, int toAcc, double amount) {
        Account *fromAccount = nullptr, *toAccount = nullptr;
        for (auto& acc : accounts) {
            if (acc.accountNumber == fromAcc)
                fromAccount = &acc;
            else if (acc.accountNumber == toAcc)
                toAccount = &acc;
        }

        if (fromAccount && toAccount && fromAccount->balance >= amount) {
            fromAccount->withdraw(amount);
            toAccount->deposit(amount);
            std::cout << "Transfer successful!\n";
        } else {
            std::cout << "Transfer failed!\n";
        }
    }
};

int main() {
    BankingServices bank;
    bank.addCustomer("John Doe", 1);
    bank.addAccount(1, 101, 1000.0);
    bank.deposit(101, 200.0);
    bank.withdraw(101, 150.0);
    bank.showAccountDetails(101);
    return 0;
}
