int N;
vector<vi> graph;

vector<bool> vis;
vi tin, low; 
int ct;

void mark_cp(int v) {
    // TODO: mark v as cutpoint somehow
}

void dfs(int v, int p = -1) {
    vis[v] = true;
    tin[v] = low[v] = ct++;
    int ch=0;
    trav(to, graph[v]) {
        if (to == p) continue;
        if (vis[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p!=-1)
                mark_cp(v);
            ++ch;
        }
    }
    if(p == -1 && ch > 1)
        mark_cp(v);
}

void find_cutpoints() {
    ct = 0;
    vis.assign(N, false);
    tin.assign(N, -1);
    low.assign(N, -1);
    for (int i = 0; i < N; ++i) {
        if (!vis[i])
            dfs(i);
    }
}
