import random

# Функция для нахождения длины блока кода Хэмминга для кодирования символов алфавита
def get_hamming_code_length(alphabet_size):
    required_bits = (alphabet_size - 1).bit_length()
    if required_bits <= 4:
        return 7, 4
    elif required_bits <= 11:
        return 15, 11
    elif required_bits <= 26:
        return 31, 26
    else:
        raise ValueError("Размер алфавита слишком большой для данного метода")

# Функция для генерации двоичных кодов символов алфавита
def generate_binary_codes(alphabet):
    binary_codes = {}
    alphabet_size = len(alphabet)
    bits = (alphabet_size - 1).bit_length()
    for i, letter in enumerate(alphabet):
        binary_codes[letter] = format(i, f'0{bits}b')
    return binary_codes

# Функция для вычисления позиций проверочных битов
def get_parity_positions(n):
    positions = []
    i = 0
    while (2 ** i) <= n:
        positions.append(2 ** i)
        i += 1
    return positions

# Кодирование одного символа методом Хэмминга
def hamming_encode(binary_code, parity_positions):
    n = len(binary_code)
    m = len(parity_positions)
    code = list('0' * (n + m))
    j = 0
    for i in range(1, len(code) + 1):
        if i not in parity_positions:
            code[i - 1] = binary_code[j]
            j += 1

    for p in parity_positions:
        parity_sum = 0
        for i in range(1, len(code) + 1):
            if i & p and code[i - 1] == '1':
                parity_sum ^= 1
        code[p - 1] = str(parity_sum)
    return ''.join(code)

# Функция для кодирования сообщения
def encode_message(message, binary_codes, code_length):
    parity_positions = get_parity_positions(code_length[0])
    encoded_message = []
    for char in message:
        binary_code = binary_codes[char]
        encoded_message.append(hamming_encode(binary_code, parity_positions))
    return encoded_message

# Функция для внесения ошибки
def corrupt_bit(encoded_message, index, bit_pos=None):
    if bit_pos is None:
        bit_pos = random.randint(0, len(encoded_message[index]) - 1)
    corrupted_char = list(encoded_message[index])
    corrupted_char[bit_pos] = '1' if corrupted_char[bit_pos] == '0' else '0'
    encoded_message[index] = ''.join(corrupted_char)
    return index, bit_pos

# Функция для обнаружения и исправления ошибок
def detect_and_correct(encoded_char):
    n = len(encoded_char)
    parity_positions = get_parity_positions(n)
    error_pos = 0
    for p in parity_positions:
        parity_sum = 0
        for i in range(1, n + 1):
            if i & p and encoded_char[i - 1] == '1':
                parity_sum ^= 1
        if parity_sum == 1:
            error_pos += p
    if error_pos:
        encoded_char = list(encoded_char)
        encoded_char[error_pos - 1] = '1' if encoded_char[error_pos - 1] == '0' else '0'
        return ''.join(encoded_char), error_pos
    return encoded_char, None

# Функция для декодирования сообщения
def decode_message(encoded_message, code_length):
    decoded_message = ''
    corrupted_info = []
    parity_positions = get_parity_positions(code_length[0])
    for i, encoded_char in enumerate(encoded_message):
        corrected_char, error_pos = detect_and_correct(encoded_char)
        if error_pos:
            corrupted_info.append((i, error_pos - 1))
        decoded_bits = ''.join([corrected_char[j] for j in range(len(corrected_char)) if j + 1 not in parity_positions])
        decoded_char = int(decoded_bits, 2)
        decoded_message += alphabet[decoded_char]
    return decoded_message, corrupted_info

# Основная программа
alphabet = "abcdefghijklmnopqrstuvwxyz"
message = "goal"
code_length = get_hamming_code_length(len(alphabet))
binary_codes = generate_binary_codes(alphabet)

# Кодируем сообщение
encoded_message = encode_message(message, binary_codes, code_length)
print("encode message:", encoded_message)


# Вносим ошибку в случайный символ
corrupted_index, corrupted_bit = corrupt_bit(encoded_message, random.randint(0, len(encoded_message) - 1))
print(f"mistake in {corrupted_index + 1} on pos {corrupted_bit}")

# Декодируем и исправляем ошибки
decoded_message, corrupted_info = decode_message(encoded_message, code_length)
print("decode message:", decoded_message)
print("info about mistake:", corrupted_info)
