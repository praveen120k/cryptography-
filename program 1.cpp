#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt text using Caesar cipher
void caesarCipher(char text[], int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) { // Check if the character is a letter
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + shift) % 26 + base;
        }
    }
}

int main() {
    char text[100];
    int shift;
    
    // Input the plaintext
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0; // Remove newline character
    
    // Input the shift value
    printf("Enter shift value (1-25): ");
    scanf("%d", &shift);
    
    // Validate shift value
    if (shift < 1 || shift > 25) {
        printf("Invalid shift value! Must be between 1 and 25.\n");
        return 1;
    }
    
    // Encrypt the text
    caesarCipher(text, shift);
    
    // Output the encrypted text
    printf("Encrypted text: %s\n", text);
    
    return 0;
}

