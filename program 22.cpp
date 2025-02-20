#include <stdio.h>
#include <stdint.h>

// S-DES S-Boxes
uint8_t SBOX1[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};

uint8_t SBOX2[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};

// Key Schedule (Simplified for S-DES)
uint8_t generate_subkeys(uint16_t key, int round) {
    return (key >> (5 - round)) & 0x1F; // Extract 5-bit subkey
}

// S-DES F function (Simplified)
uint8_t f_function(uint8_t right, uint8_t subkey) {
    // XOR with subkey
    right ^= subkey;
    // Apply S-Boxes
    uint8_t row1 = (right & 0xC) >> 2;
    uint8_t col1 = (right & 0x3);
    uint8_t row2 = (right & 0x30) >> 4;
    uint8_t col2 = (right & 0x0C) >> 2;
    return (SBOX1[row1][col1] << 2) | SBOX2[row2][col2];
}

// S-DES Encryption (Simplified Feistel Structure)
uint8_t sdes_encrypt(uint8_t plaintext, uint16_t key) {
    uint8_t left = plaintext >> 4;
    uint8_t right = plaintext & 0xF;

    for (int round = 1; round <= 2; round++) {
        uint8_t subkey = generate_subkeys(key, round);
        uint8_t temp = right;
        right = left ^ f_function(right, subkey);
        left = temp;
    }

    return (right << 4) | left;
}

// S-DES Decryption (Reversed rounds)
uint8_t sdes_decrypt(uint8_t ciphertext, uint16_t key) {
    uint8_t left = ciphertext >> 4;
    uint8_t right = ciphertext & 0xF;

    for (int round = 2; round >= 1; round--) {
        uint8_t subkey = generate_subkeys(key, round);
        uint8_t temp = right;
        right = left ^ f_function(right, subkey);
        left = temp;
    }

    return (right << 4) | left;
}

// Encrypt using CBC Mode
void cbc_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint16_t key, uint8_t iv, int blocks) {
    uint8_t prev_cipher = iv;

    for (int i = 0; i < blocks; i++) {
        uint8_t xor_block = plaintext[i] ^ prev_cipher;
        ciphertext[i] = sdes_encrypt(xor_block, key);
        prev_cipher = ciphertext[i];
    }
}

// Decrypt using CBC Mode
void cbc_decrypt(uint8_t *ciphertext, uint8_t *plaintext, uint16_t key, uint8_t iv, int blocks) {
    uint8_t prev_cipher = iv;

    for (int i = 0; i < blocks; i++) {
        uint8_t decrypted_block = sdes_decrypt(ciphertext[i], key);
        plaintext[i] = decrypted_block ^ prev_cipher;
        prev_cipher = ciphertext[i];
    }
}

// Convert 16-bit binary string to integer
uint16_t binary_to_int(const char *binary) {
    uint16_t result = 0;
    while (*binary) {
        result = (result << 1) | (*binary - '0');
        binary++;
    }
    return result;
}

// Print binary representation of 8-bit number
void print_binary(uint8_t num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

int main() {
    // Given values
    uint8_t plaintext[2] = {0x01, 0x23}; // 0000 0001 0010 0011
    uint16_t key = 0x1FD; // 01111 11101
    uint8_t iv = 0xAA; // 1010 1010
    uint8_t ciphertext[2];
    uint8_t decrypted[2];

    // Encrypt
    cbc_encrypt(plaintext, ciphertext, key, iv, 2);

    // Print Encrypted Output
    printf("Ciphertext: ");
    for (int i = 0; i < 2; i++) {
        print_binary(ciphertext[i]);
        printf(" ");
    }
    printf("\n");

    // Decrypt
    cbc_decrypt(ciphertext, decrypted, key, iv, 2);

    // Print Decrypted Output
    printf("Decrypted: ");
    for (int i = 0; i < 2; i++) {
        print_binary(decrypted[i]);
        printf(" ");
    }
    printf("\n");

    return 0;
}

