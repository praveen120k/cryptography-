#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define BLOCK_SIZE 16  // AES block size (128 bits)

// Function to generate a random IV
void generate_iv(unsigned char *iv) {
    if (!RAND_bytes(iv, BLOCK_SIZE)) {
        fprintf(stderr, "Error generating IV\n");
        exit(1);
    }
}

// Function to apply padding (1-bit followed by 0s)
void pad_data(unsigned char *data, int *len) {
    int padding_len = BLOCK_SIZE - (*len % BLOCK_SIZE);
    data[*len] = 0x80; // 1-bit padding
    for (int i = *len + 1; i < *len + padding_len; i++) {
        data[i] = 0x00; // Fill remaining with zero bits
    }
    *len += padding_len;
}

// ECB Mode Encryption
void encrypt_ecb(const unsigned char *plaintext, int len, AES_KEY *key, unsigned char *ciphertext) {
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        AES_encrypt(plaintext + i, ciphertext + i, key);
    }
}

// CBC Mode Encryption
void encrypt_cbc(const unsigned char *plaintext, int len, AES_KEY *key, unsigned char *ciphertext, unsigned char *iv) {
    unsigned char prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);

    for (int i = 0; i < len; i += BLOCK_SIZE) {
        unsigned char temp[BLOCK_SIZE];
        for (int j = 0; j < BLOCK_SIZE; j++) {
            temp[j] = plaintext[i + j] ^ prev_block[j];
        }
        AES_encrypt(temp, ciphertext + i, key);
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}

// CFB Mode Encryption
void encrypt_cfb(const unsigned char *plaintext, int len, AES_KEY *key, unsigned char *ciphertext, unsigned char *iv) {
    unsigned char feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);

    for (int i = 0; i < len; i++) {
        unsigned char encrypted_feedback[BLOCK_SIZE];
        AES_encrypt(feedback, encrypted_feedback, key);
        ciphertext[i] = plaintext[i] ^ encrypted_feedback[i % BLOCK_SIZE];
        feedback[i % BLOCK_SIZE] = ciphertext[i]; // Update feedback
    }
}

int main() {
    // AES Key (16 bytes for AES-128)
    unsigned char key[BLOCK_SIZE] = "1234567890123456"; 

    // Generate IV for CBC & CFB
    unsigned char iv[BLOCK_SIZE];
    generate_iv(iv);

    // Plaintext message
    unsigned char plaintext[64] = "Confidential message to be encrypted.";
    int len = strlen((char *)plaintext);

    // Apply padding
    pad_data(plaintext, &len);

    // Ciphertext buffers
    unsigned char ciphertext_ecb[64] = {0};
    unsigned char ciphertext_cbc[64] = {0};
    unsigned char ciphertext_cfb[64] = {0};

    // Initialize AES Key
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    // Encrypt data
    encrypt_ecb(plaintext, len, &aes_key, ciphertext_ecb);
    encrypt_cbc(plaintext, len, &aes_key, ciphertext_cbc, iv);
    encrypt_cfb(plaintext, len, &aes_key, ciphertext_cfb, iv);

    // Print results
    printf("ECB Encrypted Data: ");
    for (int i = 0; i < len; i++) printf("%02x ", ciphertext_ecb[i]);
    printf("\n");

    printf("CBC Encrypted Data: ");
    for (int i = 0; i < len; i++) printf("%02x ", ciphertext_cbc[i]);
    printf("\n");

    printf("CFB Encrypted Data: ");
    for (int i = 0; i < len; i++) printf("%02x ", ciphertext_cfb[i]);
    printf("\n");

    return 0;
}

