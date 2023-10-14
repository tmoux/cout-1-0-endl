const int L; //SET THIS TO CEIL(LOG(MX_N))
int N;
int anc[MX][L];
int dep[MX];
vector<vi> graph(MX);

int jmp(int x, int d) {
    F0R(i, L) {
        if (d&(1<<i)) {
            x = anc[x][i];
        }
    }
    return x;
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) {
        swap(a, b);
    }

    a = jmp(a, dep[a] - dep[b]);
    if (a == b) return a;
    F0Rd(i, L) {
        if (anc[a][i] != anc[b][i]) {
            a = anc[a][i];
            b = anc[b][i];
        }
    }
    return anc[a][0];
}

void dfs(int v, int p) {
    anc[v][0] = p; 
    trav(a, graph[v]) {
        if (a == p) continue;
        dep[a] = dep[v] + 1;
        dfs(a, v);
    }
}

void prep() {
    F0R(i, N) F0R(j, L) anc[i][j] = -1;
    dep[0] = 0;
    dfs(0, -1);
    FOR(j, 1, L) {
        F0R(i, N) {
            if (anc[i][j-1] != -1) {
                anc[i][j] = anc[anc[i][j-1]][j-1];
            }
        }
    }
}

