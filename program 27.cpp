#include <stdio.h>
#include <stdlib.h>

// RSA Encryption: c = (m^e) % n
int rsa_encrypt(int m, int e, int n) {
    int result = 1;
    while (e > 0) {
        if (e % 2 == 1) { // If e is odd, multiply result by base
            result = (result * m) % n;
        }
        m = (m * m) % n; // Square base
        e /= 2;
    }
    return result;
}

// Frequency analysis: Count occurrences of ciphertexts
void frequency_analysis(int ciphertexts[], int length) {
    int freq[26] = {0};

    // Count frequency of each encrypted letter
    for (int i = 0; i < length; i++) {
        freq[ciphertexts[i]]++;
    }

    // Print results
    printf("\nFrequency Analysis of Encrypted Letters:\n");
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            printf("Ciphertext %d: %d times\n", i, freq[i]);
        }
    }
}

int main() {
    // Simulated RSA parameters (using small values for demonstration)
    int e = 7, n = 143; // Normally n should be much larger!
    
    // Sample plaintext: "HELLO"
    char plaintext[] = "HELLO";
    int length = sizeof(plaintext) - 1;
    int ciphertexts[length];

    printf("Original Text: %s\n", plaintext);
    printf("Encrypted (using weak RSA per character): ");

    // Encrypt each letter separately
    for (int i = 0; i < length; i++) {
        int m = plaintext[i] - 'A'; // Convert 'A'-'Z' to 0-25
        ciphertexts[i] = rsa_encrypt(m, e, n);
        printf("%d ", ciphertexts[i]); // Print encrypted values
    }

    printf("\n\nRunning Frequency Analysis Attack...\n");
    frequency_analysis(ciphertexts, length);

    return 0;
}

