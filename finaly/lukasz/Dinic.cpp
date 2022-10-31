using T = long long;
struct Flow {
  struct E {
    int dest;
    T orig, *lim, *rev;
  };
  int zr, uj, n = 0;
  vector<unique_ptr<T>> ts;
  vector<vector<E>> graf;
  vi ptr, odl;
  void vert(int v) {
    n = max(n, v + 1);
    graf.resize(n);
    ptr.resize(n);
    odl.resize(n);
  }
  bool iszero(T v) {
    return !v; // Zmienić dla doubli.
  }
  void bfs() {
    fill(all(odl), 0);
    vi kol = {zr};
    odl[zr] = 1;
    for (int i = 0; i < siz(kol); i++) {
      for (E& e : graf[kol[i]]) {
        if (!odl[e.dest] and !iszero(*e.lim)) {
          odl[e.dest] = odl[kol[i]] + 1;
          kol.pb(e.dest);
        }
      }
    }
  }
  T dfs(int v, T lim) {
    if (v == uj) return lim;
    T ret = 0, wez;
    for (int& i = ptr[v]; i < siz(graf[v]); i++) {
      E& e = graf[v][i];
      if (odl[e.dest] == odl[v] + 1 and !iszero(*e.lim) and
          !iszero(wez = dfs(e.dest, min(*e.lim, lim)))) {
        ret += wez;
        *e.lim -= wez;
        *e.rev += wez;
        lim -= wez;
        if (iszero(lim)) break;
      }
    }
    return ret;
  }
  void add_edge(int u, int v, T lim, bool bi = false /* bidirectional? */) {
    vert(max(u, v));
    T *a = new T(lim), *b = new T(lim * bi);
    ts.eb(a);
    ts.eb(b);
    graf[u].pb(E{v, lim,      a, b});
    graf[v].pb(E{u, lim * bi, b, a});
  }
  T dinic(int zr_, int uj_) {
    zr = zr_; uj = uj_;
    vert(max(zr, uj));
    T ret = 0;
    while (true) {
      bfs();
      fill(all(ptr), 0);
      const T sta = dfs(zr, numeric_limits<T>::max());  // Dla doubli można dać
      if (iszero(sta)) break;                           // infinity() zamiast
      ret += sta;                                       // max().
    }
    return ret;
  }
  vi cut() {
    vi ret;
    bfs();
    for (int i = 0; i < n; i++)
      if (odl[i])
        ret.pb(i);
    return ret;
  }
  map<pii, T> get_flowing() {  // Tam gdzie plynie 0 może nie być
    map<pii, T> ret;           // krawędzi.
    for (int i = 0; i < n; i++)
      for (E& e : graf[i])
        if (*e.lim < e.orig)
          ret[mp(i, e.dest)] += e.orig - *e.lim;
    for (auto& i : ret) {
      const pii rev{i.st.nd, i.st.st};
      const T x = min(i.nd, ret[rev]);
      i.nd -= x;
      ret[rev] -= x;
    }
    return ret;
  }
};
