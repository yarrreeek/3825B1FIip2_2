#include <iostream>
#include <string>
#include <map>

using namespace std;

bool isNumber(const string& s) {
    for (char c : s) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

class Deposit {
private:
    bool isOpen;
    double startAmount;
    int termMonths;
    double interestRate;
    int monthsPassed;

public:
    Deposit() {
        isOpen = false;
        startAmount = 0.0;
        termMonths = 0;
        interestRate = 0.0;
        monthsPassed = 0;
    }

    bool getIsOpen() const {
        return isOpen;
    }

    void openDeposit(double amount, int months, double rate) {
        isOpen = true;
        startAmount = amount;
        termMonths = months;
        interestRate = rate;
        monthsPassed = 0;
    }

    double closeDeposit() {
        if (!isOpen) return 0.0;
        double total = getTotalAmount();
        isOpen = false;
        startAmount = 0.0;
        termMonths = 0;
        interestRate = 0.0;
        monthsPassed = 0;
        return total;
    }

    double addMonthlyInterest() {
        if (!isOpen) return 0.0;
        if (monthsPassed >= termMonths) return 0.0;

        double monthlyRate = interestRate / 12.0 / 100.0;
        double interestAmount = startAmount * monthlyRate;

        monthsPassed++;
        return interestAmount;
    }

    double getTotalAmount() const {
        if (!isOpen) return 0.0;
        double monthlyRate = interestRate / 12.0 / 100.0;
        double totalInterest = startAmount * monthlyRate * monthsPassed;
        return startAmount + totalInterest;
    }

    double getAccruedInterest() const {
        if (!isOpen) return 0.0;
        double monthlyRate = interestRate / 12.0 / 100.0;
        return startAmount * monthlyRate * monthsPassed;
    }

    int getTermMonths() const { return termMonths; }
    int getMonthsPassed() const { return monthsPassed; }
    double getInterestRate() const { return interestRate; }
    double getStartAmount() const { return startAmount; }
};

class ProcessingCenter {
private:
    struct Client {
        string fullName;
        double salaryBalance;
        Deposit deposit;
        string password;
    };

    map<string, Client> clients;

    double getRateByAmountAndTerm(double amount, int termYears) const {
        string range;
        if (amount < 100000) range = "less100";
        else if (amount < 500000) range = "100_500";
        else if (amount <= 1000000) range = "500_1000";
        else range = "over1000";

        map<string, double> ratesFor1Year;
        ratesFor1Year["less100"] = 5.0;
        ratesFor1Year["100_500"] = 6.0;
        ratesFor1Year["500_1000"] = 6.6;
        ratesFor1Year["over1000"] = 7.2;

        return ratesFor1Year[range];
    }

public:
    void addClient(const string& accNum, const string& name, double balance, const string& pass) {
        if (accNum.length() != 4 || !isNumber(accNum)) {
            cout << "Error: account number must be 4 digits.\n";
            return;
        }
        if (pass.length() <= 3) {
            cout << "Error: password too short (need >3 symbols).\n";
            return;
        }
        Client newClient;
        newClient.fullName = name;
        newClient.salaryBalance = balance;
        newClient.password = pass;
        clients[accNum] = newClient;
    }

    void* authorize(const string& accNum, const string& pass) {
        auto it = clients.find(accNum);
        if (it != clients.end() && it->second.password == pass) {
            return &(it->second);
        }
        return nullptr;
    }

    void showAvailableDeposits(void* clientPtr) const {
        if (!clientPtr) return;
        Client* client = (Client*)clientPtr;
        double balance = client->salaryBalance;
        cout << "\nAvailable deposits based on your balance (" << balance << " RUB):\n";

        int termsMonths[] = { 3, 6, 12, 24, 36 };
        int termsYears[] = { 1, 1, 1, 2, 3 };

        for (int i = 0; i < 5; i++) {
            int months = termsMonths[i];
            int years = termsYears[i];
            double rate = getRateByAmountAndTerm(balance, years);
            cout << "  - " << months << " months (" << years << " year(s)) : " << rate << "% per annum\n";
        }
        cout << endl;
    }

    bool hasOpenDeposit(void* clientPtr) const {
        if (!clientPtr) return false;
        Client* client = (Client*)clientPtr;
        return client->deposit.getIsOpen();
    }

    bool openDeposit(void* clientPtr, double amount, int termMonths) {
        if (!clientPtr) return false;
        Client* client = (Client*)clientPtr;
        if (client->deposit.getIsOpen()) {
            cout << "Error: you already have an open deposit!\n";
            return false;
        }
        if (amount <= 0) {
            cout << "Error: deposit amount must be positive.\n";
            return false;
        }
        if (amount > client->salaryBalance) {
            cout << "Error: insufficient funds on salary account.\n";
            return false;
        }

        int years = termMonths / 12;
        if (termMonths == 3 || termMonths == 6) years = 1;
        if (termMonths == 24) years = 2;
        if (termMonths == 36) years = 3;
        double rate = getRateByAmountAndTerm(amount, years);

        client->salaryBalance -= amount;
        client->deposit.openDeposit(amount, termMonths, rate);
        cout << "Deposit opened successfully! Amount: " << amount << " RUB, term: "
            << termMonths << " months, rate: " << rate << "%\n";
        return true;
    }

    void showDepositState(void* clientPtr) const {
        if (!clientPtr) return;
        Client* client = (Client*)clientPtr;
        const Deposit& d = client->deposit;
        if (!d.getIsOpen()) {
            cout << "No active deposit.\n";
            return;
        }
        cout << "\nDeposit state\n";
        cout << "Initial amount: " << d.getStartAmount() << " RUB\n";
        cout << "Term: " << d.getTermMonths() << " months\n";
        cout << "Annual rate: " << d.getInterestRate() << "%\n";
        cout << "Months passed: " << d.getMonthsPassed() << " / " << d.getTermMonths() << "\n";
        cout << "Accrued interest: " << d.getAccruedInterest() << " RUB\n";
        cout << "Total amount (with interest): " << d.getTotalAmount() << " RUB\n";
    }

    bool withdrawInterest(void* clientPtr) {
        if (!clientPtr) return false;
        Client* client = (Client*)clientPtr;
        Deposit& d = client->deposit;
        if (!d.getIsOpen()) {
            cout << "Error: no open deposit.\n";
            return false;
        }
        double interest = d.getAccruedInterest();
        if (interest <= 0) {
            cout << "No interest accrued yet.\n";
            return false;
        }
        client->salaryBalance += interest;

        double startAmount = d.getStartAmount();
        int term = d.getTermMonths();
        double rate = d.getInterestRate();
        d.openDeposit(startAmount, term, rate);

        cout << "Interest withdrawn: " << interest << " RUB transferred to salary account.\n";
        return true;
    }

    bool closeDeposit(void* clientPtr) {
        if (!clientPtr) return false;
        Client* client = (Client*)clientPtr;
        Deposit& d = client->deposit;
        if (!d.getIsOpen()) {
            cout << "Error: no open deposit to close.\n";
            return false;
        }
        if (d.getMonthsPassed() < d.getTermMonths()) {
            cout << "Error: deposit can only be closed after the term ends.\n";
            return false;
        }
        double total = d.closeDeposit();
        client->salaryBalance += total;
        cout << "Deposit closed. " << total << " RUB transferred to salary account.\n";
        return true;
    }

    string getClientName(void* clientPtr) const {
        if (!clientPtr) return "";
        Client* client = (Client*)clientPtr;
        return client->fullName;
    }
};

int main() {
    ProcessingCenter center;

    center.addClient("1234", "Ivanova Anna", 250000.0, "pass123");
    center.addClient("5678", "Petrov Oleg", 750000.0, "qwerty");
    center.addClient("9012", "Sidorova Maria", 1200000.0, "maria007");

    string accNum, pass;
    cout << "BANK DEPOSIT SYSTEM\n";
    cout << "Enter account number (4 digits): ";
    cin >> accNum;
    cout << "Enter password: ";
    cin >> pass;

    void* currentClient = center.authorize(accNum, pass);
    if (!currentClient) {
        cout << "Authorization failed. Wrong account or password.\n";
        return 1;
    }

    int choice;
    do {
        cout << "\n1 - Show available deposits\n";
        cout << "2 - Check if deposit is open\n";
        cout << "3 - Open deposit\n";
        cout << "4 - Show deposit state\n";
        cout << "5 - Withdraw interest\n";
        cout << "6 - Close deposit\n";
        cout << "0 - Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            center.showAvailableDeposits(currentClient);
            break;
        case 2:
            if (center.hasOpenDeposit(currentClient))
                cout << "You have an active deposit.\n";
            else
                cout << "No active deposit.\n";
            break;
        case 3: {
            if (center.hasOpenDeposit(currentClient)) {
                cout << "You already have a deposit. Close it first.\n";
                break;
            }
            double amount;
            int term;
            cout << "Enter deposit amount (RUB): ";
            cin >> amount;
            cout << "Enter term in months (3,6,12,24,36): ";
            cin >> term;
            if (term != 3 && term != 6 && term != 12 && term != 24 && term != 36) {
                cout << "Invalid term.\n";
                break;
            }
            center.openDeposit(currentClient, amount, term);
            break;
        }
        case 4:
            center.showDepositState(currentClient);
            break;
        case 5:
            center.withdrawInterest(currentClient);
            break;
        case 6:
            center.closeDeposit(currentClient);
            break;
        case 0:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}