#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to encrypt text using Monoalphabetic Substitution Cipher
void monoalphabeticCipher(char text[], char key[ALPHABET_SIZE]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) { // Check if the character is a letter
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = key[text[i] - base];
        }
    }
}

int main() {
    char text[100];
    char key[ALPHABET_SIZE] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M'};
    
    // Input the plaintext
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0; // Remove newline character
    
    // Encrypt the text
    monoalphabeticCipher(text, key);
    
    // Output the encrypted text
    printf("Encrypted text: %s\n", text);
    
    return 0;
}

