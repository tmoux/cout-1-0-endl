// note: just need dfs if all you need is cutpoints or BCCs
// if all you need is BCCs, ignore id
// if all you need is cutpoints, ignore stk, id, comps
// can add LCA on top of this to check if a path from a-b that
// does not visit c exists
// assumes graph is simple; must dfs multiple times if not connected
// be careful about handling isolated vertices

int N;
vector<vi> graph(MX), comps;
vi stk, num(MX), lo(MX), is_cp(MX), id(MX);
int ct = 0;

void dfs(int v, int p) {
    num[v] = lo[v] = ++ct;
    if (sz(graph[v]) == 0) {
        comps.pb({v});
        return;
    }
    stk.pb(v);
    trav(a, graph[v]) {
        if (a == p) continue;
        if (num[a]) {
            lo[v] = min(lo[v], num[a]);
        } else {
            dfs(a, v);
            lo[v] = min(lo[v], lo[a]);
            if (lo[a] >= num[v]) {
                is_cp[v] = (num[v] > 1 || num[a] > 2);
                comps.pb({v});
                while (comps.back().back() != a) {
                    comps.back().pb(stk.back());
                    stk.pop_back();
                }
            }
        }
    }
}

vector<vi> bct;

void build_tree() {
    int nid = 0;
    F0R(i, N) {
        if (is_cp[i]) {
            id[i] = nid++;
            bct.pb({});
        }
    }

    trav(comp, comps) {
        int v = nid++;
        bct.pb({});
        trav(u, comp) {
            if (!is_cp[u]) {
                id[u] = v;
            } else {
                bct[v].pb(id[u]);
                bct[id[u]].pb(v);
            }
        }
    }
}
