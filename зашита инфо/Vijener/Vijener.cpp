// Vijener.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <string>

using namespace std;

// Функция для шифрования с помощью шифра Виженера
string encryptVigenere(const string& text, const string& key, const string& alphabet) {
    string result = ""; // Зашифрованный результат
    int n = alphabet.size(); // Длина алфавита
    int keyLen = key.size(); // Длина ключевого слова
    int textLen = text.size(); // Длина текста

    // Проходим по каждому символу текста
    for (int i = 0; i < textLen; ++i) {
        char c = text[i];
        size_t index = alphabet.find(c); // Ищем индекс символа в алфавите
        if (index != string::npos) {
            // Найти символ ключа, соответствующий текущей позиции текста (ключ повторяется циклически)
            char keyChar = key[i % keyLen];
            size_t keyIndex = alphabet.find(keyChar); // Ищем индекс символа ключа
            if (keyIndex != string::npos) {
                // Шифрование: (индекс символа + индекс символа ключа) по модулю длины алфавита
                result += alphabet[(index + keyIndex) % n];
            }
        }
        else {
            result += c; // Оставляем символ без изменений, если он не в алфавите
        }
    }

    return result;
}

// Функция для расшифровки с помощью шифра Виженера
string decryptVigenere(const string& text, const string& key, const string& alphabet) {
    string result = ""; // Расшифрованный результат
    int n = alphabet.size(); // Длина алфавита
    int keyLen = key.size(); // Длина ключевого слова
    int textLen = text.size(); // Длина текста

    // Проходим по каждому символу зашифрованного текста
    for (int i = 0; i < textLen; ++i) {
        char c = text[i];
        size_t index = alphabet.find(c); // Ищем индекс символа в алфавите
        if (index != string::npos) {
            // Найти символ ключа, соответствующий текущей позиции текста (ключ повторяется циклически)
            char keyChar = key[i % keyLen];
            size_t keyIndex = alphabet.find(keyChar); // Ищем индекс символа ключа
            if (keyIndex != string::npos) {
                // Расшифровка: (индекс символа - индекс символа ключа + длина алфавита) по модулю
                result += alphabet[(index - keyIndex + n) % n];
            }
        }
        else {
            result += c; // Оставляем символ без изменений, если он не в алфавите
        }
    }

    return result;
}

int main() {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // Алфавит, который можно изменить
    string text, key;

    // Ввод текста для шифрования
    cout << "Enter the text to encrypt: ";
    getline(cin, text);

    // Ввод ключевого слова
    cout << "Enter the keyword: ";
    getline(cin, key);

    // Шифрование текста с помощью шифра Виженера
    string encrypted = encryptVigenere(text, key, alphabet);
    cout << "Encrypted text: " << encrypted << endl;

    // Расшифровка текста с помощью шифра Виженера
    string decrypted = decryptVigenere(encrypted, key, alphabet);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}
