#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BLOCK_SIZE 16  // AES block size (128 bits)

void xor_encrypt(const unsigned char *input, unsigned char *output, const unsigned char *key, int len) {
    for (int i = 0; i < len; i++) {
        output[i] = input[i] ^ key[i % BLOCK_SIZE];
    }
}

void encrypt_ecb(const unsigned char *plaintext, int len, const unsigned char *key, unsigned char *ciphertext) {
    xor_encrypt(plaintext, ciphertext, key, len);
}

void generate_iv(unsigned char *iv) {
    srand(time(NULL));
    for (int i = 0; i < BLOCK_SIZE; i++) {
        iv[i] = rand() % 256;
    }
}

int main() {
    unsigned char key[BLOCK_SIZE];
    memcpy(key, "1234567890123456", BLOCK_SIZE);  // ? Correct way

    unsigned char plaintext[64] = "Hello, AES encryption!";  
    int len = strlen((char *)plaintext);

    unsigned char ciphertext[64] = {0};

    encrypt_ecb(plaintext, len, key, ciphertext);

    printf("Encrypted Data (ECB): ");
    for (int i = 0; i < len; i++) printf("%02x ", ciphertext[i]);
    printf("\n");

    return 0;
}

