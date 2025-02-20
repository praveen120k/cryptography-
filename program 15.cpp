#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_CIPHERTEXT_LEN 1024

// Letter frequency distribution for English
double freq[ALPHABET_SIZE] = {
    0.1270, 0.0906, 0.0817, 0.0751, 0.0697, 0.0675, 0.0633, 0.0609, 0.0599, 0.0425,
    0.0403, 0.0278, 0.0276, 0.0241, 0.0223, 0.0202, 0.0202, 0.0175, 0.0149, 0.0149,
    0.0098, 0.0077, 0.0015, 0.0007, 0.0015, 0.0010
};

// Function to calculate the frequency distribution of a string
void calculateFrequency(char *text, double *textFreq) {
    int count[ALPHABET_SIZE] = {0};
    int length = 0;

    // Count the frequency of each letter (ignore non-alphabetic characters)
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            text[i] = tolower(text[i]);  // Convert to lowercase
            count[text[i] - 'a']++;
            length++;
        }
    }

    // Calculate the frequency for each letter
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        textFreq[i] = (double)count[i] / length;
    }
}

// Function to calculate the "likelihood" of a given text based on frequency distribution
double calculateLikelihood(double *textFreq) {
    double likelihood = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        likelihood += (textFreq[i] - freq[i]) * (textFreq[i] - freq[i]);
    }
    return likelihood;
}

// Function to decrypt a ciphertext using a given shift value
void decryptWithShift(char *ciphertext, int shift, char *plaintext) {
    int i = 0;
    while (ciphertext[i] != '\0') {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            plaintext[i] = ciphertext[i];  // Non-alphabetic characters remain unchanged
        }
        i++;
    }
    plaintext[i] = '\0';  // Null-terminate the plaintext
}

// Function to perform frequency attack and get top N results
void frequencyAttack(char *ciphertext, int topN) {
    double textFreq[ALPHABET_SIZE];
    double likelihoods[ALPHABET_SIZE];
    char decryptedText[MAX_CIPHERTEXT_LEN];
    int bestShifts[ALPHABET_SIZE];

    // Try all possible shifts (0 to 25)
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        decryptWithShift(ciphertext, shift, decryptedText);
        calculateFrequency(decryptedText, textFreq);
        likelihoods[shift] = calculateLikelihood(textFreq);
        bestShifts[shift] = shift;
    }

    // Sort the shifts based on likelihood (ascending)
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (likelihoods[i] > likelihoods[j]) {
                // Swap likelihoods
                double temp = likelihoods[i];
                likelihoods[i] = likelihoods[j];
                likelihoods[j] = temp;

                // Swap shifts accordingly
                int tempShift = bestShifts[i];
                bestShifts[i] = bestShifts[j];
                bestShifts[j] = tempShift;
            }
        }
    }

    // Print the top N possible plaintexts
    printf("Top %d Possible Plaintexts:\n", topN);
    for (int i = 0; i < topN; i++) {
        decryptWithShift(ciphertext, bestShifts[i], decryptedText);
        printf("Shift: %d - Likelihood: %f\n", bestShifts[i], likelihoods[i]);
        printf("Decrypted Text: %s\n\n", decryptedText);
    }
}

int main() {
    char ciphertext[MAX_CIPHERTEXT_LEN];
    int topN;

    // Input the ciphertext and the number of top guesses to display
    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_CIPHERTEXT_LEN, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';  // Remove newline character

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);

    // Perform the frequency attack and display the top N results
    frequencyAttack(ciphertext, topN);

    return 0;
}

