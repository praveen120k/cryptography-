#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt text using Vigenère cipher
void encrypt(char plaintext[], char key[]) {
    int textLen = strlen(plaintext);
    int keyLen = strlen(key);
    char ciphertext[textLen];

    for (int i = 0, j = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) { // Encrypt only alphabetic characters
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            char keyBase = isupper(key[j % keyLen]) ? 'A' : 'a';
            int shift = (key[j % keyLen] - keyBase) % 26; // Calculate shift from key
            ciphertext[i] = ((plaintext[i] - base + shift) % 26) + base;
            j++; // Move to next key character
        } else {
            ciphertext[i] = plaintext[i]; // Keep non-alphabet characters unchanged
        }
    }
    ciphertext[textLen] = '\0';
    printf("Encrypted Text: %s\n", ciphertext);
}

// Function to decrypt text using Vigenère cipher
void decrypt(char ciphertext[], char key[]) {
    int textLen = strlen(ciphertext);
    int keyLen = strlen(key);
    char plaintext[textLen];

    for (int i = 0, j = 0; i < textLen; i++) {
        if (isalpha(ciphertext[i])) { // Decrypt only alphabetic characters
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            char keyBase = isupper(key[j % keyLen]) ? 'A' : 'a';
            int shift = (key[j % keyLen] - keyBase) % 26; // Calculate shift from key
            plaintext[i] = ((ciphertext[i] - base - shift + 26) % 26) + base;
            j++; // Move to next key character
        } else {
            plaintext[i] = ciphertext[i]; // Keep non-alphabet characters unchanged
        }
    }
    plaintext[textLen] = '\0';
    printf("Decrypted Text: %s\n", plaintext);
}

int main() {
    char plaintext[100], key[100];

    printf("Enter plaintext: ");
    scanf(" %[^\n]", plaintext);

    printf("Enter keyword: ");
    scanf("%s", key);

    // Convert key to uppercase for consistency
    for (int i = 0; key[i]; i++)
        key[i] = toupper(key[i]);

    encrypt(plaintext, key);

    // To demonstrate decryption, we take encrypted text as input
    char ciphertext[100];
    printf("Enter ciphertext for decryption: ");
    scanf(" %[^\n]", ciphertext);

    decrypt(ciphertext, key);

    return 0;
}

