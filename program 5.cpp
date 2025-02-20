#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to compute GCD
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find modular inverse of a mod 26
int modInverse(int a) {
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1)
            return i;
    }
    return -1; // No modular inverse exists
}

// Function to encrypt plaintext using Affine Caesar Cipher
void encrypt(char plaintext[], int a, int b) {
    if (gcd(a, 26) != 1) {
        printf("Invalid 'a' value! Must be coprime to 26.\n");
        return;
    }

    printf("Encrypted Text: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int p = plaintext[i] - base;  // Convert letter to index (0–25)
            int c = (a * p + b) % 26;     // Apply affine cipher
            printf("%c", c + base);       // Convert index back to letter
        } else {
            printf("%c", plaintext[i]); // Keep spaces and symbols unchanged
        }
    }
    printf("\n");
}

// Function to decrypt ciphertext using Affine Caesar Cipher
void decrypt(char ciphertext[], int a, int b) {
    int a_inv = modInverse(a);
    if (a_inv == -1) {
        printf("Invalid 'a' value! No modular inverse exists.\n");
        return;
    }

    printf("Decrypted Text: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int c = ciphertext[i] - base;  // Convert letter to index (0–25)
            int p = (a_inv * (c - b + 26)) % 26; // Apply inverse affine cipher
            printf("%c", p + base);        // Convert index back to letter
        } else {
            printf("%c", ciphertext[i]); // Keep spaces and symbols unchanged
        }
    }
    printf("\n");
}

int main() {
    char plaintext[100], ciphertext[100];
    int a, b;

    // Get user input
    printf("Enter plaintext: ");
    scanf(" %[^\n]", plaintext);

    printf("Enter values for a and b: ");
    scanf("%d %d", &a, &b);

    // Encrypt the plaintext
    encrypt(plaintext, a, b);

    // Get ciphertext for decryption
    printf("Enter ciphertext for decryption: ");
    scanf(" %[^\n]", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, a, b);

    return 0;
}

