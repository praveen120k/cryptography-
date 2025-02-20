#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE_64 8    // 64-bit block size (8 bytes)
#define BLOCK_SIZE_128 16  // 128-bit block size (16 bytes)

// AES-like encryption function (mock, replace with real AES)
void encrypt_block(uint8_t *input, uint8_t *key, uint8_t *output, int block_size) {
    // Simulated encryption: XOR each byte with the key (for simplicity)
    for (int i = 0; i < block_size; i++) {
        output[i] = input[i] ^ key[i % block_size];
    }
}

// Left shift function for subkey derivation
void left_shift(uint8_t *input, uint8_t *output, int block_size) {
    uint8_t carry = 0;
    for (int i = block_size - 1; i >= 0; i--) {
        output[i] = (input[i] << 1) | carry;
        carry = (input[i] & 0x80) ? 1 : 0;  // Save MSB as carry for next byte
    }
}

// Compute CMAC subkeys
void generate_subkeys(uint8_t *key, int block_size) {
    uint8_t zero_block[block_size];
    uint8_t L[block_size], K1[block_size], K2[block_size];

    memset(zero_block, 0, block_size);  // Initialize all bits to zero

    // Encrypt the all-zero block
    encrypt_block(zero_block, key, L, block_size);

    // Determine the XOR constant (Rb)
    uint8_t Rb = (block_size == BLOCK_SIZE_64) ? 0x1B : 0x87;

    // Compute K1
    left_shift(L, K1, block_size);
    if (L[0] & 0x80) {  // If MSB was 1 before shifting
        K1[block_size - 1] ^= Rb;
    }

    // Compute K2
    left_shift(K1, K2, block_size);
    if (K1[0] & 0x80) {  // If MSB was 1 before shifting
        K2[block_size - 1] ^= Rb;
    }

    // Print results
    printf("Block Size: %d bits\n", block_size * 8);
    printf("L  = "); for (int i = 0; i < block_size; i++) printf("%02X ", L[i]); printf("\n");
    printf("K1 = "); for (int i = 0; i < block_size; i++) printf("%02X ", K1[i]); printf("\n");
    printf("K2 = "); for (int i = 0; i < block_size; i++) printf("%02X ", K2[i]); printf("\n\n");
}

int main() {
    uint8_t key_64[BLOCK_SIZE_64] = {0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F, 0x70, 0x81};
    uint8_t key_128[BLOCK_SIZE_128] = {0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F, 0x70, 0x81,
                                       0x92, 0xA3, 0xB4, 0xC5, 0xD6, 0xE7, 0xF8, 0x09};

    printf("CMAC Subkey Generation:\n");
    generate_subkeys(key_64, BLOCK_SIZE_64);
    generate_subkeys(key_128, BLOCK_SIZE_128);

    return 0;
}

