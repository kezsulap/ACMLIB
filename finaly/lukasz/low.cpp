struct Low { // dziala dla multikrawedzi, petli, niespojnego grafu
  int n, cnt, edges;
  vector<vpii> G;
  vi low, pre, par, par_nr, used, most, root, vis_s, add_s;
  Low(int n) : n(n), edges(0) {
    G.resize(n + 1);
    low.resize(n + 1);
    pre.resize(n + 1);
    par.resize(n + 1);
    par_nr.resize(n + 1);
    root.resize(n + 1);
  }
  void edge(int a, int b) {
    ++edges;
    G[a].eb(b, edges);
    G[b].eb(a, edges);
  }
  void dfs(int v) {
    pre[v] = ++cnt;
    low[v] = pre[v];
    for (auto it : G[v]) {
      int u = it.st;
      int nr = it.nd;
      if (used[nr]) continue;
      used[nr] = 1;
      if (!pre[u]) {
        par[u] = v;
        par_nr[u] = nr;
        dfs(u);
        mini(low[v], low[u]);
      } else
        mini(low[v], pre[u]);
    }
  }
  void go() { // trzeba wywolac na poczatku!
    used.resize(edges + 1);
    for(int i = 1; i <= n; ++i) if (!pre[i]) root[i] = 1, dfs(i);
  }
  vpii mosty() {
    most.resize(edges + 1);
    vpii ans;
    for(int i = 1; i <= n; ++i) {
      if (!root[i] && low[i] == pre[i]) {
        ans.eb(i, par[i]);
        most[par_nr[i]] = 1;
      }
    }
    return ans;
  }
  vi pkt_art() { // tylko jesli potrzebujemy
    vi ans, take(n + 1), root_sons(n + 1);
    for(int i = 1; i <= n; ++i) {
      if (par[i] && root[par[i]]) {
        ++root_sons[par[i]];
      }
    }
    for(int i = 1; i <= n; ++i) {
      if (root[i] && root_sons[i] >= 2) take[i] = 1;
      if (!root[i] && !root[par[i]] && low[i] >= pre[par[i]]) take[par[i]] = 1;
    }
    for(int i = 1; i <= n; ++i) if (take[i]) ans.pb(i);
    return ans;
  }
  // kod nizej tylko jesli potrzebujemy 2spojnych
  using comps = vector<vpii>; 
  void dfs_s(int v, vpii &moja) {
    vis_s[v] = 1;
    for (auto it : G[v]) {
      int u = it.st;
      int nr = it.nd;
      if (most[nr]) continue;
      if (!add_s[nr]) {
        moja.eb(v, u);
        add_s[nr] = 1;
      }
      if (!vis_s[u]) dfs_s(u, moja);
    }
  }
  comps bico() {
    vis_s.resize(n + 1);
    add_s.resize(edges + 1);
    comps ans;
    for (auto it : mosty()) ans.pb({it});
    for(int i = 1; i <= n; ++i) {
      if (!vis_s[i]) {
        vpii curr;
        dfs_s(i, curr);
        if (!curr.empty()) ans.pb(curr);
      }
    }
    return ans;
  }
};
