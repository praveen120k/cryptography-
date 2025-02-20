#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT 1000
#define ALPHABET_SIZE 26

// English letter frequency (approximate)
const char ENGLISH_FREQ[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

// Function to count letter frequencies in ciphertext
void countFrequencies(const char *text, int freq[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            freq[toupper(text[i]) - 'A']++;
        }
    }
}

// Function to create a frequency mapping
void createFrequencyMapping(int cipherFreq[], char mapping[]) {
    int sortedIndexes[ALPHABET_SIZE];

    // Initialize indexes
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sortedIndexes[i] = i;
    }

    // Sort letter frequencies in descending order
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (cipherFreq[sortedIndexes[i]] < cipherFreq[sortedIndexes[j]]) {
                int temp = sortedIndexes[i];
                sortedIndexes[i] = sortedIndexes[j];
                sortedIndexes[j] = temp;
            }
        }
    }

    // Create substitution mapping
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        mapping[sortedIndexes[i]] = ENGLISH_FREQ[i];
    }
}

// Function to decrypt text using frequency analysis
void decrypt(const char *ciphertext, char *plaintext, char mapping[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = toupper(ciphertext[i]);
            plaintext[i] = isupper(ciphertext[i]) ? mapping[ch - 'A'] : tolower(mapping[ch - 'A']);
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

// Main function
int main() {
    char ciphertext[MAX_TEXT], plaintext[MAX_TEXT];
    int cipherFreq[ALPHABET_SIZE] = {0};
    char mapping[ALPHABET_SIZE];

    // Read ciphertext from user
    printf("Enter the ciphertext:\n");
    fgets(ciphertext, MAX_TEXT, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';  // Remove newline

    // Step 1: Count letter frequencies
    countFrequencies(ciphertext, cipherFreq);

    // Step 2: Create frequency mapping
    createFrequencyMapping(cipherFreq, mapping);

    // Step 3: Decrypt using frequency-based mapping
    decrypt(ciphertext, plaintext, mapping);

    // Display output
    printf("\nTop 1 possible plaintext:\n%s\n", plaintext);

    return 0;
}

