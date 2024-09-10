// affinshifr.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <string>
#include <stdexcept>
#include <numeric> // Для std::gcd

using namespace std;


// Реализация алгоритма Евклида для вычисления НОД
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Структура для арифметики по модулю
struct ModArithmetic {
    int mod; // Модуль

    // Конструктор
    ModArithmetic(int m) : mod(m) {}

    // Нахождение обратного по модулю числа
    int modInverse(int a) {
        int m0 = mod, t, q;
        int x0 = 0, x1 = 1;

        if (mod == 1)
            return 0;

        // Расширенный алгоритм Евклида для нахождения обратного по модулю
        while (a > 1) {
            q = a / mod;
            t = mod;

            // mod теперь остаток от a
            mod = a % mod;
            a = t;
            t = x0;

            x0 = x1 - q * x0;
            x1 = t;
        }

        // Убедимся, что обратное число положительное
        if (x1 < 0)
            x1 += m0;

        mod = m0; // Восстановление модуля
        return x1;
    }

    // Операция по модулю (остаток от деления)
    int modOp(int x) {
        return (x % mod + mod) % mod;
    }
};

// Функция для шифрования с использованием аффинного шифра
string affineEncrypt(const string& text, int a, int b, const string& alphabet, ModArithmetic& modOps) {
    string result = "";
    int n = alphabet.size(); // Длина алфавита

    for (char c : text) {
        size_t index = alphabet.find(c);
        if (index != string::npos) {
            // Формула шифрования: (a * x + b) % N
            int encryptedIndex = modOps.modOp(a * index + b);
            result += alphabet[encryptedIndex];
        }
        else {
            result += c; // Оставляем символы, которые не входят в алфавит, без изменений
        }
    }

    return result;
}

// Функция для расшифровки с использованием аффинного шифра
string affineDecrypt(const string& text, int a, int b, const string& alphabet, ModArithmetic& modOps) {
    string result = "";
    int n = alphabet.size(); // Длина алфавита
    int a_inv = modOps.modInverse(a); // Обратное к a по модулю N

    for (char c : text) {
        size_t index = alphabet.find(c);
        if (index != string::npos) {
            // Формула расшифровки: a^-1 * (y - b) % N
            int decryptedIndex = modOps.modOp(a_inv * (index - b));
            result += alphabet[decryptedIndex];
        }
        else {
            result += c; // Оставляем символы, которые не входят в алфавит, без изменений
        }
    }

    return result;
}

int main() {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // Алфавит
    int a, b;
    string text;

    cout << "Enter the text to encrypt: ";
    getline(cin, text);

    cout << "Enter parameter a (should be coprime with alphabet size): ";
    cin >> a;

    cout << "Enter parameter b: ";
    cin >> b;

    int n = alphabet.size();

    // Проверим, что a и N взаимно просты
    if (gcd(a, n) != 1) {
        cerr << "Error: parameter 'a' must be coprime with the alphabet size (gcd(a, N) = 1)." << endl;
        return 1;
    }

    // Инициализируем структуру для арифметики по модулю
    ModArithmetic modOps(n);

    // Шифрование
    string encryptedText = affineEncrypt(text, a, b, alphabet, modOps);
    cout << "Encrypted text: " << encryptedText << endl;

    // Расшифровка
    string decryptedText = affineDecrypt(encryptedText, a, b, alphabet, modOps);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
