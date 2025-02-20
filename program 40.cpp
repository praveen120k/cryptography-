#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 10000  // Increased buffer size

// Function to process text (for future decryption or analysis)
void process_text(char *text) {
    printf("Processing text: %s\n", text);
}

int main() {
    // Allocate memory dynamically to prevent buffer overflow
    char *ciphertext = (char *)malloc(MAX_TEXT_LENGTH * sizeof(char));
    
    // Check if memory allocation was successful
    if (ciphertext == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter the encrypted text: ");
    
    // Read input safely
    if (fgets(ciphertext, MAX_TEXT_LENGTH, stdin) == NULL) {
        printf("Error reading input.\n");
        free(ciphertext);
        return 1;
    }

    // Remove newline character if present
    ciphertext[strcspn(ciphertext, "\n")] = 0;  

    printf("Ciphertext received: %s\n", ciphertext);

    // Process the text (example: letter frequency analysis, decryption, etc.)
    process_text(ciphertext);

    // Free allocated memory
    free(ciphertext);

    return 0;
}

