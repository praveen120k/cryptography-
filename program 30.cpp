#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Block size (128 bits / 16 bytes for AES)
#define BLOCK_SIZE 16 

// Simulated encryption function (normally AES, but simplified XOR here)
void encrypt_block(uint8_t *block, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block[i] ^ key[i]; // Simple XOR as a mock cipher
    }
}

// CBC-MAC computation
void CBC_MAC(uint8_t *message, int message_len, uint8_t *key, uint8_t *mac) {
    uint8_t IV[BLOCK_SIZE] = {0};  // Initialization vector (zero)
    uint8_t temp[BLOCK_SIZE];

    memcpy(temp, IV, BLOCK_SIZE); // Start with IV

    for (int i = 0; i < message_len; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            temp[j] ^= message[i + j]; // XOR with message block
        }
        encrypt_block(temp, key, temp); // Encrypt block
    }

    memcpy(mac, temp, BLOCK_SIZE); // MAC is the final encrypted block
}

// XOR two blocks
void xor_blocks(uint8_t *a, uint8_t *b, uint8_t *out) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        out[i] = a[i] ^ b[i];
    }
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F, 0x70, 0x81,
                               0x92, 0xA3, 0xB4, 0xC5, 0xD6, 0xE7, 0xF8, 0x09};  // Secret key
    uint8_t message[BLOCK_SIZE] = {0x6A, 0x7B, 0x8C, 0x9D, 0xAE, 0xBF, 0xC0, 0xD1,
                                   0xE2, 0xF3, 0x04, 0x15, 0x26, 0x37, 0x48, 0x59};  // Message X
    uint8_t mac[BLOCK_SIZE]; // Store CBC-MAC
    uint8_t forged_block[BLOCK_SIZE];
    uint8_t forged_mac[BLOCK_SIZE];

    // Compute CBC-MAC of X
    CBC_MAC(message, BLOCK_SIZE, key, mac);

    printf("Original CBC-MAC: ");
    for (int i = 0; i < BLOCK_SIZE; i++) printf("%02X ", mac[i]);
    printf("\n");

    // Adversary constructs (X ? T)
    xor_blocks(message, mac, forged_block);

    // Compute CBC-MAC of forged two-block message X || (X ? T)
    uint8_t forged_message[2 * BLOCK_SIZE];
    memcpy(forged_message, message, BLOCK_SIZE);
    memcpy(forged_message + BLOCK_SIZE, forged_block, BLOCK_SIZE);

    CBC_MAC(forged_message, 2 * BLOCK_SIZE, key, forged_mac);

    printf("Forged CBC-MAC:   ");
    for (int i = 0; i < BLOCK_SIZE; i++) printf("%02X ", forged_mac[i]);
    printf("\n");

    // Check if forged MAC matches original MAC
    if (memcmp(mac, forged_mac, BLOCK_SIZE) == 0) {
        printf("Attack successful: Adversary computed valid CBC-MAC without the key!\n");
    } else {
        printf("Attack failed: CBC-MAC mismatch (shouldn't happen!)\n");
    }

    return 0;
}

