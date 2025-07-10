#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <limits>

class Transaction {
private:
    std::string transactionId;
    std::string accountNumber;
    std::string type;
    double amount;
    std::string timestamp;
    std::string description;

public:
    Transaction(const std::string& accNum, const std::string& t, double amt, const std::string& desc = "")
        : accountNumber(accNum), type(t), amount(amt), description(desc) {
        // Generate a transaction ID
        transactionId = "TXN" + std::to_string(std::rand() % 1000000);

        // Format current time
        time_t now = time(0);
        char buf[100];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
        timestamp = buf;
    }

    void display() const {
        std::cout << "Transaction ID: " << transactionId << "\n"
                  << "Account: " << accountNumber << "\n"
                  << "Type: " << type << "\n"
                  << "Amount: $" << std::fixed << std::setprecision(2) << amount << "\n"
                  << "Time: " << timestamp << "\n";
        if (!description.empty()) {
            std::cout << "Description: " << description << "\n";
        }
        std::cout << "------------------------\n";
    }

    // Getters
    std::string getTransactionId() const { return transactionId; }
    std::string getAccountNumber() const { return accountNumber; }
    std::string getType() const { return type; }
    double getAmount() const { return amount; }
    std::string getTimestamp() const { return timestamp; }
};

class Account {
private:
    std::string accountNumber;
    std::string customerId;
    double balance;
    std::string type;
    std::vector<Transaction> transactions;

public:
    Account(const std::string& accNum, const std::string& custId, const std::string& t, double initialBalance = 0.0)
        : accountNumber(accNum), customerId(custId), type(t), balance(initialBalance) {}

    bool deposit(double amount, const std::string& description = "") {
        if (amount <= 0) {
            std::cout << "Deposit amount must be positive.\n";
            return false;
        }
        balance += amount;
        transactions.emplace_back(accountNumber, "Deposit", amount, description);
        std::cout << "Deposit successful. New balance: $" << balance << "\n";
        return true;
    }

    bool withdraw(double amount, const std::string& description = "") {
        if (amount <= 0) {
            std::cout << "Withdrawal amount must be positive.\n";
            return false;
        }
        if (balance < amount) {
            std::cout << "Insufficient funds.\n";
            return false;
        }
        balance -= amount;
        transactions.emplace_back(accountNumber, "Withdrawal", amount, description);
        std::cout << "Withdrawal successful. New balance: $" << balance << "\n";
        return true;
    }

    bool transfer(Account& toAccount, double amount, const std::string& description = "") {
        if (amount <= 0) {
            std::cout << "Transfer amount must be positive.\n";
            return false;
        }
        if (balance < amount) {
            std::cout << "Insufficient funds for transfer.\n";
            return false;
        }

        balance -= amount;
        toAccount.balance += amount;

        transactions.emplace_back(accountNumber, "Transfer (Out)", amount, 
                                 "To: " + toAccount.getAccountNumber() + " - " + description);
        toAccount.transactions.emplace_back(toAccount.getAccountNumber(), "Transfer (In)", amount, 
                                          "From: " + accountNumber + " - " + description);

        std::cout << "Transfer successful. New balance: $" << balance << "\n";
        return true;
    }

    void displayTransactions(int limit = 5) const {
        if (transactions.empty()) {
            std::cout << "\nNo transactions found for account " << accountNumber << ".\n";
            return;
        }
        std::cout << "\nLast " << limit << " transactions for account " << accountNumber << ":\n";
        int count = 0;
        for (auto it = transactions.rbegin(); it != transactions.rend() && count < limit; ++it, ++count) {
            it->display();
        }
    }

    void displayInfo() const {
        std::cout << "\nAccount Information:\n"
                  << "Account Number: " << accountNumber << "\n"
                  << "Customer ID: " << customerId << "\n"
                  << "Type: " << type << "\n"
                  << "Balance: $" << std::fixed << std::setprecision(2) << balance << "\n";
    }

    std::string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    std::string getCustomerId() const { return customerId; }
    std::string getType() const { return type; }
};

class Customer {
private:
    std::string customerId;
    std::string name;
    std::string address;
    std::string phone;
    std::vector<Account> accounts;

public:
    Customer(const std::string& id, const std::string& n, const std::string& addr = "", const std::string& ph = "")
        : customerId(id), name(n), address(addr), phone(ph) {}

    void addAccount(const Account& account) {
        accounts.push_back(account);
    }

    void displayAccounts() const {
        std::cout << "\nAccounts for customer " << name << " (ID: " << customerId << "):\n";
        for (const auto& account : accounts) {
            account.displayInfo();
        }
    }

    Account* findAccount(const std::string& accountNumber) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }

    std::string getCustomerId() const { return customerId; }
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }
    std::string getPhone() const { return phone; }
};

class BankingSystem {
private:
    std::vector<Customer> customers;
    int nextCustomerId = 1000;
    int nextAccountId = 10000;

public:
    Customer* createCustomer(const std::string& name, const std::string& address = "", const std::string& phone = "") {
        std::string id = "CUST" + std::to_string(nextCustomerId++);
        customers.emplace_back(id, name, address, phone);
        return &customers.back();
    }

    Account* createAccount(Customer& customer, const std::string& type, double initialBalance = 0.0) {
        std::string accNum = "ACC" + std::to_string(nextAccountId++);
        customer.addAccount(Account(accNum, customer.getCustomerId(), type, initialBalance));
        return customer.findAccount(accNum);
    }

    Customer* findCustomer(const std::string& customerId) {
        for (auto& customer : customers) {
            if (customer.getCustomerId() == customerId) {
                return &customer;
            }
        }
        return nullptr;
    }

    void displayAllCustomers() const {
        std::cout << "\nAll Customers:\n";
        for (const auto& customer : customers) {
            std::cout << "ID: " << customer.getCustomerId()<< ", Name: " << customer.getName()<< ", Phone: " << customer.getPhone() << "\n";
        }
    }
};

double getAmountInput(const std::string& prompt) {
    double amount;
    while (true) {
        std::cout << prompt;
        if (std::cin >> amount && amount > 0) {
            return amount;
        }
        std::cout << "Invalid amount. Please enter a positive number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    BankingSystem bank;
    std::srand(static_cast<unsigned>(std::time(0))); // Seed for random transaction IDs

    // Sample customers and accounts
    Customer* cust1 = bank.createCustomer("John Doe", "123 Main St", "555-1234");
    Account* acc1 = bank.createAccount(*cust1, "Savings", 1000.0);
    Account* acc2 = bank.createAccount(*cust1, "Checking", 500.0);

    Customer* cust2 = bank.createCustomer("Jane Smith", "456 Oak Ave", "555-5678");
    Account* acc3 = bank.createAccount(*cust2, "Savings", 2000.0);

    std::cout << "Banking System Demo\n";
    bank.displayAllCustomers();

    std::cout << "\nCustomer 1 operations:\n";
    cust1->displayAccounts();
    acc1->deposit(500.0, "Paycheck deposit");
    acc1->withdraw(200.0, "ATM withdrawal");
    acc1->transfer(*acc2, 300.0, "Transfer to checking");
    acc1->displayTransactions();
    acc2->displayTransactions();

    std::cout << "\nCustomer 2 operations:\n";
    acc3->deposit(1000.0, "Bonus deposit");
    acc3->displayInfo();
    acc3->displayTransactions();

    std::cout << "\nTransfer between customers:\n";
    acc1->transfer(*acc3, 150.0, "Payment to Jane");
    acc1->displayTransactions();
    acc3->displayTransactions();

    return 0;
}
