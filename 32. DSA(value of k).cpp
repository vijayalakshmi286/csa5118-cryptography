#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void dsa_signature(void) {
    srand(time(NULL));
    int k = rand() % 1000;
    printf("DSA Signature - Value of k: %d\n", k);
}

void rsa_signature(void) {
    srand(time(NULL));
    int k = rand() % 1000;
    printf("RSA Signature - Value of k: %d\n", k);
}

int main() {
    int choice;
    printf("Enter 1 for DSA Signature\n");
    printf("Enter 2 for RSA Signature\n");
    scanf("%d", &choice);

    if (choice == 1) {
        dsa_signature();
        dsa_signature();
    } else if (choice == 2) {
        rsa_signature();
        rsa_signature();
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
