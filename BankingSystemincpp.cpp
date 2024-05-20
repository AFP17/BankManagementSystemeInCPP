#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

struct Account {
    std::string name;
    long long accountNumber;
    double balance;
};

Account accounts[10]; // Simple fixed-size array for accounts
int numAccounts = 0; // Counter for the number of accounts

void createAccount() {
    if (numAccounts >= 10) {
        std::cout << "\n============================\n";
        std::cout << "Bank is full. Cannot create more accounts.\n";
        std::cout << "============================\n";
        return;
    }

    std::cout << "\nEnter your name: ";
    std::cin.ignore();
    getline(std::cin, accounts[numAccounts].name);
    accounts[numAccounts].accountNumber = rand() % 90000 + 10000; // Random 5-digit ID
    std::cout << "Enter initial balance: $";
    std::cin >> accounts[numAccounts].balance;
    std::cout << "\n============================\n";
    std::cout << "Account created successfully!\n";
    std::cout << "Account Number: " << accounts[numAccounts].accountNumber << std::endl;
    std::cout << "============================\n";
    numAccounts++;
}

void deposit() {
    long long accountNumber;
    double amount;
    std::cout << "\nEnter account number: ";
    std::cin >> accountNumber;
    std::cout << "Enter amount to deposit: $";
    std::cin >> amount;

    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            accounts[i].balance += amount;
            std::cout << "\n============================\n";
            std::cout << "Successfully deposited $" << std::fixed << std::setprecision(2) << amount << "\n";
            std::cout << "New Balance: $" << std::fixed << std::setprecision(2) << accounts[i].balance << "\n";
            std::cout << "============================\n";
            return;
        }
    }
    std::cout << "\n============================\n";
    std::cout << "Account not found.\n";
    std::cout << "============================\n";
}

void withdraw() {
    long long accountNumber;
    double amount;
    std::cout << "\nEnter account number: ";
    std::cin >> accountNumber;
    std::cout << "Enter amount to withdraw: $";
    std::cin >> amount;

    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber && accounts[i].balance >= amount) {
            accounts[i].balance -= amount;
            std::cout << "\n============================\n";
            std::cout << "Successfully withdrew $" << std::fixed << std::setprecision(2) << amount << "\n";
            std::cout << "Remaining Balance: $" << std::fixed << std::setprecision(2) << accounts[i].balance << "\n";
            std::cout << "============================\n";
            return;
        }
    }
    std::cout << "\n============================\n";
    std::cout << "Account not found or insufficient funds.\n";
    std::cout << "============================\n";
}

void showAccountDetails() {
    long long accountNumber;
    std::cout << "\nEnter account number: ";
    std::cin >> accountNumber;

    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            std::cout << "\n============================\n";
            std::cout << "Account Details:\n";
            std::cout << "Account Number: " << accountNumber << "\n";
            std::cout << "Name: " << accounts[i].name << "\n";
            std::cout << "Balance: $" << std::fixed << std::setprecision(2) << accounts[i].balance << "\n";
            std::cout << "============================\n";
            return;
        }
    }
    std::cout << "\n============================\n";
    std::cout << "Account not found.\n";
    std::cout << "============================\n";
}

int main() {
    srand(time(0)); // Initialize random number generator
    int choice;

    while (true) {
        std::cout << "\n=================================\n";
        std::cout << "         Banking System Menu\n";
        std::cout << "=================================\n";
        std::cout << "1. Create Account\n";
        std::cout << "2. Deposit Money\n";
        std::cout << "3. Withdraw Money\n";
        std::cout << "4. Show Account Details\n";
        std::cout << "5. Exit\n";
        std::cout << "=================================\n";
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                showAccountDetails();
                break;
            case 5:
                std::cout << "\nExiting program. Thank you for using our services.\n";
                return 0;
            default:
                std::cout << "\nInvalid choice. Please enter a number between 1 and 5.\n";
        }
    }
    return 0;
}
