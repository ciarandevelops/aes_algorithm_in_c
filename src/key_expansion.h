#ifndef KEY_EXPANSION_H_INCLUDED
#define KEY_EXPANSION_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include "variables.h"
#include "print_functions.h"

unsigned char** expand_key(unsigned char* master_key)

{
    unsigned char** key_columns = (unsigned char**)calloc(Nb * (Nr + 1), sizeof(unsigned char*));

    for (int i = 0; i < 4; i++)
    {
        key_columns[i] = (unsigned char*)malloc(Nb * sizeof(unsigned char));
        memcpy(key_columns[i], &master_key[4*i], Nb);
    };

    unsigned char* word = (unsigned char*)malloc(4 * sizeof(unsigned char));

    for (int i = 4; i < 44; i++)
    {
        memcpy(word, key_columns[i-1], 4);

        if (i % Nk == 0)
        {
            unsigned char temp = word[0];
            word[0] = word[1];
            word[1] = word[2];
            word[2] = word[3];
            word[3] = temp;

            for (int j = 0; j < Nb; j++)
            {
                {
                    word[j] = s_box[word[j]];
                }
            }
            word[0] ^= r_con[i/Nk];
        }
        unsigned char* prev_word = key_columns[i-Nk];
        unsigned char* new_word = (unsigned char*)malloc(Nb * sizeof(unsigned char));
        for (int j = 0; j < Nb; j++)
        {
            new_word[j] = prev_word[j] ^ word[j];
        }
        key_columns[i] = new_word;
    }

    unsigned char** key_matrices = (unsigned char**)malloc((Nr + 1) * sizeof(unsigned char*));
    for (int i = 0; i < (Nr + 1); i++)
    {
        key_matrices[i] = (unsigned char*)malloc(Nb * Nb * sizeof(unsigned char));
        for (int j = 0; j < Nb; j++)
        {
            for (int k = 0; k < Nb; k++)
            {
                key_matrices[i][j + k * Nb] = key_columns[i * Nb + j][k];
            }
        }
    };
    return key_matrices;
};
#endif // KEY_EXPANSION_H_INCLUDED
