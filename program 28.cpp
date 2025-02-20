#include <stdio.h>

// Function for modular exponentiation: (base^exp) % mod
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {  // If exponent is odd, multiply base
            result = (result * base) % mod;
        }
        base = (base * base) % mod;  // Square base
        exp /= 2;
    }
    return result;
}

int main() {
    // Public parameters
    long long q = 23;  // Prime number
    long long a = 5;   // Primitive root of q

    // Private secrets
    long long x_A = 6;  // Alice's private key
    long long x_B = 15; // Bob's private key

    // Compute public keys
    long long A = mod_exp(a, x_A, q); // A = a^x_A mod q
    long long B = mod_exp(a, x_B, q); // B = a^x_B mod q

    printf("Publicly shared values: q = %lld, a = %lld\n", q, a);
    printf("Alice sends: %lld\n", A);
    printf("Bob sends: %lld\n", B);

    // Compute shared secret
    long long key_A = mod_exp(B, x_A, q); // (B^x_A) % q
    long long key_B = mod_exp(A, x_B, q); // (A^x_B) % q

    printf("Alice's computed key: %lld\n", key_A);
    printf("Bob's computed key: %lld\n", key_B);

    if (key_A == key_B) {
        printf("Key exchange successful! Shared key = %lld\n", key_A);
    } else {
        printf("Error in key exchange.\n");
    }

    return 0;
}

