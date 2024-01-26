#include <iostream>
#include <cmath>

using namespace std;

float a, c;
int choice;
int p;

int factorial(int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}

int main() {
    setlocale(LC_ALL, "Rus");
    while (p != 2) {
        cout << "Выберите операцию:\n";
        cout << "1. Сложение\n";
        cout << "2. Вычитание\n";
        cout << "3. Умножение\n";
        cout << "4. Деление\n";
        cout << "5. Возведение в степень\n";
        cout << "6. 1 процент от числа\n";
        cout << "7. Факториал\n";
        cout << "8. Квадратный корень\n";
        cout << "9. Выйти\n";
        cin >> choice;
        switch (choice) {
        case 1: {
            cout << "Введите первое число ";
            cin >> a;
            cout << "Введите второе число ";
            float b;
            cin >> b;
            c = a + b;
            break;
        }
        case 2: {
            cout << "Введите первое число ";
            cin >> a;
            cout << "Введите второе число ";
            float b;
            cin >> b;
            c = a - b;
            break;
        }
        case 3: {
            cout << "Введите первое число ";
            cin >> a;
            cout << "Введите второе число ";
            float b;
            cin >> b;
            c = a * b;
            break;
        }
        case 4: {
            cout << "Введите первое число ";
            cin >> a;
            cout << "Введите второе число ";
            float b;
            cin >> b;
            if (b != 0) {
                c = a / b;
            }
            else {
                cout << "Деление на ноль невозможно." << endl;
                continue;
            }
            break;
        }
        case 5: {
            cout << "Введите число ";
            cin >> a;
            cout << "Введите степень ";
            float b;
            cin >> b;
            c = pow(a, b);
            break;
        }
        case 6: {
            cout << "Введите число ";
            cin >> a;
            c = a * 0.01;
            break;
        }
        case 7: {
            cout << "Введите число ";
            cin >> a;
            if (a < 0) {
                cout << "Факториал определен только для неотрицательных целых чисел." << endl;
            }
            else {
                c = factorial((int)a);
            }
            break;
        }
        case 8: {
            cout << "Введите число ";
            cin >> a;
            c = sqrt(a);
            break;
        }
        case 9: {
            p = 2; 
            break;
        }
        default: {
            cout << "Неверный выбор операции." << endl;
            break;
        }
        }
        cout << "Результат =" << c << endl;
    }
    return 0;
}
