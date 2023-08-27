#ifndef AES_H_INCLUDED
#define AES_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include "variables.h"
#include "print_functions.h"
#include "key_expansion.h"
#include "processing_functions.h"

unsigned char* encrypt_block(unsigned char* plaintext, unsigned char* key) {

    add_round_key(plaintext, key);

    unsigned char** keys = expand_key(key);

    unsigned char keys_i_col_first[4][4];
    unsigned char keys10_col_first[4][4];

    int i;
    for (i = 1; i < 10; i++) {
        sub_bytes(plaintext);
        shift_rows(plaintext);
        mix_columns(plaintext);
        unsigned char result[4][4];
        switch_rows_columns(keys[i], result);
        add_round_key(plaintext, result);
    }

    sub_bytes(plaintext);
    shift_rows(plaintext);
    switch_rows_columns(keys[10], keys10_col_first);
    add_round_key(plaintext, keys10_col_first);

    return plaintext;
};


unsigned char* decrypt_block(unsigned char* ciphertext, unsigned char* key) {

    unsigned char** keys = expand_key(key);
    unsigned char keys10_col_first[4][4];
    unsigned char keys0_col_first[4][4];
    switch_rows_columns(keys[10], keys10_col_first);
    add_round_key(ciphertext, keys10_col_first);
    inv_shift_rows(ciphertext);
    inv_sub_bytes(ciphertext);

    int i;
    for (i = 9; i > 0; i--) {
        unsigned char result[4][4];
        switch_rows_columns(keys[i], result);
        add_round_key(ciphertext, result);
        inv_mix_columns(ciphertext);
        inv_shift_rows(ciphertext);
        inv_sub_bytes(ciphertext);
    }
    switch_rows_columns(keys[0], keys0_col_first);
    add_round_key(ciphertext, keys0_col_first);
    return ciphertext;
};

#endif // AES_H_INCLUDED
