#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 500

// Function to count character frequency
void countFrequency(char text[], int freq[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 32 && text[i] <= 126) { // Only count printable characters
            freq[text[i]]++;
        }
    }
}

// Function to replace characters in the ciphertext
void replaceCharacters(char text[], char oldChar, char newChar) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == oldChar) {
            text[i] = newChar;
        }
    }
}

int main() {
    char ciphertext[MAX_LEN] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 (88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    int freq[128] = {0}; // ASCII character frequencies

    // Step 1: Count character frequency
    countFrequency(ciphertext, freq);

    // Step 2: Display character frequency
    printf("Character Frequencies:\n");
    for (int i = 32; i <= 126; i++) {
        if (freq[i] > 0) {
            printf("%c: %d\n", i, freq[i]);
        }
    }

    // Step 3: Manual substitution
    char oldChar, newChar;
    printf("\nReplace characters manually (e.g., enter '‡ E' to replace '‡' with 'E'). Enter '0 0' to stop.\n");

    while (1) {
        printf("Enter old and new character: ");
        scanf(" %c %c", &oldChar, &newChar);

        if (oldChar == '0' && newChar == '0') {
            break;
        }

        replaceCharacters(ciphertext, oldChar, newChar);
        printf("\nUpdated Ciphertext:\n%s\n", ciphertext);
    }

    printf("\nFinal Decrypted Text:\n%s\n", ciphertext);
    return 0;
}

