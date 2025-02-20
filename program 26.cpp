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

// Function to factorize n if d is known
void factorize_n(int n, int e, int d) {
    int phi = (d * e - 1);
    int p, q;

    // Find p and q by testing factors of phi(n)
    for (p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            q = n / p;
            if ((p - 1) * (q - 1) == phi / (d * e - 1)) {
                printf("Recovered Factors: p = %d, q = %d\n", p, q);
                break;
            }
        }
    }
    
    // Compute new d for a new public exponent e'
    int new_e = 37; // Choose a different public exponent
    int new_d = mod_inverse(new_e, phi);

    printf("New Public Key: (e' = %d, n = %d)\n", new_e, n);
    printf("New Private Key: d' = %d\n", new_d);
}

int main() {
    // Given values
    int n = 3599;  // n = p * q (previous modulus)
    int e = 31;    // Original public key
    int d = 1087;  // Original private key (leaked)

    printf("Original Public Key: (e = %d, n = %d)\n", e, n);
    printf("Original Private Key (leaked): d = %d\n", d);

    // Attempt to change only e and d
    factorize_n(n, e, d);

    return 0;
}

