#include <stdio.h>

// Function to compute the greatest common divisor (GCD)
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Extended Euclidean Algorithm to find modular inverse
int mod_inverse(int e, int phi) {
    int t1 = 0, t2 = 1, r1 = phi, r2 = e, q, temp;

    while (r2 > 0) {
        q = r1 / r2;

        temp = r1;
        r1 = r2;
        r2 = temp - q * r2;

        temp = t1;
        t1 = t2;
        t2 = temp - q * t2;
    }

    if (t1 < 0)
        t1 += phi;  // Ensure d is positive

    return t1;
}

int main() {
    // Given values
    int n = 3599;       // n = pq (we don’t know p and q)
    int e = 31;         // Public exponent
    int known_plaintext = 1770;  // Given that it has a common factor with n

    // Step 1: Find p using GCD
    int p = gcd(known_plaintext, n);
    if (p == 1 || p == n) {
        printf("No useful common factor found.\n");
        return 1;
    }

    // Step 2: Compute q
    int q = n / p;
    printf("Prime factors found: p = %d, q = %d\n", p, q);

    // Step 3: Compute Euler's Totient Function f(n)
    int phi = (p - 1) * (q - 1);
    printf("Euler's Totient f(n) = %d\n", phi);

    // Step 4: Compute d as the modular inverse of e modulo f(n)
    int d = mod_inverse(e, phi);
    printf("Private Key (d) = %d\n", d);

    return 0;
}

