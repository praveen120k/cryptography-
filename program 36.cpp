#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to find the modular inverse of a mod m (for decryption)
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // No modular inverse exists
}

// Encrypt function for Affine Caesar Cipher
void encrypt(const char *plaintext, char *ciphertext, int a, int b) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            int p = toupper(plaintext[i]) - 'A'; // Convert to 0-25
            int C = (a * p + b) % 26; // Affine transformation
            ciphertext[i] = 'A' + C; // Convert back to letter
        } else {
            ciphertext[i] = plaintext[i]; // Preserve spaces/punctuation
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

// Decrypt function for Affine Caesar Cipher
void decrypt(const char *ciphertext, char *plaintext, int a, int b) {
    int a_inv = modInverse(a, 26); // Compute modular inverse of a
    if (a_inv == -1) {
        printf("Error: No modular inverse exists for a=%d in mod 26. Choose another 'a'.\n", a);
        exit(1);
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int C = toupper(ciphertext[i]) - 'A'; // Convert to 0-25
            int P = (a_inv * (C - b + 26)) % 26; // Reverse transformation
            plaintext[i] = 'A' + P; // Convert back to letter
        } else {
            plaintext[i] = ciphertext[i]; // Preserve spaces/punctuation
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

// Main function
int main() {
    char plaintext[100], ciphertext[100], decrypted[100];
    int a, b;

    // Input plaintext
    printf("Enter a message (uppercase letters only): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    // Input key values
    printf("Enter values for a and b (a should have an inverse mod 26): ");
    scanf("%d %d", &a, &b);

    // Encrypt the plaintext
    encrypt(plaintext, ciphertext, a, b);
    
    // Decrypt back to plaintext
    decrypt(ciphertext, decrypted, a, b);

    // Display results
    printf("\nAffine Caesar Cipher Encryption & Decryption\n");
    printf("Plaintext:  %s\n", plaintext);
    printf("Encrypted:  %s\n", ciphertext);
    printf("Decrypted:  %s\n", decrypted);

    return 0;
}

