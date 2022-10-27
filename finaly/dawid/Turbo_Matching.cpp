struct matching {
  int n;
  vector<vi> V;
  vector<bool> odw;
  vi para, strona;
  matching(int _n) : n(_n) { // zakladam numeracje od 1, nie moze byc 0
    V.resize(n + 1);
    odw.resize(n + 1);
    para.resize(n + 1);
  }
  void addedge(int a, int b) { // zakladam ze a jest z lewej, b z prawej
    V[a].pb(b);
    strona.pb(a);
  }
  bool skojarz(int x) { // x nalezy do strona
    odw[x] = 1;
    for (auto v : V[x]) {
      if (!para[v] || (!odw[para[v]] && skojarz(para[v]))) {
        para[v] = x;
        para[x] = v;
        return 1;
    } }
    return 0;
  }
  vpii go() {
    sort(all(strona));
    strona.resize(unique(all(strona)) - strona.begin());
    for (int i = 1; i <= n; ++i)
      shuffle(all(V[i]), default_random_engine(2137));
    sort(all(strona), [&](int a, int b){return siz(V[a]) < siz(V[b]);});
    bool ok = 0;
    do {
      ok = 0;
      for (auto i : strona) odw[i] = 0;
      for (auto i : strona)
        if (!para[i] && skojarz(i))
          ok = 1;
    } while (ok);
    vpii res;
    for (auto i : strona)
      if (para[i])
        res.pb(mp(i, para[i]));
    return res;
} };