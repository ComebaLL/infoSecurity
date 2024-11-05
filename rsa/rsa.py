import random

# Простая проверка на простоту
def is_prime(num):
    if num <= 1:
        return False
    if num <= 3:
        return True
    if num % 2 == 0 or num % 3 == 0:
        return False
    i = 5
    while i * i <= num:
        if num % i == 0 or num % (i + 2) == 0:
            return False
        i += 6
    return True

# Расширенный алгоритм Евклида для нахождения d
def extended_gcd(a, b):
    if b == 0:
        return a, 1, 0
    gcd, x1, y1 = extended_gcd(b, a % b)
    x = y1
    y = x1 - (a // b) * y1
    return gcd, x, y

# Вычисление мультипликативного обратного числа
def mod_inverse(e, phi):
    gcd, x, y = extended_gcd(e, phi)
    if gcd == 1:
        return x % phi
    return None

# Генерация простых чисел
def generate_prime_candidate(bits):
    while True:
        p = random.getrandbits(bits)
        if p % 2 != 0 and is_prime(p):
            return p

# Функция для нахождения взаимно простого числа с phi
def find_coprime(phi):
    e = 3
    while e < phi:
        if extended_gcd(e, phi)[0] == 1:
            return e
        e += 2

# Функция для генерации ключей
def generate_keys(bits=8):
    p = generate_prime_candidate(bits)
    q = generate_prime_candidate(bits)
    n = p * q
    phi = (p - 1) * (q - 1)
    e = find_coprime(phi)
    d = mod_inverse(e, phi)
    return (e, n), (d, n)

# Шифрование сообщения
def encrypt(message, pk):
    e, n = pk
    if not (0 < message < n):
        raise ValueError("Message must be a positive integer smaller than n")
    return pow(message, e, n)

# Расшифрование сообщения
def decrypt(ciphertext, sk):
    d, n = sk
    return pow(ciphertext, d, n)

# Пример использования
public_key, secret_key = generate_keys()
print("Public key:", public_key)
print("Secret key:", secret_key)

# Сообщение для шифрования
message = 42
print("Message:", message)

# Шифруем сообщение
ciphertext = encrypt(message, public_key)
print("Encoded message:", ciphertext)

# Расшифровываем сообщение
decrypted_message = decrypt(ciphertext, secret_key)
print("Decoded message:", decrypted_message)
