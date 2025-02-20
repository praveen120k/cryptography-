#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Mock AES encryption (for simplicity, just a dummy XOR-based transformation)
void aes_encrypt_block(uint8_t *input, uint8_t *output, uint8_t *key) {
    for (int i = 0; i < 16; i++) {
        output[i] = input[i] ^ key[i];  // Simple XOR for illustration
    }
}

// Mock AES decryption (same operation for XOR-based AES mock)
void aes_decrypt_block(uint8_t *input, uint8_t *output, uint8_t *key) {
    for (int i = 0; i < 16; i++) {
        output[i] = input[i] ^ key[i];  // XOR reverses itself
    }
}

// **Padding: Append "1" bit, then "0" bits**
void pad_message(uint8_t *message, int *length) {
    int padding_needed = 16 - (*length % 16);
    message[*length] = 0x80; // Append '1'
    for (int i = 1; i < padding_needed; i++) {
        message[*length + i] = 0x00; // Append '0's
    }
    *length += padding_needed;
}

// **ECB Mode Encryption**
void encrypt_ecb(uint8_t *plaintext, uint8_t *ciphertext, int length, uint8_t *key) {
    for (int i = 0; i < length; i += 16) {
        aes_encrypt_block(&plaintext[i], &ciphertext[i], key);
    }
}

// **CBC Mode Encryption**
void encrypt_cbc(uint8_t *plaintext, uint8_t *ciphertext, int length, uint8_t *key, uint8_t *iv) {
    uint8_t block[16];
    memcpy(block, iv, 16); // Start with IV

    for (int i = 0; i < length; i += 16) {
        for (int j = 0; j < 16; j++) {
            block[j] ^= plaintext[i + j]; // XOR with previous ciphertext
        }
        aes_encrypt_block(block, &ciphertext[i], key);
        memcpy(block, &ciphertext[i], 16); // Update for next block
    }
}

// **CFB Mode Encryption**
void encrypt_cfb(uint8_t *plaintext, uint8_t *ciphertext, int length, uint8_t *key, uint8_t *iv) {
    uint8_t block[16];
    memcpy(block, iv, 16); // Start with IV

    for (int i = 0; i < length; i += 16) {
        aes_encrypt_block(block, block, key); // Encrypt IV or last ciphertext
        for (int j = 0; j < 16; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ block[j]; // XOR with keystream
        }
        memcpy(block, &ciphertext[i], 16); // Update IV with new ciphertext
    }
}

// **Main Function**
int main() {
    uint8_t plaintext[64] = "Hello, this is a test message!";
    int length = strlen((char *)plaintext);

    // Padding
    pad_message(plaintext, &length);

    // AES 128-bit key (dummy key for testing)
    uint8_t key[16] = { 0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F, 0x7A, 0x8B,
                        0x9C, 0xAD, 0xBE, 0xCF, 0xD0, 0xE1, 0xF2, 0x03 };

    // Initialization Vector (IV)
    uint8_t iv[16] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                       0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };

    uint8_t ciphertext[64], decrypted[64];

    // Encrypt in ECB mode
    encrypt_ecb(plaintext, ciphertext, length, key);
    printf("ECB Ciphertext: ");
    for (int i = 0; i < length; i++) printf("%02X ", ciphertext[i]);
    printf("\n");

    // Encrypt in CBC mode
    encrypt_cbc(plaintext, ciphertext, length, key, iv);
    printf("CBC Ciphertext: ");
    for (int i = 0; i < length; i++) printf("%02X ", ciphertext[i]);
    printf("\n");

    // Encrypt in CFB mode
    encrypt_cfb(plaintext, ciphertext, length, key, iv);
    printf("CFB Ciphertext: ");
    for (int i = 0; i < length; i++) printf("%02X ", ciphertext[i]);
    printf("\n");

    return 0;
}

