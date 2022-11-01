struct FU {                          //numeracja od zera
  vi p; vector<bool> b;              //nie dawać multikrawędzi ani pętli
  FU() {}                            //nie odpalać IsPlanar() ponad raz
  FU(int n) : p(n), b(n) { iota(p.begin(), p.end(), 0); }
  pair<int, bool> Find(int v) {
    if (p[v] == v) { return {v, 0}; }
    auto res = Find(p[v]); res.second ^= b[v];
    p[v] = res.first; b[v] = res.second; return res;
  }
  bool Union(int x, int y, bool flip) {
    bool xb, yb; tie(x, xb) = Find(x); tie(y, yb) = Find(y);
    if (x == y) { return !(xb ^ yb ^ flip); }
    p[x] = y; b[x] = xb ^ yb ^ flip; return true;
  }
};
struct PlanarityTest {
  int N, M, tm;
  vector<vi> adj, dn, up; vector<pair<int,int>> e_up;
  vector<bool> vis; vi low, pre;
  FU fu;
  void DfsLow(int v, int p) {
    vis[v] = true; low[v] = pre[v] = tm++;
    for (int s : adj[v]) {
      if (s == p) { continue; }
      if (!vis[s]) {
        dn[v].pb(s); DfsLow(s, v); low[v] = min(low[v], low[s]);
      } else if (pre[s] < pre[v]) {
        up[v].pb(siz(e_up)); e_up.pb({v, s});
        low[v] = min(low[v], pre[s]);
      }
    }
  }
  vi Interlace(const vi &ids, int lo) {
    vi ans;
    for (int e : ids) if (pre[e_up[e].second] > lo) ans.pb(e);
    return ans;
  }
  bool AddFU(const vi &a, const vi &b) {
    for (int k = 1; k <= siz(a) - 1; ++k) if (!fu.Union(a[k - 1], a[k], 0)) { return 0; }
    for (int k = 1; k <= siz(b) - 1; ++k) if (!fu.Union(b[k - 1], b[k], 0)) { return 0; }
    if (siz(a) && siz(b) && !fu.Union(a[0], b[0], 1)) { return 0; }
    return 1;
  }
  bool DfsPlanar(int v, int p) {
    for (int s : dn[v]) if (!DfsPlanar(s, v)) { return false; }
    auto sz = siz(dn[v]);
		for (int i = 0; i < sz; ++i) {
			for (int j = i + 1; j < sz; ++j)
        auto a = Interlace(up[dn[v][i]], low[dn[v][j]]);
        auto b = Interlace(up[dn[v][j]], low[dn[v][i]]);
        if (!AddFU(a, b)) { return false; }
      }
      for (int j : up[v]) {
        if (e_up[j].first != v) { continue; }
        auto a = Interlace(up[dn[v][i]], pre[e_up[j].second]);
        auto b = Interlace({j}, low[dn[v][i]]);
        if (!AddFU(a, b)) { return false; }
      }
    }
    for (int s : dn[v]) {
      for (int idx : up[s]) {
        if (pre[e_up[idx].second] < pre[p]) { up[v].pb(idx); }
      }
      up[s].clear(); up[s].shrink_to_fit();
    }
    return true;
  }
  PlanarityTest(int n) : N(n), M(0), adj(n) {}
  void AddEdge(int u, int v) { adj[u].pb(v); adj[v].pb(u); ++M; }
  bool IsPlanar() {
    if (N <= 3) { return true; }
    if (M > 3 * N - 6) { return false; }
    vis = vector<bool>(N);
    up = dn = vector<vi>(N);
    low = pre = vi(N);
		for (int v = 0; v < N; ++v) if (!vis[v]) {
      e_up.clear(); tm = 0; DfsLow(v, -1);
      fu = FU(siz(e_up));
      if (!DfsPlanar(v, -1)) { return false; }
    }
    return true;
  }
};
