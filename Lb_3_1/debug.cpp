#include <iostream>
#include "modAlphaCipher.h"
using namespace std;

int main() {
    try {
        // Тестируем базовые случаи
        modAlphaCipher cipher1("КОД");
        cout << "Ключ: КОД, Текст: МАМАМ" << endl;
        cout << "Результат: " << cipher1.encrypt("МАМАМ") << endl;
        
        modAlphaCipher cipher2("Б");
        cout << "Ключ: Б, Текст: ОБЕДЕННЫЙПЕРЕРЫВ" << endl;
        cout << "Результат: " << cipher2.encrypt("ОБЕДЕННЫЙПЕРЕРЫВ") << endl;
        
        modAlphaCipher cipher3("Я");
        cout << "Ключ: Я, Текст: ОБЕДЕННЫЙПЕРЕРЫВ" << endl;
        cout << "Результат: " << cipher3.encrypt("ОБЕДЕННЫЙПЕРЕРЫВ") << endl;
        
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
    return 0;
}