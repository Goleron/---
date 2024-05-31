#include <iostream>
#include <string>
#include <windows.h>

typedef bool (*ContainsCharsFunc)(const char*, const char*);

int main() {
    setlocale(LC_ALL, "Rus");
    std::string inputString, charsToFind;
    std::cout << "������� ������: ";
    std::getline(std::cin, inputString);
    std::cout << "������� ������� ��� ������: ";
    std::getline(std::cin, charsToFind);

    HMODULE hLib = LoadLibrary(TEXT("CheckChars.dll"));
    if (hLib == NULL) {
        std::cerr << "�� ������� ��������� ����������!" << std::endl;
        return 1;
    }

    ContainsCharsFunc containsChars = (ContainsCharsFunc)GetProcAddress(hLib, "containsChars");
    if (containsChars == NULL) {
        std::cerr << "�� ������� ����� ������� containsChars � ����������!" << std::endl;
        FreeLibrary(hLib);
        return 1;
    }

    bool result = containsChars(inputString.c_str(), charsToFind.c_str());
    if (result) {
        std::cout << "��� ������� ������� � ������." << std::endl;
    }
    else {
        std::cout << "�� ��� ������� ������� � ������." << std::endl;
    }

    FreeLibrary(hLib);
    return 0;
}
