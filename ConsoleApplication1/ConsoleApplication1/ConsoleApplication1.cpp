#include <iostream>

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    BankAccount(int accountNumber, double initialBalance) : accountNumber(accountNumber), balance(initialBalance), interestRate(0.0) {}

    void deposit(double amount) {
        if (amount <= 0) {
            std::cout << "Сумма должна быть больше 0." << std::endl;
            return;
        }
        this->balance += amount;
        std::cout << "Средства успешно внесены. Текущий баланс: " << this->balance << std::endl;
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > this->balance) {
            std::cout << "Невозможно выполнить операцию снятия." << std::endl;
            return false;
        }
        this->balance -= amount;
        std::cout << "Снятие прошло успешно. Текущий баланс: " << this->balance << std::endl;
        return true;
    }

    double getBalance() const {
        return this->balance;
    }

    double getInterest() const {
        return this->balance * this->interestRate * (1.0 / 12.0);
    }

    void setInterestRate(double newInterestRate) {
        if (newInterestRate < 0) {
            std::cout << "Процентная ставка не может быть отрицательной." << std::endl;
            return;
        }
        this->interestRate = newInterestRate;
        std::cout << "Процентная ставка успешно установлена." << std::endl;
    }

    int getAccountNumber() const {
        return this->accountNumber;
    }

    friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};

bool transfer(BankAccount& from, BankAccount& to, double amount) {
    if (from.withdraw(amount)) {
        to.deposit(amount);
        return true;
    }
    else {
        return false;
    }
}

void showMenu() {
    std::cout << "\n*** Меню управления счетом ***\n";
    std::cout << "1. Внести средства\n";
    std::cout << "2. Снять средства\n";
    std::cout << "3. Показать текущий баланс\n";
    std::cout << "4. Рассчитать и показать проценты\n";
    std::cout << "5. Установить процентную ставку\n";
    std::cout << "6. Показать номер счета\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите опцию: ";
}

int main() {
    setlocale(LC_ALL, "Rus");
    BankAccount account(12345, 1000.0);
    int choice;
    double amount;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Введите сумму для внесения: ";
            std::cin >> amount;
            account.deposit(amount);
            break;
        case 2:
            std::cout << "Введите сумму для снятия: ";
            std::cin >> amount;
            account.withdraw(amount);
            break;
        case 3:
            std::cout << "Текущий баланс: " << account.getBalance() << std::endl;
            break;
        case 4:
            std::cout << "Рассчитанные проценты: " << account.getInterest() << std::endl;
            break;
        case 5:
            std::cout << "Введите новую процентную ставку: ";
            std::cin >> amount;
            account.setInterestRate(amount);
            break;
        case 6:
            std::cout << "Номер счета: " << account.getAccountNumber() << std::endl;
            break;
        case 0:
            std::cout << "Выход из программы..." << std::endl;
            break;
        default:
            std::cout << "Некорректный ввод. Пожалуйста, попробуйте еще раз." << std::endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
