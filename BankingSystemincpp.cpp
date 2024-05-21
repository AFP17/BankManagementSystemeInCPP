#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include <vector>

struct Account {
    std::string name;
    long long accountNumber;
    double balance;
    std::vector<std::string> transactions;
};

Account accounts[10]; // Fixed-size array for accounts
int numAccounts = 0; // Counter for the number of accounts
int currentUserIndex = -1; // Index for the current logged-in user

std::string formatCurrency(double amount) {
    char buffer[50];
    sprintf(buffer, "%.2f$", amount);
    return std::string(buffer);
}

void createAccount() {
    if (numAccounts >= 10) {
        std::cout << "\n============================\n";
        std::cout << "Bank is full. Cannot create more accounts.\n";
        std::cout << "============================\n";
        return;
    }

    std::cout << "\n--- Create Account ---\n";
    std::cout << "Enter your name: ";
    std::cin.ignore();
    getline(std::cin, accounts[numAccounts].name);
    accounts[numAccounts].accountNumber = rand() % 90000 + 10000; // Random 5-digit ID
    std::cout << "Enter initial balance: ";
    std::cin >> accounts[numAccounts].balance;
    std::cout << "\n============================\n";
    std::cout << "Account created successfully!\n";
    std::cout << "Account Number: " << accounts[numAccounts].accountNumber << "\n";
    std::cout << "============================\n";
    numAccounts++;
}

void login() {
    long long accountNumber;
    std::cout << "\n--- Login ---\n";
    std::cout << "Enter account number to login: ";
    std::cin >> accountNumber;

    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            currentUserIndex = i;
            std::cout << "\n============================\n";
            std::cout << "Login successful! Welcome " << accounts[i].name << "!\n";
            std::cout << "============================\n";
            return;
        }
    }
    std::cout << "\n============================\n";
    std::cout << "Account not found.\n";
    std::cout << "============================\n";
}

void deposit() {
    double amount;
    std::string description;
    std::cout << "\n--- Deposit Money ---\n";
    std::cout << "Enter amount to deposit: ";
    std::cin >> amount;
    std::cin.ignore(); // Ignore newline character left in buffer
    std::cout << "Enter description for this transaction: ";
    getline(std::cin, description);

    accounts[currentUserIndex].balance += amount;
    std::string transaction = "Deposited: " + formatCurrency(amount) + " - " + description;
    accounts[currentUserIndex].transactions.push_back(transaction);
    std::cout << "\n============================\n";
    std::cout << "Successfully deposited " << formatCurrency(amount) << "\n";
    std::cout << "New Balance: " << formatCurrency(accounts[currentUserIndex].balance) << "\n";
    std::cout << "============================\n";
}

void withdraw() {
    double amount;
    std::string description;
    std::cout << "\n--- Withdraw Money ---\n";
    std::cout << "Enter amount to withdraw: ";
    std::cin >> amount;
    std::cin.ignore(); // Ignore newline character left in buffer
    std::cout << "Enter description for this transaction: ";
    getline(std::cin, description);

    if (accounts[currentUserIndex].balance >= amount) {
        accounts[currentUserIndex].balance -= amount;
        std::string transaction = "Withdrew: " + formatCurrency(amount) + " - " + description;
        accounts[currentUserIndex].transactions.push_back(transaction);
        std::cout << "\n============================\n";
        std::cout << "Successfully withdrew " << formatCurrency(amount) << "\n";
        std::cout << "Remaining Balance: " << formatCurrency(accounts[currentUserIndex].balance) << "\n";
        std::cout << "============================\n";
    } else {
        std::cout << "\n============================\n";
        std::cout << "Insufficient funds.\n";
        std::cout << "============================\n";
    }
}

void showAccountDetails() {
    std::cout << "\n--- Account Details ---\n";
    std::cout << "Account Number: " << accounts[currentUserIndex].accountNumber << "\n";
    std::cout << "Name: " << accounts[currentUserIndex].name << "\n";
    std::cout << "Balance: " << formatCurrency(accounts[currentUserIndex].balance) << "\n";
    std::cout << "Transaction History:\n";
    for (size_t i = 0; i < accounts[currentUserIndex].transactions.size(); i++) {
        std::cout << "  - " << accounts[currentUserIndex].transactions[i] << "\n";
    }
    std::cout << "============================\n";
}

void showAccountDetailsMenu() {
    int choice;
    while (true) {
        showAccountDetails();
        std::cout << "\n1. Return to previous menu\n";
        std::cout << "Enter your choice (1): ";
        std::cin >> choice;

        if (choice == 1) {
            return; // Return to the user menu
        } else {
            std::cout << "\nInvalid choice. Please enter 1 to return.\n";
        }
    }
}

void userMenu() {
    int choice;
    while (true) {
        std::cout << "\n=================================\n";
        std::cout << "       Welcome, " << accounts[currentUserIndex].name << "\n";
        std::cout << "       Balance: " << formatCurrency(accounts[currentUserIndex].balance) << "\n";
        std::cout << "=================================\n";
        std::cout << "1. Deposit Money\n";
        std::cout << "2. Withdraw Money\n";
        std::cout << "3. Show Account Details\n";
        std::cout << "4. Log Off\n";
        std::cout << "5. Exit\n";
        std::cout << "=================================\n";
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                deposit();
                break;
            case 2:
                withdraw();
                break;
            case 3:
                showAccountDetailsMenu();
                break;
            case 4:
                currentUserIndex = -1;
                return; // Log off and return to the main menu
            case 5:
                std::cout << "\nExiting program. Thank you for using our services.\n";
                exit(0);
            default:
                std::cout << "\nInvalid choice. Please enter a number between 1 and 5.\n";
        }
    }
}

int main() {
    srand(time(0)); // Initialize random number generator
    int choice;

    while (true) {
        std::cout << "\n=================================\n";
        std::cout << "         Banking System Menu\n";
        std::cout << "=================================\n";
        std::cout << "1. Create Account\n";
        std::cout << "2. Login\n";
        std::cout << "3. Exit\n";
        std::cout << "=================================\n";
        std::cout << "Enter your choice (1-3): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                login();
                if (currentUserIndex != -1) {
                    userMenu();
                }
                break;
            case 3:
                std::cout << "\nExiting program. Thank you for using our services.\n";
                return 0;
            default:
                std::cout << "\nInvalid choice. Please enter a number between 1 and 3.\n";
        }
    }

    return 0;
}
