#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_CIPHERTEXT_LEN 1024

// Frequency distribution for English (approximate values)
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

// Function to perform frequency attack and get top N results
void frequencyAttack(char *ciphertext, int topN) {
    double textFreq[ALPHABET_SIZE];
    double likelihoods[ALPHABET_SIZE];
    char decryptedText[MAX_CIPHERTEXT_LEN];
    int bestShifts[ALPHABET_SIZE];

    // Generate all possible mappings for monoalphabetic cipher (brute force substitution)
    char cipherAlphabet[ALPHABET_SIZE] = "abcdefghijklmnopqrstuvwxyz";
    char tempCipher[ALPHABET_SIZE];
    char tempPlain[ALPHABET_SIZE] = "etaoinshrdlcumwfgypbvkjxqz";

    // Try all possible permutations of the cipher alphabet (26 possible shifts)
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        // Create a permutation of the alphabet based on the shift
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            tempCipher[i] = cipherAlphabet[(i + shift) % ALPHABET_SIZE];
        }

        // Map the ciphertext to the substituted plaintext
        int i = 0;
        while (ciphertext[i] != '\0') {
            if (isalpha(ciphertext[i])) {
                char letter = tolower(ciphertext[i]);
                decryptedText[i] = tempCipher[letter - 'a'];
            } else {
                decryptedText[i] = ciphertext[i];
            }
            i++;
        }

        decryptedText[i] = '\0'; // Null-terminate the decrypted text

        // Calculate the frequency of the decrypted text
        calculateFrequency(decryptedText, textFreq);
        
        // Calculate the likelihood of the decrypted text
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
        printf("Shift: %d - Likelihood: %f\n", bestShifts[i], likelihoods[i]);
        // Apply the best shift and print the decrypted text
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            tempCipher[j] = cipherAlphabet[(j + bestShifts[i]) % ALPHABET_SIZE];
        }

        int j = 0;
        while (ciphertext[j] != '\0') {
            if (isalpha(ciphertext[j])) {
                decryptedText[j] = tempCipher[tolower(ciphertext[j]) - 'a'];
            } else {
                decryptedText[j] = ciphertext[j];
            }
            j++;
        }
        decryptedText[j] = '\0';  // Null-terminate the decrypted text
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

