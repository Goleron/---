#include <iostream>

int main() {
    setlocale(LC_ALL, "Rus");
    const int rows = 3;
    const int cols = 5;

    double matrix[rows][cols];
    for (int i = 0; i < rows; ++i) {
        std::cout << "Введите элементы строки " << i + 1 << " (5 элементов): ";
        for (int j = 0; j < cols; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    std::cout << "Средние арифметические элементов строк:\n";
    for (int i = 0; i < rows; ++i) {
        double sum = 0;
        for (int j = 0; j < cols; ++j) {
            sum += matrix[i][j];
        }
        double average = sum / cols;
        std::cout << "Строка " << i + 1 << ": " << average << "\n";
    }

    return 0;
}
