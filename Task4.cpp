#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Transaction {
public:
    string type;
    double amount;

    Transaction(string t, double a) : type(t), amount(a) {}

    void display() const {
        cout << type << ": " << amount << endl;
    }
};

class Account {
private:
    double  balance;
    vector<Transaction> transactions;

public:
    int accountNumber;
    string ownerName

    Account(int accNum, string owner) : accountNumber(accNum), ownerName(owner), balance(0) {}

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        cout << "Deposited " << amount << ". New Balance: " << balance << endl;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!\n";
            return false;
        }
        balance -= amount;
        transactions.emplace_back("Withdrawal", amount);
        cout << "Withdrawn " << amount << ". New Balance: " << balance << endl;
        return true;
    }

    void transfer(Account& recipient, double amount) {
        if (withdraw(amount)) {
            recipient.deposit(amount);
            transactions.emplace_back("Transfer to " + recipient.ownerName, amount);
            cout << "Transferred " << amount << " to " << recipient.ownerName << endl;
        }
    }

    void displayTransactions() const {
        cout << "Transaction History for " << ownerName << ":\n";
        for (const auto& txn : transactions)
            txn.display();
    }

    void displayBalance() const {
        cout << ownerName << "'s Account Balance: " << balance << endl;
    }
};

class Customer {
public:
    string name;
    Account account;

    Customer(string n, int accNum) : name(n), account(accNum, n) {}

    void performDeposit(double amount) {
        account.deposit(amount);
    }

    void performWithdrawal(double amount) {
        account.withdraw(amount);
    }

    void performTransfer(Customer& recipient, double amount) {
        account.transfer(recipient.account, amount);
    }

    void showBalance() const {
        account.displayBalance();
    }

    void showTransactions() const {
        account.displayTransactions();
    }
};

int main() {
    Customer customer1("Alice", 101);
    Customer customer2("Bob", 102);

    customer1.performDeposit(1000);
    customer1.performWithdrawal(300);
    customer1.performTransfer(customer2, 200);

    customer1.showBalance();
    customer1.showTransactions();
    
    customer2.showBalance();
    customer2.showTransactions();

    return 0;
}