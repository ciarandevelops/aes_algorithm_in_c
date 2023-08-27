#ifndef PROCESSING_FUNCTIONS_H_INCLUDED
#define PROCESSING_FUNCTIONS_H_INCLUDED

#include <stdlib.h>
#include "variables.h"

switch_rows_columns(unsigned char matrix[4][4], unsigned char result[4][4]) {
    int i, j;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            result[i][j] = matrix[j][i];
        }
    }
};

#endif // PROCESSING_FUNCTIONS_H_INCLUDED
