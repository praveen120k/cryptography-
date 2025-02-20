#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 2
#define MOD 26

// Function to multiply the key matrix with plaintext vector
void matrixMultiply(int matrix[MATRIX_SIZE][MATRIX_SIZE], int plaintext[MATRIX_SIZE], int result[MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        result[i] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i] += matrix[i][j] * plaintext[j];
        }
        result[i] %= MOD; // take modulo 26
    }
}

// Function to encrypt the message
void encryptHillCipher(char *plaintext, int key[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext) {
    int len = strlen(plaintext);
    int i = 0;
    while (i < len) {
        int plaintextPair[MATRIX_SIZE] = {0};

        // Convert two characters to their numerical equivalents
        for (int j = 0; j < MATRIX_SIZE && i < len; j++, i++) {
            if (isalpha(plaintext[i])) {
                plaintextPair[j] = tolower(plaintext[i]) - 'a';
            } else {
                plaintextPair[j] = 0;
            }
        }

        // Encrypt the plaintext pair
        int encryptedPair[MATRIX_SIZE];
        matrixMultiply(key, plaintextPair, encryptedPair);

        // Convert the result to characters and append to ciphertext
        for (int j = 0; j < MATRIX_SIZE; j++) {
            ciphertext[i - MATRIX_SIZE + j] = encryptedPair[j] + 'a';
        }
    }
    ciphertext[len] = '\0';
}

// Function to decrypt the ciphertext
void decryptHillCipher(char *ciphertext, int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext) {
    // Calculate the inverse of the key matrix
    int determinant = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % MOD;
    int inverseDeterminant = -1;
    for (int i = 0; i < MOD; i++) {
        if ((determinant * i) % MOD == 1) {
            inverseDeterminant = i;
            break;
        }
    }

    // Calculate the inverse key matrix
    int inverseKey[MATRIX_SIZE][MATRIX_SIZE] = {
        {(key[1][1] * inverseDeterminant) % MOD, (-key[0][1] * inverseDeterminant) % MOD},
        {(-key[1][0] * inverseDeterminant) % MOD, (key[0][0] * inverseDeterminant) % MOD}
    };

    // Ensure positive values by adding MOD and taking modulo
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (inverseKey[i][j] < 0) {
                inverseKey[i][j] += MOD;
            }
        }
    }

    int len = strlen(ciphertext);
    int i = 0;
    while (i < len) {
        int ciphertextPair[MATRIX_SIZE] = {0};

        // Convert two characters to their numerical equivalents
        for (int j = 0; j < MATRIX_SIZE && i < len; j++, i++) {
            if (isalpha(ciphertext[i])) {
                ciphertextPair[j] = tolower(ciphertext[i]) - 'a';
            }
        }

        // Decrypt the ciphertext pair
        int decryptedPair[MATRIX_SIZE];
        matrixMultiply(inverseKey, ciphertextPair, decryptedPair);

        // Convert the result to characters and append to plaintext
        for (int j = 0; j < MATRIX_SIZE; j++) {
            plaintext[i - MATRIX_SIZE + j] = decryptedPair[j] + 'a';
        }
    }
    plaintext[len] = '\0';
}

int main() {
    char plaintext[] = "meet me at the usual place at ten rather than eight oclock";
    char ciphertext[100];
    char decryptedText[100];

    // Hill cipher key
    int key[MATRIX_SIZE][MATRIX_SIZE] = {{9, 4}, {5, 7}};

    // Encrypt the message
    encryptHillCipher(plaintext, key, ciphertext);
    printf("Encrypted Text: %s\n", ciphertext);

    // Decrypt the message
    decryptHillCipher(ciphertext, key, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}

