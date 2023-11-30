#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AES_BLOCK_SIZE 16

void aes_encrypt_ecb(const unsigned char *plaintext, const unsigned char *key, unsigned char *ciphertext, int text_len) {
    for (int i = 0; i < text_len; ++i) {
        ciphertext[i] = plaintext[i] ^ key[i % AES_BLOCK_SIZE];
    }
}

void aes_encrypt_cbc(const unsigned char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext, int text_len) {
    unsigned char prev_block[AES_BLOCK_SIZE];
    memcpy(prev_block, iv, AES_BLOCK_SIZE);

    for (int i = 0; i < text_len; ++i) {
        unsigned char tmp[AES_BLOCK_SIZE];
        tmp[i % AES_BLOCK_SIZE] = plaintext[i] ^ prev_block[i % AES_BLOCK_SIZE] ^ key[i % AES_BLOCK_SIZE];
        ciphertext[i] = tmp[i % AES_BLOCK_SIZE];
        prev_block[i % AES_BLOCK_SIZE] = tmp[i % AES_BLOCK_SIZE];
    }
}

void aes_encrypt_cfb(const unsigned char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext, int text_len) {

    unsigned char prev_block[AES_BLOCK_SIZE];
    memcpy(prev_block, iv, AES_BLOCK_SIZE);

    for (int i = 0; i < text_len; ++i) {
        unsigned char tmp[AES_BLOCK_SIZE];
        aes_encrypt_ecb(prev_block, key, tmp, AES_BLOCK_SIZE);
        ciphertext[i] = plaintext[i] ^ tmp[0];
        memcpy(prev_block, prev_block + 1, AES_BLOCK_SIZE - 1);
        prev_block[AES_BLOCK_SIZE - 1] = ciphertext[i];
    }
}

int main() {
	unsigned char key[AES_BLOCK_SIZE];
	unsigned char iv[AES_BLOCK_SIZE];
	
	strcpy((char *)key, "my_secret_key");
	strcpy((char *)iv, "initial_vec");


    const char *plaintext = "This is a sample plaintext for encryption.";
    int plaintext_len = strlen(plaintext);

    unsigned char ecb_ciphertext[plaintext_len];
    unsigned char cbc_ciphertext[plaintext_len];
    unsigned char cfb_ciphertext[plaintext_len];

    aes_encrypt_ecb((const unsigned char *)plaintext, key, ecb_ciphertext, plaintext_len);
    aes_encrypt_cbc((const unsigned char *)plaintext, key, iv, cbc_ciphertext, plaintext_len);
    aes_encrypt_cfb((const unsigned char *)plaintext, key, iv, cfb_ciphertext, plaintext_len);

    printf("Plaintext: %s\n", plaintext);

    printf("ECB Ciphertext: ");
    for (int i = 0; i < plaintext_len; ++i) {
        printf("%02x", ecb_ciphertext[i]);
    }
    printf("\n");

    printf("CBC Ciphertext: ");
    for (int i = 0; i < plaintext_len; ++i) {
        printf("%02x", cbc_ciphertext[i]);
    }
    printf("\n");

    printf("CFB Ciphertext: ");
    for (int i = 0; i < plaintext_len; ++i) {
        printf("%02x", cfb_ciphertext[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}
