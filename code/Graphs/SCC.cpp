struct Scc {
  using graph = vector<vi>;
  int n, cnt; // spojne w porzadku topo 1 ... cnt
  graph G, T;
  vi vis, comp, post; // comp - numer spojnej wierzcholka
  Scc(int n) : n(n), cnt(0) {
    G.resize(n + 1);
    T.resize(n + 1);
    vis.resize(n + 1);
    comp.resize(n + 1);
  }
  void edge(int a, int b) {
    G[a].pb(b);
    T[b].pb(a);
  }
  void dfs(int v, graph &gra) {
    vis[v] = 1;
    if (&gra == &T) comp[v] = cnt;
    for (auto it : gra[v]) if (!vis[it]) dfs(it, gra);
    if (&gra == &G) post.pb(v);
  }
  void go() {
    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i, G);
    reverse(all(post));
    fill(all(vis), 0);
    for (auto it : post) if (!vis[it]) ++cnt, dfs(it, T);
  }
};
