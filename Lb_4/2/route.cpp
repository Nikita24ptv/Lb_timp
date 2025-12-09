/**
 * @file route.cpp
 * @author Ваше Имя
 * @version 1.0
 * @date 2025-12-09
 * @brief Реализация класса code для шифрования методом табличной маршрутной перестановки
 */

#include "route.h"

/**
 * @brief Конструктор класса code
 * @param skey Ключ шифрования
 * @param text Открытый текст
 * @throw cipher_error Если ключ некорректного размера
 */
code::code(int skey, string text) {
    key = getValidKey(skey, text);
}

/**
 * @brief Шифрование текста методом табличной маршрутной перестановки
 * @param text Открытый текст
 * @return Зашифрованная строка
 */
string code::encryption(const string& text) {
    string t = getValidOpenText(text);
    int k = 0;
    int simvoli = t.size();
    int stroki = simvoli / key;
    char** tabl = new char* [stroki];
    for (int i = 0; i < stroki; i++)
        tabl[i] = new char [key];

    // Запись по строкам слева направо
    for (int i = 0; i < stroki; i++)
        for (int j = 0; j < key; j++) {
            if(k < simvoli) {
                tabl[i][j] = t[k];
                k++;
            }
        }

    // Чтение по столбцам справа налево
    k = 0;
    for (int j = key - 1; j >= 0 ; j--)
        for (int i = 0; i < stroki; i++) {
            t[k] = tabl[i][j];
            k++;
        }

    // Очистка памяти
    for (int i = 0; i < stroki; i++)
        delete[] tabl[i];
    delete[] tabl;

    return t;
}

/**
 * @brief Расшифрование текста
 * @param text Зашифрованный текст
 * @param open_text Исходный открытый текст
 * @return Расшифрованная строка
 */
string code::transcript(const string& text, const string& open_text) {
    if (text.empty() || open_text.empty()) {
        throw cipher_error("Один из текстов пуст!");
    }

    for (char c : text) {
        if (!isalpha(c)) {
            throw cipher_error("Некорректные символы в зашифрованном тексте!");
        }
    }

    for (char c : open_text) {
        if (!isalpha(c)) {
            throw cipher_error("Некорректные символы в открытом тексте!");
        }
    }

    string t = getValidCipherText(text, open_text);
    int k = 0;
    int simvoli = t.size();
    int stroki = simvoli / key;
    char** tabl = new char* [stroki];
    for (int i = 0; i < stroki; i++)
        tabl[i] = new char [key];

    // Заполнение таблицы из зашифрованного текста (обратный порядок чтения)
    for (int j = key - 1; j >= 0 ; j--)
        for (int i = 0; i < stroki; i++) {
            tabl[i][j] = t[k];
            k++;
        }

    // Чтение таблицы по строкам слева направо
    k = 0;
    for (int i = 0; i < stroki; i++)
        for (int j = 0; j < key; j++) {
            t[k] = tabl[i][j];
            k++;
        }

    // Очистка памяти
    for (int i = 0; i < stroki; i++)
        delete[] tabl[i];
    delete[] tabl;

    return t;
}

/**
 * @brief Проверяет зашифрованный текст на соответствие длине
 * @param s Зашифрованный текст
 * @param open_text Открытый текст
 * @return Зашифрованный текст
 * @throw cipher_error Если длины не совпадают
 */
inline string code::getValidCipherText(const string& s, const string& open_text) {
    int r1 = s.size();
    int r2 = open_text.size();
    if (r1 != r2) {
        throw cipher_error("Неправильный зашифрованный текст: " + s);
    }
    return s;
}

/**
 * @brief Проверяет и нормализует открытый текст
 * @param s Открытый текст
 * @return Текст без пробелов
 * @throw cipher_error Если текст пустой или содержит некорректные символы
 */
inline string code::getValidOpenText(const string& s) {
    string text = s;

    if (text.empty()) {
        throw cipher_error("Отсутствует открытый текст!");
    }

    text.erase(remove_if(text.begin(), text.end(), [](char c) {
        if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && c != ' ') {
            throw cipher_error("В тексте встречены некорректные символы!");
        }
        return c == ' ';
    }), text.end());

    return text;
}

/**
 * @brief Проверяет валидность ключа
 * @param key Предлагаемый ключ
 * @param Text Открытый текст
 * @return Валидный ключ
 * @throw cipher_error Если ключ меньше 2 или больше длины текста
 */
inline int code::getValidKey(int key, const string& Text) {
    if (key < 2 || key > Text.length()) {
        throw cipher_error("Ключ некорректного размера");
    }
    return key;
}