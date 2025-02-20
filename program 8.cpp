#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to remove duplicate characters from a keyword
void removeDuplicates(char str[], char result[]) {
    int seen[256] = {0};  // To track seen characters
    int j = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (!seen[(unsigned char)str[i]]) {
            seen[(unsigned char)str[i]] = 1;
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
}

// Function to generate the cipher mapping
void generateCipher(char keyword[], char cipherMap[]) {
    char uniqueKeyword[ALPHABET_SIZE] = {0};
    removeDuplicates(keyword, uniqueKeyword);

    int index = 0;
    int used[256] = {0};  // Track used characters
    for (int i = 0; uniqueKeyword[i] != '\0'; i++) {
        cipherMap[index++] = uniqueKeyword[i];
        used[(unsigned char)uniqueKeyword[i]] = 1;
    }

    // Fill remaining letters
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[(unsigned char)c]) {
            cipherMap[index++] = c;
        }
    }
    cipherMap[index] = '\0';
}

// Function to encrypt text
void encryptText(char text[], char cipherMap[], char encrypted[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            encrypted[i] = cipherMap[text[i] - base];
        } else {
            encrypted[i] = text[i];  // Keep spaces and punctuation unchanged
        }
    }
    encrypted[strlen(text)] = '\0';
}

// Function to decrypt text
void decryptText(char text[], char cipherMap[], char decrypted[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            // Find the index of the encrypted character in cipherMap
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                if (cipherMap[j] == text[i]) {
                    decrypted[i] = 'A' + j;
                    break;
                }
            }
        } else {
            decrypted[i] = text[i];  // Keep spaces and punctuation unchanged
        }
    }
    decrypted[strlen(text)] = '\0';
}

int main() {
    char keyword[ALPHABET_SIZE], plaintext[100], encrypted[100], decrypted[100];
    char cipherMap[ALPHABET_SIZE];

    // Input the keyword
    printf("Enter keyword (uppercase letters only): ");
    scanf("%s", keyword);

    // Convert keyword to uppercase
    for (int i = 0; keyword[i] != '\0'; i++) {
        keyword[i] = toupper(keyword[i]);
    }

    // Generate cipher sequence
    generateCipher(keyword, cipherMap);

    printf("\nCipher Mapping:\n");
    printf("Plain:   ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
    printf("Cipher:  %s\n", cipherMap);

    // Input plaintext
    printf("\nEnter plaintext: ");
    scanf(" %[^\n]", plaintext);  // Read full line including spaces

    // Encrypt the text
    encryptText(plaintext, cipherMap, encrypted);
    printf("\nEncrypted text: %s\n", encrypted);

    // Decrypt the text
    decryptText(encrypted, cipherMap, decrypted);
    printf("\nDecrypted text: %s\n", decrypted);

    return 0;
}

