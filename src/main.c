#include <stdio.h>
#include <stdlib.h>

#include "variables.h"
#include "processing_functions.h"
#include "key_expansion.h"
#include "print_functions.h"
#include "encryption.h"
#include "decryption.h"
#include "aes.h"

int main() {
    char key[] = "mysecretkey12345";
    unsigned char* master_key = (unsigned char*)key;

    char password[] = "thisisatest009876";
    unsigned char plaintext[4][4];

    // Copy the data from the pointer to the 2D array
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            plaintext[i][j] = (unsigned char)password[i * 4 + j];
        }
    }

    printf("\nORIGINAL PLAINTEXT BLOCK: \n");
    print_matrix(plaintext);

    unsigned char* ciphertext = (unsigned char*) malloc(16 * sizeof(unsigned char));

    ciphertext = encrypt_block(plaintext, master_key);

    printf("\nENCRYPTED CIPHERTEXT BLOCK: \n");
    print_matrix(ciphertext);

    unsigned char* password_unlocked = (unsigned char*) malloc(16 * sizeof(unsigned char));
    password_unlocked = decrypt_block(ciphertext, master_key);

    printf("\nDECRYPTED CIPHERTEXT BLOCK: \n");
    print_matrix(password_unlocked);

return 0;
};

