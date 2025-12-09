/**
 * @file modAlphaCipher.cpp
 * @author Никита Седнёв
 * @version 1.0
 * @date 2025-11-27
 * @brief Реализация класса modAlphaCipher для шифрования методом Гронсфельда (русская версия)
 */

#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>
#include <iostream>

std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> codec; ///< Конвертер UTF-8 <-> wstring

/**
 * @brief Конструктор класса modAlphaCipher
 * @param skey Ключ шифрования
 * @throw cipher_error При недопустимом ключе
 */
modAlphaCipher::modAlphaCipher(const std::string& skey) {
    for (unsigned i = 0; i < numAlpha.size(); i++)
        alphaNum[numAlpha[i]] = i;
    key = convert(getValidKey(skey));
    
    if (key.size() > 1) {
        bool allSame = true;
        for (size_t i = 1; i < key.size(); i++) {
            if (key[i] != key[0]) {
                allSame = false;
                break;
            }
        }
        if (allSame)
            throw cipher_error("WeakKey");
    }
}

/**
 * @brief Шифрование текста
 * @param open_text Открытый текст
 * @return Зашифрованная строка
 */
std::string modAlphaCipher::encrypt(const std::string& open_text) {
    std::vector<int> work = convert(getValidOpenText(open_text));
    for (unsigned i = 0; i < work.size(); i++)
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    return convert(work);
}

/**
 * @brief Расшифрование текста
 * @param cipher_text Зашифрованный текст
 * @return Расшифрованная строка
 */
std::string modAlphaCipher::decrypt(const std::string& cipher_text) {
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for (unsigned i = 0; i < work.size(); i++)
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    return convert(work);
}

/**
 * @brief Преобразует строку в вектор числовых кодов
 * @param s Входная строка
 * @return Вектор номеров символов в алфавите
 */
std::vector<int> modAlphaCipher::convert(const std::string& s) {
    std::wstring ws = codec.from_bytes(s);
    std::vector<int> result;
    for (auto c : ws)
        result.push_back(alphaNum[c]);
    return result;
}

/**
 * @brief Преобразует вектор числовых кодов в строку
 * @param v Вектор номеров символов
 * @return Строка, соответствующая вектору
 */
std::string modAlphaCipher::convert(const std::vector<int>& v) {
    std::wstring ws;
    for (auto i : v)
        ws.push_back(numAlpha[i]);
    std::string result = codec.to_bytes(ws);
    return result;
}

/**
 * @brief Проверяет и нормализует ключ
 * @param s Исходный ключ
 * @return Ключ в верхнем регистре без не-букв
 * @throw cipher_error Если ключ пустой или содержит не-буквы
 */
std::string modAlphaCipher::getValidKey(const std::string & s) {
    std::wstring ws = codec.from_bytes(s);
    if (ws.empty())
        throw cipher_error("Пустой ключ");
    
    std::wstring tmp = ws;
    for (auto& c : tmp) {
        if (c < L'А' || c > L'я')
            throw cipher_error("Неверный ключ: содержит не-буквенные символы");
        if (c >= L'а' && c <= L'я')
            c -= 32;
    }
    
    std::string mp = codec.to_bytes(tmp);
    return mp;
}

/**
 * @brief Проверяет и нормализует открытый текст
 * @param s Исходный открытый текст
 * @return Текст в верхнем регистре без не-букв
 * @throw cipher_error Если текст пустой после удаления не-букв
 */
std::string modAlphaCipher::getValidOpenText(const std::string & s) {
    std::wstring ws = codec.from_bytes(s);
    std::wstring tmp;
    
    for (auto c : ws) {
        if (c >= L'А' && c <= L'я') {
            if (c >= L'а' && c <= L'я')
                tmp.push_back(c - 32);
            else
                tmp.push_back(c);
        }
    }
    
    if (tmp.empty())
        throw cipher_error("Отсутствует открытый текст!");
    
    std::string mp = codec.to_bytes(tmp);
    return mp;
}

/**
 * @brief Проверяет зашифрованный текст
 * @param s Зашифрованный текст
 * @return Текст без изменений
 * @throw cipher_error Если текст пустой или содержит недопустимые символы
 */
std::string modAlphaCipher::getValidCipherText(const std::string & s) {
    std::wstring ws = codec.from_bytes(s);
    
    if (ws.empty())
        throw cipher_error("Empty cipher text");
    
    for (auto c : ws) {
        if ((c < L'А' || c > L'Я') && c != L'Ё')
            throw cipher_error("Неправильный зашифрованный текст!");
    }
    
    std::string mp = codec.to_bytes(ws);
    return mp;
}