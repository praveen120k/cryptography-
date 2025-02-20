#include <stdio.h>
#include <string.h>

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

// Function to decrypt using Affine cipher
void decrypt(char ciphertext[], int a, int b) {
    int a_inv = modInverse(a);
    if (a_inv == -1) {
        printf("Invalid 'a' value! No modular inverse exists.\n");
        return;
    }

    printf("Decrypted Text: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            int C = ciphertext[i] - 'A';
            int P = (a_inv * (C - b + 26)) % 26; // Apply inverse transformation
            printf("%c", P + 'A');
        } else {
            printf("%c", ciphertext[i]); // Keep spaces and punctuation unchanged
        }
    }
    printf("\n");
}

int main() {
    char ciphertext[100];
    int a = 15, b;

    // Solve for `b` using B ? E mapping
    b = (1 - (a * 4) % 26 + 26) % 26;

    printf("Computed values: a = %d, b = %d\n", a, b);

    // Get ciphertext input
    printf("Enter ciphertext: ");
    scanf(" %[^\n]", ciphertext);

    // Decrypt ciphertext
    decrypt(ciphertext, a, b);

    return 0;
}

