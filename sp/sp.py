import random

# 1. Перевод символа в 16-битную последовательность
def char_to_bin(char):
    return format(ord(char), '016b')

# 2. Перевод строки из двух символов в 32-битную последовательность
def str_to_bin(string):
    return char_to_bin(string[0]) + char_to_bin(string[1])

# 3. Генерация случайной перестановки
def generate_permutation(lst):
    for _ in range(64):  # 64 раза меняем случайные пары
        i, j = random.sample(range(len(lst)), 2)
        lst[i], lst[j] = lst[j], lst[i]
    return lst

# 4. P-блок (шифрование)
def p_block_encrypt(bin_seq, permutation):
    return ''.join(bin_seq[i] for i in permutation)

# 5. P-блок (расшифрование)
def p_block_decrypt(bin_seq, permutation):
    result = [''] * len(permutation)
    for i, p in enumerate(permutation):
        result[p] = bin_seq[i]
    return ''.join(result)

# 6. S-блок (шифрование)
def s_block_encrypt(four_bits, s_permutation):
    decimal = int(four_bits, 2)
    encrypted_decimal = s_permutation[decimal]
    return format(encrypted_decimal, '04b')

# 7. S-блок (расшифрование)
def s_block_decrypt(four_bits, s_permutation):
    decimal = int(four_bits, 2)
    decrypted_decimal = s_permutation.index(decimal)
    return format(decrypted_decimal, '04b')

# 8. Разбить 32-битную последовательность на 8 частей по 4 бита и зашифровать S-блоками
def apply_s_blocks(bin_seq, s_permutation):
    encrypted_seq = ''
    for i in range(0, len(bin_seq), 4):
        encrypted_seq += s_block_encrypt(bin_seq[i:i+4], s_permutation)
    return encrypted_seq

# 9. Расшифровать с помощью батареи S-блоков
def apply_s_blocks_decrypt(bin_seq, s_permutation):
    decrypted_seq = ''
    for i in range(0, len(bin_seq), 4):
        decrypted_seq += s_block_decrypt(bin_seq[i:i+4], s_permutation)
    return decrypted_seq

# Перевод обратно в строку
def bin_to_str(bin_seq):
    first_char = chr(int(bin_seq[:16], 2))
    second_char = chr(int(bin_seq[16:], 2))
    return first_char + second_char

# Основная программа

# Генерация перестановок
p_permutation = generate_permutation(list(range(32)))  # Полная перестановка для 32 бит
s_permutation = generate_permutation(list(range(16)))

# Пример строки для шифрования
message = "ЖП"

# Шифрование
print(f"Исходное сообщение: {message}")

# Перевод строки в 32-битную последовательность
bin_seq = str_to_bin(message)
print(f"Битовая форма исходного сообщения: {bin_seq}")

# Шифрование P-блоком (теперь для всей 32-битной строки)
encrypted_p1 = p_block_encrypt(bin_seq, p_permutation)
print(f"Зашифрованная p-блоком битовая форма: {encrypted_p1}")

# Шифрование S-блоками
encrypted_s_blocks = apply_s_blocks(encrypted_p1, s_permutation)
print(f"Зашифрованная батареей s-блоков битовая форма: {encrypted_s_blocks}")

# Шифрование P-блоком
final_encrypted = p_block_encrypt(encrypted_s_blocks, p_permutation)
print(f"Зашифрованная p-блоком битовая форма: {final_encrypted}")

# Перевод зашифрованной последовательности в строку
encrypted_message = bin_to_str(final_encrypted)
print(f"Зашифрованное сообщение: {encrypted_message}")

print("\nПереходим к расшифровке...")

# Расшифрование
# Расшифрование P-блоком
decrypted_p1 = p_block_decrypt(final_encrypted, p_permutation)
print(f"Расшифрованная обратным p-блоком битовая форма: {decrypted_p1}")

# Расшифрование S-блоками
decrypted_s_blocks = apply_s_blocks_decrypt(decrypted_p1, s_permutation)
print(f"Расшифрованная батареей обратных s-блоков битовая форма: {decrypted_s_blocks}")

# Расшифрование P-блоком
final_decrypted = p_block_decrypt(decrypted_s_blocks, p_permutation)
print(f"Расшифрованная обратным p-блоком битовая форма: {final_decrypted}")

# Перевод обратно в строку
decrypted_message = bin_to_str(final_decrypted)
print(f"Расшифрованное сообщение: {decrypted_message}")
