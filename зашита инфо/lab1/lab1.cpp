// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Функция для шифрования строки с помощью шифра Цезаря
string encryptCaesar(const string& text, int shift, const string& alphabet) {
    string result = "";
    int n = alphabet.size();

    for (char c : text) {
        size_t index = alphabet.find(c);
        if (index != string::npos) {
            // сдвигаем индекс символа и возвращаем зашифрованный символ
            result += alphabet[(index + shift) % n];
        }
        else {
            result += c; // оставляем символ без изменений, если он не в алфавите
        }
    }

    return result;
}

// Функция для расшифровки строки с помощью шифра Цезаря
string decryptCaesar(const string& text, int shift, const string& alphabet) {
    string result = "";
    int n = alphabet.size();

    for (char c : text) {
        size_t index = alphabet.find(c);
        if (index != string::npos) {
            // сдвигаем индекс символа назад и возвращаем расшифрованный символ
            result += alphabet[(index - shift + n) % n];
        }
        else {
            result += c; // оставляем символ без изменений, если он не в алфавите
        }
    }

    return result;
}

// Функция для атаки полным перебором
vector<string> bruteForceCaesar(const string& text, const string& alphabet) {
    vector<string> variants;
    int n = alphabet.size();

    for (int shift = 0; shift < n; ++shift) {
        variants.push_back(decryptCaesar(text, shift, alphabet));
    }

    return variants;
}

int main() {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // указанный алфавит
    string text;
    int shift;

    cout << "enter text: ";
    getline(cin, text);
    cout << "shift size: ";
    cin >> shift;

    // Шифрование
    string encrypted = encryptCaesar(text, shift, alphabet);
    cout << "encrypted text.: " << encrypted << endl;

    // Расшифровка
    string decrypted = decryptCaesar(encrypted, shift, alphabet);
    cout << "decrypt сaesar: " << decrypted << endl;

    // Атака полным перебором
    cout << "\nDecryption options (brute force):" << endl;
    vector<string> variants = bruteForceCaesar(encrypted, alphabet);
    for (int i = 0; i < variants.size(); ++i) {
        cout << "shift " << i << ": " << variants[i] << endl;
    }

    return 0;
}
