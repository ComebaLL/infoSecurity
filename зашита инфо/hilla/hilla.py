import numpy as np

# Определим алфавит (английский алфавит A-Z)
alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
n = len(alphabet)

# Преобразование символа в индекс
def char_to_index(c):
    return alphabet.index(c)

# Преобразование индекса в символ
def index_to_char(i):
    return alphabet[i % n]

# Шифрование Хилла
def hill_encrypt(plain_text, A):
    # Преобразуем текст в числа
    plain_indices = [char_to_index(c) for c in plain_text]
    
    # Делаем размер текста кратным размеру матрицы
    m = A.shape[0]
    if len(plain_indices) % m != 0:
        # Дополняем текст 'X', если не кратен размеру
        plain_indices += [char_to_index('X')] * (m - len(plain_indices) % m)

    # Разбиваем на блоки и шифруем
    encrypted_indices = []
    for i in range(0, len(plain_indices), m):
        block = plain_indices[i:i + m]
        encrypted_block = np.dot(A, block) % n
        encrypted_indices.extend(encrypted_block)
    
    # Преобразуем обратно в текст
    encrypted_text = ''.join(index_to_char(i) for i in encrypted_indices)
    return encrypted_text

# Расшифрование Хилла
def hill_decrypt(cipher_text, A_inv):
    # Преобразуем зашифрованный текст в числа
    cipher_indices = [char_to_index(c) for c in cipher_text]
    
    m = A_inv.shape[0]
    
    # Разбиваем на блоки и расшифровываем
    decrypted_indices = []
    for i in range(0, len(cipher_indices), m):
        block = cipher_indices[i:i + m]
        decrypted_block = np.dot(A_inv, block) % n
        decrypted_indices.extend(decrypted_block)
    
    # Преобразуем обратно в текст
    decrypted_text = ''.join(index_to_char(i) for i in decrypted_indices)
    return decrypted_text

# Пример использования

# Матрица для шифрования (ключ)
A = np.array([[3, 3],
              [2, 5]])

# Инверсия матрицы по модулю 26
# Используем функцию для нахождения обратной матрицы по модулю
def matrix_mod_inv(A, mod):
    det = int(np.round(np.linalg.det(A)))  # Определитель
    det_inv = pow(det, -1, mod)  # Обратный определитель по модулю
    A_inv = det_inv * np.round(det * np.linalg.inv(A)).astype(int) % mod
    return A_inv

# Инвертируем матрицу A
A_inv = matrix_mod_inv(A, n)

# Текст для шифрования
plain_text = "ASDASDADSasdass"

# Шифрование
cipher_text = hill_encrypt(plain_text, A)
print(f"Зашифрованный текст: {cipher_text}")

# Расшифрование
decrypted_text = hill_decrypt(cipher_text, A_inv)
print(f"Расшифрованный текст: {decrypted_text}")
