//from https://cp-algorithms.com/graph/dinic.html
//Complexity: O(E*V^2)
struct Edge {
   int v, u;
   ll cap, flow = 0;
   Edge(int v, int u, ll cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
   const ll flow_inf = 1e18;
   vector<Edge> edges;
   vector<vi> adj;
   int n, m = 0;
   int s, t;
   vi lev, ptr;
   queue<int> q;

   Dinic(int n, int s, int t) : n(n), s(s), t(t) {
       adj.resize(n);
       lev.resize(n);
       ptr.resize(n);
   }

   void add_edge(int v, int u, ll cap) {
       edges.emplace_back(v, u, cap);
       edges.emplace_back(u, v, 0);
       adj[v].push_back(m);
       adj[u].push_back(m + 1);
       m += 2;
   }

   bool bfs() {
       while (!q.empty()) {
           int v = q.front();
           q.pop();
           trav(id, adj[v]) {
               if (edges[id].cap - edges[id].flow < 1)
                   continue;
               if (lev[edges[id].u] != -1)
                   continue;
               lev[edges[id].u] = lev[v] + 1;
               q.push(edges[id].u);
           }
       }
       return lev[t] != -1;
   }

   ll dfs(int v, ll pu) {
       if (pu == 0)
           return 0;
       if (v == t)
           return pu;
       for (int& cid = ptr[v]; cid < sz(adj[v]); cid++) {
           int id = adj[v][cid];
           int u = edges[id].u;
           if (lev[v] + 1 != lev[u] || edges[id].cap - edges[id].flow < 1)
               continue;
           ll tr = dfs(u, min(pu, edges[id].cap - edges[id].flow));
           if (tr == 0)
               continue;
           edges[id].flow += tr;
           edges[id ^ 1].flow -= tr;
           return tr;
       }
       return 0;
   }

   ll flow() {
       ll f = 0;
       while (true) {
           fill(all(lev), -1);
           lev[s] = 0;
           q.push(s);
           if (!bfs())
               break;
           fill(all(ptr), 0);
           while (ll pu = dfs(s, flow_inf)) {
               f += pu;
           }
       }
       return f;
   }
};
