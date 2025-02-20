#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MATRIX_SIZE 2
#define MOD 26

// Function to calculate modular inverse
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // No modular inverse found
}

// Function to calculate the determinant of a 2x2 matrix
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % MOD;
}

// Function to find the inverse of a 2x2 matrix
void matrixInverse(int matrix[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(matrix);
    int invDet = modInverse(det, MOD);
    
    inverse[0][0] = (matrix[1][1] * invDet) % MOD;
    inverse[0][1] = (-matrix[0][1] * invDet) % MOD;
    inverse[1][0] = (-matrix[1][0] * invDet) % MOD;
    inverse[1][1] = (matrix[0][0] * invDet) % MOD;

    // Adjust negative values
    if (inverse[0][0] < 0) inverse[0][0] += MOD;
    if (inverse[0][1] < 0) inverse[0][1] += MOD;
    if (inverse[1][0] < 0) inverse[1][0] += MOD;
    if (inverse[1][1] < 0) inverse[1][1] += MOD;
}

// Function to multiply two matrices
void matrixMultiply(int matrix1[MATRIX_SIZE][MATRIX_SIZE], int matrix2[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] %= MOD;
        }
    }
}

// Function to convert characters to numerical equivalents (A=0, B=1, ..., Z=25)
void convertToNumbers(char *text, int *numbers) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            numbers[i] = tolower(text[i]) - 'a';
        } else {
            numbers[i] = -1; // Ignore non-alphabet characters
        }
    }
}

// Function to solve the Hill cipher key matrix using two plaintext-ciphertext pairs
void knownPlaintextAttack(char *plaintext1, char *ciphertext1, char *plaintext2, char *ciphertext2) {
    int p1[2], c1[2], p2[2], c2[2];

    // Convert plaintext and ciphertext to numeric values
    convertToNumbers(plaintext1, p1);
    convertToNumbers(ciphertext1, c1);
    convertToNumbers(plaintext2, p2);
    convertToNumbers(ciphertext2, c2);

    // Construct the matrix P and C from the given plaintext-ciphertext pairs
    int P[2][2] = {{p1[0], p1[1]}, {p2[0], p2[1]}};
    int C[2][2] = {{c1[0], c1[1]}, {c2[0], c2[1]}};

    // Find the inverse of P (mod 26)
    int P_inv[2][2];
    matrixInverse(P, P_inv);

    // Calculate the key matrix K = C * P_inv (mod 26)
    int K[2][2];
    matrixMultiply(C, P_inv, K);

    // Output the result (Key matrix)
    printf("The key matrix is:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", K[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Plaintext and ciphertext pairs
    char plaintext1[] = "me";
    char ciphertext1[] = "we";
    char plaintext2[] = "at";
    char ciphertext2[] = "bf";

    // Perform Known Plaintext Attack to break the Hill cipher
    knownPlaintextAttack(plaintext1, ciphertext1, plaintext2, ciphertext2);

    return 0;
}

