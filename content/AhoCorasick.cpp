// NOTE: val/num variables in v, cnt argument to add_string,
// and dfs/compute methods may be unnecessary
struct AhoCorasick {
    static const int K = 26;

    struct V {
        int nxt[K];
        bool leaf = false;
        int p = -1;
        char pch;
        int link = -1;
        int go[K];
        ll val = -1;
        ll num = 0;

        V(int p=-1, char ch='$') : p(p), pch(ch) {
            fill(begin(nxt), end(nxt), -1);
            fill(begin(go), end(go), -1);
        }
    };

    vector<V> t;

    void init() {
        V v; t.pb(v);
    }

    void add_string(string const& s, int cnt) {
        int v = 0;
        trav(ch, s) {
            int c = ch - 'a';
            if (t[v].nxt[c] == -1) {
                t[v].nxt[c] = t.size();
                t.emplace_back(v, ch);
            }
            v = t[v].nxt[c];
        }
        t[v].leaf = true;
        t[v].num = cnt;
    }

    ll dfs(int v) {
        if (t[v].val != -1) {
            return t[v].val;
        }
        ll ans = t[v].num;
        ans += dfs(get_link(v));
        return t[v].val = ans;
    }

    // sets value for each node to sum of values
    // over suffix links
    void compute() {
        t[0].val = 0;
        FOR(i, 1, sz(t)) {
            dfs(i);
        }
    }

    int get_link(int v) {
        if (t[v].link == -1) {
            if (v == 0 || t[v].p == 0)
                t[v].link = 0;
            else
                t[v].link = go(get_link(t[v].p), t[v].pch);
        }
        return t[v].link;
    }

    int go(int v, char ch) {
        int c = ch - 'a';
        if (t[v].go[c] == -1) {
            if (t[v].nxt[c] != -1)
                t[v].go[c] = t[v].nxt[c];
            else
                t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
        }
        return t[v].go[c];
    }
};
