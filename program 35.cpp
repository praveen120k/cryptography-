#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// Function to generate a random key stream
void generate_key(int *key, int length) {
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < length; i++) {
        key[i] = rand() % 26; // Random number between 0 and 25
    }
}

// Encrypt function (One-Time Pad Vigenère Cipher)
void encrypt(const char *plaintext, char *ciphertext, int *key) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            int shift = key[i];
            if (isupper(plaintext[i])) {
                ciphertext[i] = 'A' + (plaintext[i] - 'A' + shift) % 26;
            } else {
                ciphertext[i] = 'a' + (plaintext[i] - 'a' + shift) % 26;
            }
        } else {
            ciphertext[i] = plaintext[i]; // Preserve spaces/punctuation
        }
    }
    ciphertext[i] = '\0'; // Null-terminate the string
}

// Decrypt function (One-Time Pad Vigenère Cipher)
void decrypt(const char *ciphertext, char *plaintext, int *key) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int shift = key[i];
            if (isupper(ciphertext[i])) {
                plaintext[i] = 'A' + (ciphertext[i] - 'A' - shift + 26) % 26;
            } else {
                plaintext[i] = 'a' + (ciphertext[i] - 'a' - shift + 26) % 26;
            }
        } else {
            plaintext[i] = ciphertext[i]; // Preserve spaces/punctuation
        }
    }
    plaintext[i] = '\0'; // Null-terminate the string
}

// Main function
int main() {
    char plaintext[100], ciphertext[100], decrypted[100];
    int key[100];

    // Input plaintext
    printf("Enter a message: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    int length = strlen(plaintext);

    // Generate random key
    generate_key(key, length);

    // Encrypt the plaintext
    encrypt(plaintext, ciphertext, key);
    
    // Decrypt back to plaintext
    decrypt(ciphertext, decrypted, key);

    // Display results
    printf("\nGenerated Key: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }

    printf("\nEncrypted Text: %s", ciphertext);
    printf("\nDecrypted Text: %s\n", decrypted);

    return 0;
}

