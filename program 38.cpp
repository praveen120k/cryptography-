#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 2  // Using 2x2 Hill Cipher

// Function to compute the modular inverse of a number (mod 26)
int modInverse(int num, int mod) {
    num = num % mod;
    for (int x = 1; x < mod; x++) {
        if ((num * x) % mod == 1)
            return x;
    }
    return -1;  // No modular inverse exists
}

// Function to compute determinant of a 2x2 matrix mod 26
int determinant(int matrix[2][2]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
}

// Function to compute modular inverse of a matrix
void inverseMatrix(int matrix[2][2], int invMatrix[2][2]) {
    int det = determinant(matrix);
    if (det < 0) det += 26;

    int detInv = modInverse(det, 26);
    if (detInv == -1) {
        printf("Matrix is not invertible.\n");
        exit(1);
    }

    // Adjugate and multiply by determinant inverse
    invMatrix[0][0] = (matrix[1][1] * detInv) % 26;
    invMatrix[0][1] = (-matrix[0][1] * detInv) % 26;
    invMatrix[1][0] = (-matrix[1][0] * detInv) % 26;
    invMatrix[1][1] = (matrix[0][0] * detInv) % 26;

    // Ensure positive mod 26 values
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (invMatrix[i][j] < 0)
                invMatrix[i][j] += 26;
}

// Function to multiply matrices mod 26
void multiplyMatrix(int matrix1[2][2], int matrix2[2][2], int result[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] %= 26;
        }
    }
}

// Function to compute encryption key from known plaintext-ciphertext pairs
void computeKey(int plaintext[2][2], int ciphertext[2][2], int key[2][2]) {
    int invPlaintext[2][2];
    inverseMatrix(plaintext, invPlaintext);
    multiplyMatrix(ciphertext, invPlaintext, key);
}

// Function to decrypt a ciphertext using a given key
void decrypt(int key[2][2], int ciphertext[2], int plaintext[2]) {
    int invKey[2][2];
    inverseMatrix(key, invKey);

    for (int i = 0; i < 2; i++) {
        plaintext[i] = (invKey[i][0] * ciphertext[0] + invKey[i][1] * ciphertext[1]) % 26;
        if (plaintext[i] < 0)
            plaintext[i] += 26;
    }
}

// Main function
int main() {
    // Known plaintext-ciphertext pairs
    int plaintext[2][2] = {{7, 8}, {19, 20}};  // "HI" and "ST"
    int ciphertext[2][2] = {{3, 10}, {17, 24}}; // Corresponding cipher text

    int key[2][2];
    computeKey(plaintext, ciphertext, key);

    // Display the computed key
    printf("Recovered Key Matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            printf("%d ", key[i][j]);
        printf("\n");
    }

    // Example: Decrypt a ciphertext using the recovered key
    int cipherTextBlock[2] = {3, 10}; // Assume "CI"
    int decrypted[2];

    decrypt(key, cipherTextBlock, decrypted);

    printf("Decrypted Text: %c%c\n", decrypted[0] + 'A', decrypted[1] + 'A');

    return 0;
}

