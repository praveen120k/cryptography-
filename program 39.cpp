#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 1000

// Function to count letter frequencies in the ciphertext
void frequencyAnalysis(char *ciphertext, int freq[ALPHABET_SIZE]) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        freq[i] = 0; // Initialize frequency array

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int index = toupper(ciphertext[i]) - 'A';
            freq[index]++;
        }
    }
}

// Function to find the most frequent letter in the ciphertext
int mostFrequentLetter(int freq[ALPHABET_SIZE]) {
    int maxIndex = 0;
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if (freq[i] > freq[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

// Function to decrypt text with a given shift key
void decryptWithKey(char *ciphertext, int key, char *decryptedText) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            decryptedText[i] = ((ciphertext[i] - base - key + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
        } else {
            decryptedText[i] = ciphertext[i]; // Preserve non-alphabet characters
        }
    }
    decryptedText[i] = '\0';
}

// Function to perform letter frequency attack and output top possible plaintexts
void letterFrequencyAttack(char *ciphertext, int topResults) {
    int freq[ALPHABET_SIZE];
    frequencyAnalysis(ciphertext, freq);
    int mostFrequent = mostFrequentLetter(freq); // Most frequent letter index (A=0, B=1, ...)

    printf("\nTop %d Possible Decryptions:\n", topResults);
    printf("----------------------------------\n");

    for (int i = 0; i < topResults; i++) {
        int key = (mostFrequent - ('E' - 'A') + i) % ALPHABET_SIZE; // Shift guessing
        if (key < 0) key += ALPHABET_SIZE; // Ensure positive key

        char decryptedText[MAX_TEXT_LENGTH];
        decryptWithKey(ciphertext, key, decryptedText);
        printf("Key %2d: %s\n", key, decryptedText);
    }
}

// Main function
int main() {
    char ciphertext[MAX_TEXT_LENGTH];

    // Get user input
    printf("Enter the encrypted text: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0; // Remove newline character

    int topResults = 10; // Show top 10 results
    letterFrequencyAttack(ciphertext, topResults);

    return 0;
}

