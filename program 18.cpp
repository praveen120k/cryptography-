#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define KEY_SIZE 56  // DES key size in bits
#define SUBKEY_SIZE 48  // Size of each subkey in bits (48 bits for DES)
#define NUM_ROUNDS 16  // Number of rounds in DES

// Function to perform circular left shift on a bit string
uint32_t leftShift(uint32_t input, int shifts) {
    return ((input << shifts) | (input >> (28 - shifts))) & 0xFFFFFFF;
}

// Function to generate subkeys
void generateSubkeys(uint64_t key, uint64_t subkeys[NUM_ROUNDS]) {
    // Split the 56-bit key into two 28-bit halves
    uint32_t left = (key >> 28) & 0xFFFFFFF;  // Left 28 bits
    uint32_t right = key & 0xFFFFFFF;         // Right 28 bits

    // Perform key schedule: generate 16 subkeys
    for (int i = 0; i < NUM_ROUNDS; i++) {
        // Perform left shifts
        left = leftShift(left, 1);  // 1-bit left shift per round (could be different in DES)
        right = leftShift(right, 1);

        // Generate the 48-bit subkey
        uint64_t subkey = 0;

        // First 24 bits from left 28 bits
        subkey = (subkey | ((left >> 4) & 0xFFFFFF));  // First 24 bits from left part
        
        // Second 24 bits from right 28 bits
        subkey = (subkey | ((right >> 4) & 0xFFFFFF) << 24);  // Next 24 bits from right part

        subkeys[i] = subkey;
    }
}

// Function to print a 48-bit subkey
void printSubkey(uint64_t subkey) {
    for (int i = 47; i >= 0; i--) {
        printf("%d", (subkey >> i) & 1);
    }
    printf("\n");
}

int main() {
    uint64_t key = 0x133457799BBCDFF1;  // Example 56-bit key (8 bytes)
    uint64_t subkeys[NUM_ROUNDS];  // Array to store 16 subkeys

    printf("Initial Key (56-bits):\n");
    printf("0x%016llX\n", key);

    // Generate subkeys
    generateSubkeys(key, subkeys);

    // Print the 16 subkeys
    printf("\nGenerated Subkeys (48-bits each):\n");
    for (int i = 0; i < NUM_ROUNDS; i++) {
        printf("Subkey %d: ", i + 1);
        printSubkey(subkeys[i]);
    }

    return 0;
}

