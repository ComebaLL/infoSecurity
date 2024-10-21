#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>

using namespace std;

// Функция для создания случайной перестановки
vector<int> generateKey() {
    vector<int> key(256);
    iota(key.begin(), key.end(), 0);
    random_device rd;
    mt19937 g(rd());
    shuffle(key.begin(), key.end(), g);
    return key;
}

// Инициализация генератора случайных чисел
vector<int> initializeGenerator(vector<int>& key) {
    vector<int> gen = key;
    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + gen[i] + key[i]) % 256;
        swap(gen[i], gen[j]);
    }
    return gen;
}

// Генерация гаммы для сообщения
vector<int> generateGamma(vector<int>& gen, int messageLength) {
    vector<int> gamma(messageLength);
    int i = 0, j = 0;
    for (int k = 0; k < messageLength; ++k) {
        i = (i + 1) % 256;
        j = (j + gen[i]) % 256;
        swap(gen[i], gen[j]);
        int t = (gen[i] + gen[j]) % 256;
        gamma[k] = gen[t];
    }
    return gamma;
}

// Шифрование и расшифрование сообщения
vector<int> xorMessage(const vector<int>& message, const vector<int>& gamma) {
    vector<int> result(message.size());
    for (size_t i = 0; i < message.size(); ++i) {
        result[i] = message[i] ^ gamma[i];
    }
    return result;
}

// Преобразование строки в вектор байтов
vector<int> stringToBytes(const string& str) {
    vector<int> bytes(str.begin(), str.end());
    return bytes;
}

// Преобразование вектора байтов обратно в строку
string bytesToString(const vector<int>& bytes) {
    return string(bytes.begin(), bytes.end());
}

int main() {

    // Сообщение для шифрования
    string message = "sdadadad";
    cout << "message: " << message << endl;

    // Шаг 1: Создание ключа
    vector<int> key = generateKey();
    cout << "Key" << endl;

    // Шаг 2: Инициализация генератора
    vector<int> gen = initializeGenerator(key);
    cout << "Generator" << endl;

    // Шаг 3: Генерация гаммы
    vector<int> messageBytes = stringToBytes(message);
    vector<int> gamma = generateGamma(gen, messageBytes.size());

    // Шаг 4: Шифрование
    vector<int> encryptedMessage = xorMessage(messageBytes, gamma);
    cout << "Message encrypted:" << bytesToString(encryptedMessage) << endl;

    // Шаг 5: Расшифрование
    vector<int> decryptedMessage = xorMessage(encryptedMessage, gamma);
    cout << "message decrypted: " << bytesToString(decryptedMessage) << endl;

    return 0;
}
