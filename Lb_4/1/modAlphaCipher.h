/**
 * @file modAlphaCipher.h
 * @author Никита Седнёв
 * @version 1.0
 * @date 2025-11-27
 * @brief Заголовочный файл для модуля шифрования методом Гронсфельда (русская версия)
 * @warning Реализация только для русского языка (алфавит: А-Я, Ё)
 */

#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <locale>
#include <codecvt>

/**
 * @class cipher_error
 * @brief Класс исключения для ошибок шифрования
 * @details Производный от std::invalid_argument, используется для обработки ошибок в модуле шифрования
 */
class cipher_error: public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg):
        std::invalid_argument(what_arg) {}
};

/**
 * @class modAlphaCipher
 * @brief Класс для шифрования и расшифрования текста методом Гронсфельда (русский алфавит)
 * @details Использует русский алфавит из 33 букв (А-Я, Ё). 
 *          Ключ и текст должны содержать только русские буквы (регистр не важен).
 */
class modAlphaCipher {
private:
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; ///< Алфавит по порядку
    std::map<wchar_t,int> alphaNum; ///< Ассоциативный массив "символ -> номер"
    std::vector<int> key; ///< Ключ в числовом виде

    std::vector<int> convert(const std::string& s);
    std::string convert(const std::vector<int>& v);
    std::string getValidKey(const std::string & s);
    std::string getValidOpenText(const std::string & s);
    std::string getValidCipherText(const std::string & s);

public:
    modAlphaCipher() = delete; ///< Запрет конструктора без параметров

    /**
     * @brief Конструктор с ключом
     * @param skey Ключ в виде строки
     * @throw cipher_error Если ключ пустой, содержит не-буквы или является слабым (одинаковые символы)
     */
    modAlphaCipher(const std::string& skey);

    /**
     * @brief Шифрует открытый текст
     * @param open_text Текст для шифрования
     * @return Зашифрованная строка (в верхнем регистре)
     * @throw cipher_error Если текст пустой или не содержит букв
     */
    std::string encrypt(const std::string& open_text);

    /**
     * @brief Расшифровывает зашифрованный текст
     * @param cipher_text Зашифрованный текст
     * @return Расшифрованная строка (в верхнем регистре)
     * @throw cipher_error Если текст пустой или содержит недопустимые символы
     */
    std::string decrypt(const std::string& cipher_text);
};