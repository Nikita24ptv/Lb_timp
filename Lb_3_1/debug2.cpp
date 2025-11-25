#include <iostream>
#include "modAlphaCipher.h"
#include <iomanip>
using namespace std;

void printHex(const string& str) {
    for(unsigned char c : str) {
        cout << hex << setw(2) << setfill('0') << (int)c << " ";
    }
    cout << endl;
}

int main() {
    try {
        cout << "=== Точное тестирование ===" << endl;
        
        // Тест 1: Длинный ключ
        cout << "1. Ключ: ПАРОЛЬ, Текст: МАМАМ" << endl;
        modAlphaCipher cipher1("ПАРОЛЬ");
        string result1 = cipher1.encrypt("МАМАМ");
        cout << "Результат: " << result1 << endl;
        cout << "Hex: "; printHex(result1);
        cout << endl;
        
        // Тест 2: Основной тест
        cout << "2. Ключ: Б, Текст: ОБЕДЕННЫЙПЕРЕРЫВ" << endl;
        modAlphaCipher cipher2("Б");
        string result2 = cipher2.encrypt("ОБЕДЕННЫЙПЕРЕРЫВ");
        cout << "Результат: " << result2 << endl;
        cout << "Hex: "; printHex(result2);
        cout << "Длина: " << result2.length() << endl;
        cout << endl;
        
        // Тест 3: Максимальный сдвиг
        cout << "3. Ключ: Я, Текст: ОБЕДЕННЫЙПЕРЕРЫВ" << endl;
        modAlphaCipher cipher3("Я");
        string result3 = cipher3.encrypt("ОБЕДЕННЫЙПЕРЕРЫВ");
        cout << "Результат: " << result3 << endl;
        cout << "Hex: "; printHex(result3);
        cout << endl;
        
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
    return 0;
}