#ifndef DECRYPTION_H_INCLUDED
#define DECRYPTION_H_INCLUDED

void inv_sub_bytes(unsigned char s[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            s[i][j] = inv_s_box[s[i][j]];
        }
    }
}

void inv_shift_rows(unsigned char state[][4]) {
    unsigned char tmp;

    tmp = state[3][1];
    state[3][1] = state[2][1];
    state[2][1] = state[1][1];
    state[1][1] = state[0][1];
    state[0][1] = tmp;

    tmp = state[0][2];
    state[0][2] = state[2][2];
    state[2][2] = tmp;
    tmp = state[1][2];
    state[1][2] = state[3][2];
    state[3][2] = tmp;

    tmp = state[1][3];
    state[1][3] = state[2][3];
    state[2][3] = state[3][3];
    state[3][3] = state[0][3];
    state[0][3] = tmp;
};

void inv_mix_columns(unsigned char s[4][4]) {
    unsigned char u, v;

    for (int i = 0; i < 4; ++i) {
        u = xtime(xtime(s[i][0] ^ s[i][2]));
        v = xtime(xtime(s[i][1] ^ s[i][3]));

        s[i][0] ^= u;
        s[i][1] ^= v;
        s[i][2] ^= u;
        s[i][3] ^= v;
    }
    mix_columns(s);
};

#endif // DECRYPTION_H_INCLUDED
