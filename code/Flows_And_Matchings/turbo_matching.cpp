struct matching {
  int n;
  vector<VI> V;
  vector<bool> odw;
  VI para, strona;
  matching(int _n) : n(_n) { // zakładam numeracje od 1, nie może być 0
    V.resize(n + 1);
    odw.resize(n + 1);
    para.resize(n + 1);
  }
  void addedge(int a, int b) { // zakładam że a jest z lewej, b z prawej
    V[a].PB(b);
    strona.PB(a);
  }
  bool skojarz(int x) { // x należy do strona
    odw[x] = 1;
    for (auto v : V[x]) {
      if (!para[v] || (!odw[para[v]] && skojarz(para[v]))) {
        para[v] = x;
        para[x] = v;
        return 1;
    } }
    return 0;
  }
  VPII go() {
    sort(ALL(strona));
    strona.resize(unique(ALL(strona)) - strona.begin());
    REP(i, n + 1)
      random_shuffle(ALL(V[i]));
    sort(ALL(strona), [&](int a, int b){return V[a].size() < V[b].size();});
    bool ok = 0;
    do {
      ok = 0;
      for (auto i : strona) odw[i] = 0;
      for (auto i : strona)
        if (!para[i] && skojarz(i))
          ok = 1;
    } while (ok);
    VPII res;
    for (auto i : strona)
      if (para[i])
        res.PB(MP(i, para[i]));
    return res;
} };
