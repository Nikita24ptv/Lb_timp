/**
 * @file route.h
 * @author Ваше Имя
 * @version 1.0
 * @date 2025-12-09
 * @brief Заголовочный файл для модуля шифрования методом табличной маршрутной перестановки
 * @warning Реализация только для английского языка
 */

#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
using namespace std;

/**
 * @class cipher_error
 * @brief Класс исключения для ошибок шифрования
 * @details Производный от std::invalid_argument, используется для обработки ошибок в модуле шифрования
 */
class cipher_error: public invalid_argument {
public:
    explicit cipher_error(const string& what_arg):
        invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg):
        invalid_argument(what_arg) {}
};

/**
 * @class code
 * @brief Класс для шифрования и расшифрования методом табличной маршрутной перестановки
 * @details Использует таблицу с заданным количеством столбцов (ключ). 
 *          Запись: по строкам слева направо, сверху вниз.
 *          Чтение: по столбцам сверху вниз, справа налево.
 */
class code {
private:
    int key; ///< Количество столбцов таблицы (ключ шифрования)

    /**
     * @brief Проверяет и возвращает валидный ключ
     * @param key Предлагаемый ключ
     * @param Text Открытый текст для проверки длины
     * @return Валидный ключ
     * @throw cipher_error Если ключ некорректного размера
     */
    inline int getValidKey(int key, const string& Text);

    /**
     * @brief Проверяет и нормализует открытый текст
     * @param s Исходный открытый текст
     * @return Текст без пробелов и с проверкой символов
     * @throw cipher_error Если текст пустой или содержит некорректные символы
     */
    inline string getValidOpenText(const string& s);

    /**
     * @brief Проверяет зашифрованный текст на соответствие длине
     * @param s Зашифрованный текст
     * @param open_text Исходный открытый текст
     * @return Зашифрованный текст без изменений
     * @throw cipher_error Если длины текстов не совпадают
     */
    inline string getValidCipherText(const string& s, const string& open_text);

public:
    code() = delete; ///< Запрет конструктора без параметров

    /**
     * @brief Конструктор с ключом и текстом
     * @param skey Ключ шифрования (количество столбцов)
     * @param text Открытый текст для проверки длины ключа
     * @throw cipher_error Если ключ некорректного размера
     */
    code(int skey, string text);

    /**
     * @brief Шифрует открытый текст методом маршрутной перестановки
     * @param text Текст для шифрования
     * @return Зашифрованная строка
     * @throw cipher_error Если текст пустой или содержит некорректные символы
     */
    string encryption(const string& text);

    /**
     * @brief Расшифровывает зашифрованный текст
     * @param text Зашифрованный текст
     * @param open_text Исходный открытый текст (для проверки длины)
     * @return Расшифрованная строка
     * @throw cipher_error Если тексты пустые, содержат некорректные символы или разной длины
     */
    string transcript(const string& text, const string& open_text);
};