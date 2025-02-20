#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char keyMatrix[SIZE][SIZE];

// Function to remove duplicate characters from the key
void prepareKeyMatrix(char key[]) {
    int map[26] = {0}; // To track letter usage
    int i, j, k = 0;
    
    // Convert key to uppercase and fill matrix
    for (i = 0; key[i]; i++) {
        if (key[i] == 'J') key[i] = 'I'; // Replace 'J' with 'I'
        if (!isalpha(key[i])) continue; // Ignore non-alphabet characters
        key[i] = toupper(key[i]);

        if (!map[key[i] - 'A']) {
            keyMatrix[k / SIZE][k % SIZE] = key[i];
            map[key[i] - 'A'] = 1;
            k++;
        }
    }

    // Fill remaining matrix with unused letters
    for (i = 0; i < 26; i++) {
        if (i + 'A' == 'J') continue; // Skip 'J' as 'I' is used
        if (!map[i]) {
            keyMatrix[k / SIZE][k % SIZE] = i + 'A';
            k++;
        }
    }
}

// Function to find positions of two letters in the matrix
void findPosition(char letter, int *row, int *col) {
    if (letter == 'J') letter = 'I'; // Treat 'J' as 'I'
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt plaintext using Playfair cipher
void encrypt(char plaintext[]) {
    char processedText[100] = {0};
    int len = 0;

    // Process the plaintext: Remove spaces, convert to uppercase, insert 'X' for duplicate letters in pairs
    for (int i = 0; plaintext[i]; i++) {
        if (!isalpha(plaintext[i])) continue;
        processedText[len++] = toupper(plaintext[i]);
    }

    // Adjust for duplicate letters and odd-length plaintext
    for (int i = 0; i < len; i += 2) {
        if (processedText[i] == processedText[i + 1]) {
            memmove(processedText + i + 2, processedText + i + 1, len - i);
            processedText[i + 1] = 'X'; // Insert 'X' between duplicate letters
            len++;
        }
    }
    if (len % 2 != 0) processedText[len++] = 'X'; // Ensure even length

    // Encrypt the digraphs
    printf("Encrypted Text: ");
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        findPosition(processedText[i], &r1, &c1);
        findPosition(processedText[i + 1], &r2, &c2);

        if (r1 == r2) { // Same row: shift right
            printf("%c%c", keyMatrix[r1][(c1 + 1) % SIZE], keyMatrix[r2][(c2 + 1) % SIZE]);
        } else if (c1 == c2) { // Same column: shift down
            printf("%c%c", keyMatrix[(r1 + 1) % SIZE][c1], keyMatrix[(r2 + 1) % SIZE][c2]);
        } else { // Rectangle swap
            printf("%c%c", keyMatrix[r1][c2], keyMatrix[r2][c1]);
        }
    }
    printf("\n");
}

// Function to display the key matrix
void displayMatrix() {
    printf("Playfair Key Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", keyMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char key[100], plaintext[100];

    printf("Enter the keyword (no spaces): ");
    scanf("%s", key);
    prepareKeyMatrix(key);
    displayMatrix();

    printf("Enter plaintext: ");
    scanf(" %[^\n]", plaintext);

    encrypt(plaintext);

    return 0;
}

