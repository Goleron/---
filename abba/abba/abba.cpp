#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

string reverse(const string& word) {
    setlocale(LC_ALL, "Rus");
    string reversedWord = word;
    reverse(reversedWord.begin(), reversedWord.end());
    return reversedWord;
}

string removeVowels(const string& word) {
    setlocale(LC_ALL, "Rus");
    string result;
    for (char ch : word) {
        if (string("aeiouAEIOU").find(ch) == string::npos) {
            result += ch;
        }
    }
    return result;
}

string removeConsonants(const string& word) {
    setlocale(LC_ALL, "Rus");
    string result;
    for (char ch : word) {
        if (string("aeiouAEIOU").find(ch) != string::npos) {
            result += ch;
        }
    }
    return result;
}

string shuffle(const string& word) {
    setlocale(LC_ALL, "Rus");
    string shuffledWord = word;
    random_shuffle(shuffledWord.begin(), shuffledWord.end());
    return shuffledWord;
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(static_cast<unsigned int>(time(0)));

    string word;
    int choice;

    cout << "Введите слово: ";
    cin >> word;

    do {
        cout << "\nМеню:\n"
            << "1. Вывести слово задом наперед\n"
            << "2. Вывести слово без гласных\n"
            << "3. Вывести слово без согласных\n"
            << "4. Рандомно раскидывать буквы заданного слова\n"
            << "5. Выйти\n"
            << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Результат: " << reverse(word) << endl;
            break;
        case 2:
            cout << "Результат: " << removeVowels(word) << endl;
            break;
        case 3:
            cout << "Результат: " << removeConsonants(word) << endl;
            break;
        case 4:
            cout << "Результат: " << shuffle(word) << endl;
            break;
        case 5:
            cout << "Выход из программы..." << endl;
            break;
        default:
            cout << "Неверный выбор. Пожалуйста, выберите снова." << endl;
        }
    } while (choice != 5);

    return 0;
}
