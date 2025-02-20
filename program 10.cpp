#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char keyMatrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'J'},
    {'K', 'U', 'N', 'O', 'P'},
    {'Q', 'Z', 'V', 'W', 'X'},
    {'Y', 'E', 'L', 'A', 'R'},
    {'G', 'D', 'S', 'T', 'B'}
};

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

// Function to prepare the message (split into digraphs)
void prepareMessage(char message[], char prepared[]) {
    int k = 0;
    for (int i = 0; message[i] != '\0'; i++) {
        if (isalpha(message[i])) {
            prepared[k++] = toupper(message[i]);
        }
    }

    // Add a filler letter if the message has odd length
    if (k % 2 != 0) {
        prepared[k++] = 'X';
    }
    prepared[k] = '\0';
}

// Function to encrypt Playfair digraphs
void encryptPlayfair(char text[], char encrypted[]) {
    int len = strlen(text);
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        findPosition(text[i], &r1, &c1);
        findPosition(text[i + 1], &r2, &c2);

        // Same row: Shift right
        if (r1 == r2) {
            c1 = (c1 + 1) % SIZE;
            c2 = (c2 + 1) % SIZE;
        }
        // Same column: Shift down
        else if (c1 == c2) {
            r1 = (r1 + 1) % SIZE;
            r2 = (r2 + 1) % SIZE;
        }
        // Rectangle swap
        else {
            int temp = c1;
            c1 = c2;
            c2 = temp;
        }

        // Replace with encrypted letters
        encrypted[i] = keyMatrix[r1][c1];
        encrypted[i + 1] = keyMatrix[r2][c2];
    }
}

// Function to encrypt a given message
void encryptMessage(char message[]) {
    char prepared[100], encrypted[100];

    // Prepare the message (remove non-alphabet characters and handle odd length)
    prepareMessage(message, prepared);

    // Encrypt the message
    encryptPlayfair(prepared, encrypted);

    // Display the encrypted message
    printf("Encrypted Message: ");
    for (int i = 0; encrypted[i] != '\0'; i++) {
        printf("%c", encrypted[i]);
    }
    printf("\n");
}

int main() {
    char message[] = "Must see you over Cadogan West. Coming at once.";

    printf("Original Message: %s\n", message);
    encryptMessage(message);

    return 0;
}

