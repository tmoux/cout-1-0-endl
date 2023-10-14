int h = 0, k = 0;
while (h < sz(coef) && k < sz(coef[0])) {
    int i_max = h; ld max_val = abs(coef[h][k]);
    FOR(j, h+1, sz(coef)) if (ckmax(max_val, abs(coef[j][k]))) i_max = j;
    if (abs(coef[i_max][k]) < 1e-9) {
        k++;
    } else {
        F0R(i, sz(coef[0])) {
            swap(coef[h][i], coef[i_max][i]);
        }
        ld inVal = (ld) 1 / coef[h][k];
        F0R(i, sz(coef[0])) {
            coef[h][i] *= inVal;
        }
        F0R(i, sz(coef)) {
            if (i == h) continue;
            ld cur = coef[i][k];
            F0R(j, sz(coef[0])) {
                coef[i][j] -= cur * coef[h][j];
            }
        }
        h++; k++;
    }
}
