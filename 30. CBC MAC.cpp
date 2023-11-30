#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AES_BLOCK_SIZE 16

unsigned char* xor_bytes(const unsigned char *byte_str1, const unsigned char *byte_str2, int len) {
	unsigned char *result = (unsigned char *)malloc(len);
    if (!result) {
        return NULL;
    }

    for (int i = 0; i < len; ++i) {
        result[i] = byte_str1[i] ^ byte_str2[i];
    }

    return result;
}

unsigned char* cbc_mac(const unsigned char *key, const unsigned char *message, int msg_len) {
    unsigned char *prev_block = (unsigned char *)malloc(AES_BLOCK_SIZE);
    if (!prev_block) {
        return NULL;
    }
    memset(prev_block, 0, AES_BLOCK_SIZE);

    unsigned char *xor_result;
    unsigned char *encrypted_block;
    unsigned char *padded_message = (unsigned char *)malloc(((msg_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE);
    if (!padded_message) {
        free(prev_block);
        return NULL;
    }
    memset(padded_message, 0, ((msg_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE);
    memcpy(padded_message, message, msg_len);

    for (int i = 0; i < msg_len; i += AES_BLOCK_SIZE) {
        xor_result = xor_bytes(padded_message + i, prev_block, AES_BLOCK_SIZE);
        if (!xor_result) {
            free(prev_block);
            free(padded_message);
            return NULL;
        }

        encrypted_block = (unsigned char *)malloc(AES_BLOCK_SIZE);
        if (!encrypted_block) {
            free(prev_block);
            free(padded_message);
            free(xor_result);
            return NULL;
        }
        memcpy(encrypted_block, xor_result, AES_BLOCK_SIZE);

        free(prev_block);
        prev_block = encrypted_block;
        free(xor_result);
    }

    free(padded_message);
    return prev_block;
}

int main() {
    unsigned char key[AES_BLOCK_SIZE * 2];
    unsigned char message[] = "Hello, this is a one-block message.";
    int msg_len = strlen((const char *)message);

    unsigned char *t = cbc_mac(key, message, msg_len);
    if (t) {
        printf("Original T (MAC for one-block message): ");
        for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
            printf("%02x", t[i]);
        }
        printf("\n");

        free(t);
    } else {
        printf("Error calculating CBC-MAC.\n");
    }

    return 0;
}
