#include <stdio.h>
#include <math.h>

int main() {
    // Calculating the total number of Playfair cipher keys (approximately 25!)
    double total_keys = 0;
    for (int i = 25; i >= 1; i--) {
        total_keys += log2(i);
    }

    // Approximate the power of 2
    printf("Total number of Playfair cipher keys (approx): 2^%.2f\n", total_keys);
    return 0;
}

