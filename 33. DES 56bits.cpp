#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_bits(size_t const size, void const *const ptr) {
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = b[i] >> j;
            byte &= 1;
            printf("%u", byte);
        }
    }
    puts("");
}

int main() {
    unsigned char plaintext[8] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38};

    unsigned char key[7] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    printf("Plaintext: ");
    print_bits(8, plaintext);

    int i;
    for (i = 0; i < 7; i++) {
        int parity = 0;
        int j;
        for (j = 0; j < 7; j++) {
            if (key[i] & (1 << j)) {
                parity++;
            }
        }
        key[i] |= (parity % 2) << 7;
    }

    printf("Key: ");
    print_bits(56, key);

    unsigned char ciphertext[8];
    for (i = 0; i < 8; i++) {
        ciphertext[i] = plaintext[i] ^ key[i];
    }

    printf("Ciphertext: ");
    print_bits(8, ciphertext);

    return 0;
}
