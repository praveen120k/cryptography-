#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>  // Include this header for strlen

// Function to generate a random key stream of length n
void generateKeyStream(int *keyStream, int n) {
    for (int i = 0; i < n; i++) {
        keyStream[i] = rand() % 26;  // Random number between 0 and 25 (A-Z)
    }
}

// Function to encrypt the plaintext using the One-Time Pad Vigenère Cipher
void encrypt(char *plaintext, int *keyStream, char *ciphertext) {
    int i = 0;
    while (plaintext[i] != '\0') {
        if (isalpha(plaintext[i])) {
            int shift = keyStream[i];  // Get the corresponding key value for the current letter
            if (isupper(plaintext[i])) {
                ciphertext[i] = (plaintext[i] - 'A' + shift) % 26 + 'A';
            } else if (islower(plaintext[i])) {
                ciphertext[i] = (plaintext[i] - 'a' + shift) % 26 + 'a';
            }
        } else {
            ciphertext[i] = plaintext[i];  // Non-alphabet characters are not encrypted
        }
        i++;
    }
    ciphertext[i] = '\0';  // Null-terminate the ciphertext
}

// Function to decrypt the ciphertext using the One-Time Pad Vigenère Cipher
void decrypt(char *ciphertext, int *keyStream, char *plaintext) {
    int i = 0;
    while (ciphertext[i] != '\0') {
        if (isalpha(ciphertext[i])) {
            int shift = keyStream[i];  // Get the corresponding key value for the current letter
            if (isupper(ciphertext[i])) {
                plaintext[i] = (ciphertext[i] - 'A' - shift + 26) % 26 + 'A';
            } else if (islower(ciphertext[i])) {
                plaintext[i] = (ciphertext[i] - 'a' - shift + 26) % 26 + 'a';
            }
        } else {
            plaintext[i] = ciphertext[i];  // Non-alphabet characters are not decrypted
        }
        i++;
    }
    plaintext[i] = '\0';  // Null-terminate the plaintext
}

int main() {
    srand(time(NULL));  // Seed the random number generator

    char plaintext[] = "Meet me at the park at 3 PM.";
    int n = strlen(plaintext);  // Get the length of the plaintext
    int keyStream[n];

    // Generate the random key stream
    generateKeyStream(keyStream, n);

    char ciphertext[n + 1];  // Array to store the encrypted text
    char decryptedText[n + 1];  // Array to store the decrypted text

    // Encrypt the plaintext
    encrypt(plaintext, keyStream, ciphertext);
    printf("Encrypted Text: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, keyStream, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}

