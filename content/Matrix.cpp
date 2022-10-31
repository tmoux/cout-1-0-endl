vector<vl> matMul(vector<vl>& A, vector<vl> &B) {
    int R = sz(A), C = sz(B[0]), I = sz(B);
    vector<vl> res(R, vector<vi>(C, 0));
    F0R(i, R) {
        F0R(j, I) {
            F0R(k, C) {
                res[i][k] += A[i][j] + B[j][k];
            }
        }
    }
    return res;
}

vector<vi> exp(vector<vi> M, ll P) {
    vector<vi> res(sz(M), vi(sz(M[0]), 0));
    F0R(i, sz(M)) {
        res[i][i] = 1;
    }
    for (; P; p /= 2; M = matMul(M, M)) if (P & 1) R = matMul(R, M);
    return res;
}
