#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char keyMatrix[SIZE][SIZE];

// Function to remove duplicate characters from the keyword
void generateKeyMatrix(char key[]) {
    int seen[26] = {0};
    int row = 0, col = 0;
    
    // Remove duplicate letters and insert key into the matrix
    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I';  // J is treated as I in Playfair
        
        if (!seen[ch - 'A']) {
            keyMatrix[row][col] = ch;
            seen[ch - 'A'] = 1;
            col++;
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }

    // Fill remaining letters (excluding 'J')
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; // Skip J
        if (!seen[ch - 'A']) {
            keyMatrix[row][col] = ch;
            seen[ch - 'A'] = 1;
            col++;
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }
}

// Function to find the position of a letter in the key matrix
void findPosition(char letter, int *row, int *col) {
    if (letter == 'J') letter = 'I';  // Treat J as I
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (keyMatrix[r][c] == letter) {
                *row = r;
                *col = c;
                return;
            }
        }
    }
}

// Function to decrypt Playfair digraphs
void decryptPlayfair(char text[]) {
    int len = strlen(text);
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        findPosition(text[i], &r1, &c1);
        findPosition(text[i + 1], &r2, &c2);

        // Same row: Shift left
        if (r1 == r2) {
            c1 = (c1 - 1 + SIZE) % SIZE;
            c2 = (c2 - 1 + SIZE) % SIZE;
        }
        // Same column: Shift up
        else if (c1 == c2) {
            r1 = (r1 - 1 + SIZE) % SIZE;
            r2 = (r2 - 1 + SIZE) % SIZE;
        }
        // Rectangle swap
        else {
            int temp = c1;
            c1 = c2;
            c2 = temp;
        }

        // Replace with decrypted letters
        text[i] = keyMatrix[r1][c1];
        text[i + 1] = keyMatrix[r2][c2];
    }
}

int main() {
    char keyword[50] = "MONARCHY";  // Assume MONARCHY as the key
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";

    // Generate Playfair key matrix
    generateKeyMatrix(keyword);

    // Display the Playfair key matrix
    printf("Playfair Key Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", keyMatrix[i][j]);
        }
        printf("\n");
    }

    // Decrypt the Playfair ciphertext
    decryptPlayfair(ciphertext);

    // Output the decrypted text
    printf("\nDecrypted Text: %s\n", ciphertext);

    return 0;
}

