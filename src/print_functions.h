#ifndef PRINT_FUNCTIONS_H_INCLUDED
#define PRINT_FUNCTIONS_H_INCLUDED

void print_key_matrices(unsigned char** key_matrices) {
    for (int i = 0; i < 11; i++) {
        printf("Round %d:\n", i);
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                printf("%02x ", key_matrices[i][j + k * 4]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void print_matrix(unsigned char matrix[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%02X ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_round(unsigned char bytes[4])
{
        for (int j = 0; j < 4; j++)
        {
            printf("%02X ", bytes[j]);
        }
        printf("\n");

}

void print_bytes(char *key, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02x ", key[i]);
    }
    printf("\n");
}

#endif // PRINT_FUNCTIONS_H_INCLUDED
