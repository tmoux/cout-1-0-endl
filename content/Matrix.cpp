vector<vl> matMul(vector<vl>& A, vector<vl> &B) {
    int R = sz(A), C = sz(B[0]), I = sz(B);
    vector<vl> res(R, vl(C, 0));
    F0R(i, R) {
        F0R(j, I) {
            F0R(k, C) {
                res[i][k] += (A[i][j] * B[j][k]);
            }
        }
    }
    return res;
}

vector<vl> exp(vector<vl> M, ll P) {
    vector<vl> R(sz(M), vl(sz(M[0]), 0));
    F0R(i, sz(M)) {
        R[i][i] = 1;
    }
    for (; P; P /= 2, M = matMul(M, M)) if (P & 1) R = matMul(R, M);
    return R;
}
