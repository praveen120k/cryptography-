#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Mock hashing function (simple XOR-based for demo)
uint32_t hash_message(const char *message) {
    uint32_t hash = 0;
    while (*message) {
        hash = (hash << 5) - hash + (*message++); // Simple rolling hash
    }
    return hash;
}

// Simulated DSA Signature (random k for each signing)
void dsa_sign(const char *message, uint32_t private_key, uint32_t p) {
    uint32_t hash = hash_message(message);
    
    // Generate a new random k each time (in real DSA, it must be cryptographically secure)
    uint32_t k = (rand() % (p - 1)) + 1; 

    // Compute signature (mock calculation)
    uint32_t r = (hash * k) % p; 
    uint32_t s = (private_key * r) % p; 

    printf("DSA Signature: (r = %u, s = %u) [with random k = %u]\n", r, s, k);
}

// Simulated RSA Signature (same output for the same message)
void rsa_sign(const char *message, uint32_t private_key, uint32_t n) {
    uint32_t hash = hash_message(message);
    
    // Compute signature (mock RSA: s = hash^d mod n)
    uint32_t signature = (hash * private_key) % n; 

    printf("RSA Signature: %u [Same for identical messages]\n", signature);
}

int main() {
    srand(time(NULL)); // Seed random for DSA k

    const char *message = "Hello, DSA and RSA!";
    uint32_t private_key = 12345; // Example private key
    uint32_t prime_p = 9973;      // A prime modulus for DSA
    uint32_t rsa_n = 3233;        // Modulus for RSA (n = p*q)

    printf("Signing the message: \"%s\"\n\n", message);

    // Generate DSA Signatures (should be different each time)
    printf("DSA Signatures:\n");
    dsa_sign(message, private_key, prime_p);
    dsa_sign(message, private_key, prime_p);

    // Generate RSA Signatures (should be the same)
    printf("\nRSA Signatures:\n");
    rsa_sign(message, private_key, rsa_n);
    rsa_sign(message, private_key, rsa_n);

    return 0;
}

