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

// Generate subkeys for S-DES
uint8_t generate_subkeys(uint16_t key, int round) {
    return (key >> (5 - round)) & 0x1F; // Extract 5-bit subkey
}

// S-DES Feistel Function
uint8_t f_function(uint8_t right, uint8_t subkey) {
    right ^= subkey; // XOR with subkey
    uint8_t row1 = (right & 0xC) >> 2;
    uint8_t col1 = (right & 0x3);
    uint8_t row2 = (right & 0x30) >> 4;
    uint8_t col2 = (right & 0x0C) >> 2;
    return (SBOX1[row1][col1] << 2) | SBOX2[row2][col2];
}

// S-DES Encryption (Feistel Structure)
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

// Encrypt using Counter (CTR) Mode
void ctr_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint16_t key, uint8_t counter, int blocks) {
    for (int i = 0; i < blocks; i++) {
        uint8_t keystream = sdes_encrypt(counter, key); // Encrypt counter
        ciphertext[i] = plaintext[i] ^ keystream; // XOR with plaintext
        counter++; // Increment counter
    }
}

// Decrypt using Counter (CTR) Mode (Same as encryption)
void ctr_decrypt(uint8_t *ciphertext, uint8_t *plaintext, uint16_t key, uint8_t counter, int blocks) {
    for (int i = 0; i < blocks; i++) {
        uint8_t keystream = sdes_encrypt(counter, key); // Encrypt counter
        plaintext[i] = ciphertext[i] ^ keystream; // XOR with ciphertext
        counter++; // Increment counter
    }
}

// Print binary representation of an 8-bit number
void print_binary(uint8_t num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

int main() {
    // Given values
    uint8_t plaintext[3] = {0x01, 0x02, 0x04}; // 0000 0001 0000 0010 0000 0100
    uint16_t key = 0x1FD; // 01111 11101
    uint8_t counter = 0x00; // 0000 0000
    uint8_t ciphertext[3];
    uint8_t decrypted[3];

    // Encrypt
    ctr_encrypt(plaintext, ciphertext, key, counter, 3);

    // Print Encrypted Output
    printf("Ciphertext: ");
    for (int i = 0; i < 3; i++) {
        print_binary(ciphertext[i]);
        printf(" ");
    }
    printf("\n");

    // Decrypt
    ctr_decrypt(ciphertext, decrypted, key, counter, 3);

    // Print Decrypted Output
    printf("Decrypted: ");
    for (int i = 0; i < 3; i++) {
        print_binary(decrypted[i]);
        printf(" ");
    }
    printf("\n");

    return 0;
}

