#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char key;
    char value;
} KeyValuePair;

char* decryptSimpleSubstitution(const char* ciphertext, KeyValuePair* key, int keySize) {
    int ciphertextLength = strlen(ciphertext);
    char* decryption = (char*)malloc((ciphertextLength + 1) * sizeof(char));

    for (int i = 0; i < ciphertextLength; ++i) {
        bool found = false;
        for (int j = 0; j < keySize; ++j) {
            if (ciphertext[i] == key[j].key) {
                decryption[i] = key[j].value;
                found = true;
                break;
            }
        }
        if (!found) {
            decryption[i] = ciphertext[i];
        }
    }
    decryption[ciphertextLength] = '\0';
    return decryption;
}

int main() {
    const char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†860))85;;]8*;:‡*8†83"
                               "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*-4)88*"
                               ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81"
                               "(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    
    KeyValuePair hints[] = {
        {'†', 'E'}, {'4', 'T'}, {'8', 'H'}, {'†', 'E'}, {'3', 'R'}, {'1', 'A'}, {';', 'N'},
        {'6', 'I'}, {'5', 'S'}, {'0', 'O'}, {'-', 'F'}, {':', 'U'}, {']', 'L'}, {'(', 'W'},
        {')', 'Y'}, {'?', 'G'}
    };

    int hintsSize = sizeof(hints) / sizeof(hints[0]);

    char* decryptedMessage = decryptSimpleSubstitution(ciphertext, hints, hintsSize);

    printf("Decrypted Message:\n");
    printf("%s\n", decryptedMessage);

    free(decryptedMessage);

    return 0;
}

