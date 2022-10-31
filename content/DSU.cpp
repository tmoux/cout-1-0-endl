int parent[MX], si[MX];

void init(int N) {
    F0R(i, N) parent[i] = i, si[i] = 0;
}

int get(int x) {
    if (parent[x] != x) parent[x] = get(parent[x]);
    return parent[x];
}

void unify(int x, int y) {
    x = get(x); y = get(y);
    if (x == y) return;
    if (si[x] < si[y]) swap(x, y);
    if (si[x] == si[y]) si[x]++;
    parent[y] = x;

}
