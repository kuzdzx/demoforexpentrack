#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#define MAX_EXPENSES 100  

struct Expense {
    string category;
    double amount;
};

void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

void showBalance(double balance) {
    cout << "Your current balance is: $" << fixed << setprecision(2) << balance << "\n";
}

double deposit() {
    double amount;
    cout << "Enter the amount to deposit: ";
    while (!(cin >> amount) || amount <= 0) {
        cout << "Invalid amount. Try again: ";
        clearInput();
    }
    return amount;
}

double withdraw(double& balance) {
    double amount;
    cout << "Enter the amount to withdraw: ";
    while (!(cin >> amount) || amount <= 0) {
        cout << "Invalid amount. Try again: ";
        clearInput();
    }
    if (amount > balance) {
        cout << "Insufficient balance.\n";
        return 0;
    } else {
        balance -= amount;
        return amount;
    }
}

string selectCategory() {
    cout << "\nSelect an expense category:\n";
    cout << "1. Food\n";
    cout << "2. Tuition Fee\n";
    cout << "3. Clothes\n";
    cout << "4. Internet Fee\n";
    cout << "5. Savings\n";
    cout << "6. Transportation\n";
    cout << "7. Others\n";
    cout << "Enter your choice (1-7): ";

    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 7) {
        cout << "Invalid choice. Please select a number between 1 and 7: ";
        clearInput();
    }

    switch (choice) {
        case 1: return "Food";
        case 2: return "Tuition Fee";
        case 3: return "Clothes";
        case 4: return "Internet Fee";
        case 5: return "Savings";
        case 6: return "Transportation";
        case 7: {
            cin.ignore();
            string customCategory;
            cout << "Enter a custom category: ";
            getline(cin, customCategory);
            return customCategory;
        }
        default:
            return "Others";
    }
}

void addExpense(Expense expenses[], double& balance, int& expenseCount) {
    if (expenseCount >= MAX_EXPENSES) {
        cout << "Expense list is full! Cannot add more expenses.\n";
        return;
    }

    string category = selectCategory();
    double amount;

    cout << "Enter expense amount: ";
    while (!(cin >> amount) || amount <= 0) {
        cout << "Invalid amount. Try again: ";
        clearInput();
    }

    if (amount <= balance) {
        expenses[expenseCount].category = category;
        expenses[expenseCount].amount = amount;
        expenseCount++;
        balance -= amount;
        cout << "Expense added successfully!\n";
    } else {
        cout << "Insufficient balance to add this expense.\n";
    }
}

void viewExpenses(Expense expenses[], int expenseCount) {
    if (expenseCount == 0) {
        cout << "No expenses recorded yet.\n";
        return;
    }

    cout << "\nRecorded Expenses:\n";
    for (int i = 0; i < expenseCount; i++) {
        cout << "Category: " << expenses[i].category 
             << ", Amount: $" << fixed << setprecision(2) << expenses[i].amount << "\n";
    }
}

int main() {
    double balance = 0.0;
    Expense expenses[MAX_EXPENSES];
    int expenseCount = 0;  
    int choice;

    cout << "Welcome to the Expense Tracker!\n";
    cout << "Do you want to deposit an initial amount? (y/n): ";
    char initialDeposit;
    cin >> initialDeposit;

    if (initialDeposit == 'y' || initialDeposit == 'Y') {
        balance += deposit();
    } else {
        cout << "Exiting the program. Goodbye!\n";
        return 0;
    }

    do {
        cout << "\nMain Menu:\n";
        cout << "1. Show Balance\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Add an Expense\n";
        cout << "5. View All Expenses\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice)) {
            cout << "Invalid choice. Please enter a number: ";
            clearInput();
        }

        switch (choice) {
            case 1:
                showBalance(balance);
                break;
            case 2:
                balance += deposit();
                break;
            case 3:
                withdraw(balance);
                break;
            case 4:
                addExpense(expenses, balance, expenseCount);
                break;
            case 5:
                viewExpenses(expenses, expenseCount);
                break;
            case 6:
                cout << "Thank you for using the Expense Tracker. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (true);

    return 0;
}
    