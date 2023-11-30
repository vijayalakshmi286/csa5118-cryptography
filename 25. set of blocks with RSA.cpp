#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1) {
        return 0;
    }

    while (a > 1) {
        q = a / m;
        t = m;

        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) {
        x1 += m0;
    }

    return x1;
}

int main() {
    int n = 3233;
    int e = 17;
    int blocks[] = {1791, 123, 2509, 1281};

    int common_factor = -1;
    for (int i = 0; i < sizeof(blocks) / sizeof(blocks[0]); ++i) {
        for (int j = i + 1; j < sizeof(blocks) / sizeof(blocks[0]); ++j) {
            if (gcd(blocks[i], n) != 1 && gcd(blocks[j], n) != 1) {
                common_factor = gcd(blocks[i], n);
                break;
            }
        }
        if (common_factor != -1) {
            break;
        }
    }

    if (common_factor != -1) {
        int p = common_factor;
        int q = n / p;
        int phi = (p - 1) * (q - 1);
        int d = mod_inverse(e, phi);

        int plaintext_blocks[sizeof(blocks) / sizeof(blocks[0])];
        for (int i = 0; i < sizeof(blocks) / sizeof(blocks[0]); ++i) {
            plaintext_blocks[i] = 1;
            for (int j = 0; j < d; ++j) {
                plaintext_blocks[i] = (plaintext_blocks[i] * blocks[i]) % n;
            }
        }

        printf("Plaintext blocks: ");
        for (int i = 0; i < sizeof(plaintext_blocks) / sizeof(plaintext_blocks[0]); ++i) {
            printf("%d ", plaintext_blocks[i]);
        }
        printf("\n");
    } else {
        printf("No common factor found.\n");
    }

    return 0;
}
