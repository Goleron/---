#include <iostream>
#include <string>
#include <windows.h>

typedef bool (*ContainsCharsFunc)(const char*, const char*);

int main() {
    setlocale(LC_ALL, "Rus");
    std::string inputString, charsToFind;
    std::cout << "Введите строку: ";
    std::getline(std::cin, inputString);
    std::cout << "Введите символы для поиска: ";
    std::getline(std::cin, charsToFind);

    HMODULE hLib = LoadLibrary(TEXT("CheckChars.dll"));
    if (hLib == NULL) {
        std::cerr << "Не удалось загрузить библиотеку!" << std::endl;
        return 1;
    }

    ContainsCharsFunc containsChars = (ContainsCharsFunc)GetProcAddress(hLib, "containsChars");
    if (containsChars == NULL) {
        std::cerr << "Не удалось найти функцию containsChars в библиотеке!" << std::endl;
        FreeLibrary(hLib);
        return 1;
    }

    bool result = containsChars(inputString.c_str(), charsToFind.c_str());
    if (result) {
        std::cout << "Все символы найдены в строке." << std::endl;
    }
    else {
        std::cout << "Не все символы найдены в строке." << std::endl;
    }

    FreeLibrary(hLib);
    return 0;
}
