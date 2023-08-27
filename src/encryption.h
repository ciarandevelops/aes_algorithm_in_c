#ifndef ENCRYPTION_H_INCLUDED
#define ENCRYPTION_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include "variables.h"
#include "print_functions.h"
#include "key_expansion.h"
#include "processing_functions.h"

void sub_bytes(unsigned char s[4][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            s[i][j] = s_box[s[i][j]];
        }
    }
};

void shift_rows(unsigned char state[][4]) {
    unsigned char tmp;

    tmp = state[0][1];
    state[0][1] = state[1][1];
    state[1][1] = state[2][1];
    state[2][1] = state[3][1];
    state[3][1] = tmp;

    tmp = state[0][2];
    state[0][2] = state[2][2];
    state[2][2] = tmp;
    tmp = state[1][2];
    state[1][2] = state[3][2];
    state[3][2] = tmp;

    tmp = state[0][3];
    state[0][3] = state[3][3];
    state[3][3] = state[2][3];
    state[2][3] = state[1][3];
    state[1][3] = tmp;
};

unsigned char xtime(unsigned char a)
{
    return ((a << 1) ^ 0x1B) & 0xFF ? (a & 0x80 ? 0x1B : 0x00) ^ ((a << 1) & 0xFF) : (a << 1);
};

void mix_single_column(unsigned char *a)
{
    unsigned char t = a[0] ^ a[1] ^ a[2] ^ a[3];
    unsigned char u = a[0];
    a[0] ^= t ^ xtime(a[0] ^ a[1]);
    a[1] ^= t ^ xtime(a[1] ^ a[2]);
    a[2] ^= t ^ xtime(a[2] ^ a[3]);
    a[3] ^= t ^ xtime(a[3] ^ u);
};

void mix_columns(unsigned char s[4][4])
{
    int i;
    for (i = 0; i < 4; i++) {
        mix_single_column(s[i]);
    }
};

void add_round_key(unsigned char s[4][4], unsigned char k[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            s[i][j] ^= k[i][j];
        }
    }
};

#endif // ENCRYPTION_H_INCLUDED
