#include <stdio.h>

unsigned char bytes2matrix(const unsigned char *text, unsigned char matrix[4][4]) {
    for (int i = 0; i < 16; i++) {
        int row = i / 4;
        int col = i % 4;
        matrix[row][col] = text[i];
    }
}