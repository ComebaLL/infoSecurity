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

// Вывод вектора с пояснением
void printVector(const string& description, const vector<int>& vec, int limit = 10) {
    cout << description << ": [";
    for (size_t i = 0; i < min(vec.size(), static_cast<size_t>(limit)); ++i) {
        cout << vec[i];
        if (i < min(vec.size(), static_cast<size_t>(limit)) - 1) cout << ", ";
    }
    if (vec.size() > limit) cout << ", ...";
    cout << "]" << endl;
}

int main() {
    // Сообщение для шифрования
    string message = "asdasdkmasd";
    cout << "Message: " << message << endl;

    // Шаг 1: Создание ключа
    vector<int> key = generateKey();
    printVector("Key", key);

    // Шаг 2: Инициализация генератора
    vector<int> gen = initializeGenerator(key);
    printVector("Initialized random number generator", gen);

    // Шаг 3: Генерация гаммы
    vector<int> messageBytes = stringToBytes(message);
    printVector("Unicode codes of message characters", messageBytes);

    vector<int> gamma = generateGamma(gen, messageBytes.size());
    printVector("Gamma", gamma);

    // Шаг 4: Шифрование
    vector<int> encryptedMessage = xorMessage(messageBytes, gamma);
    printVector("Encrypted message (list)", encryptedMessage);

    // Преобразование зашифрованного сообщения в строку Unicode
    string encryptedString = bytesToString(encryptedMessage);
    cout << "Encrypted message (Unicode characters): " << encryptedString << endl;

    // Шаг 5: Расшифрование
    vector<int> decryptedMessage = xorMessage(encryptedMessage, gamma);
    printVector("Decrypted message (list)", decryptedMessage);

    string decryptedString = bytesToString(decryptedMessage);
    cout << "Decrypted message (Unicode characters): " << decryptedString << endl;

    return 0;
}