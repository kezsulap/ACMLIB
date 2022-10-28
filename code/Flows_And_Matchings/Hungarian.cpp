//a[1..n][1..m] - wagi, n<=m, O(n^2*m), znajduje minimalny koszt (masymalny: *-1)
//u[0..n], v[0..m] - funkcja potencjalu, p[0..m], ans[0..n] - skojarzenie
struct hungarian { // cost = -v[0]
  int n, m;
  vector<vi> a;
  vi u, v, p, way, ans;
  hungarian(int _n, int _m) : n(_n), m(_m) {
    #define re(x, y) (x).resize(y + 1)
    re(a, n); re(u, n); re(v, m); re(p, m); re(way, m), re(ans, n);
    for (auto &x : a) re(x, m);
  }
  void addcost(int v1, int v2, int c) {
    a[v1][v2] = c;
  }
  void solve() {
    for(int i = 1; i <= n; ++i) {
      p[0] = i;
      int j0 = 0;
      vi minv(m + 1, INT_MAX); // uwaga, moze byc potrzebny LL!
      vector<char> used(m + 1, false);
      do {
        used[j0] = true;
        int i0 = p[j0], delta = INT_MAX, j1 = 0;
        for (int j = 1; j <= m; ++j) {
          if (!used[j]) {
            int cur = a[i0][j] - u[i0] - v[j];
            if (cur < minv[j]) {
              minv[j] = cur;
              way[j] = j0;
            }
            if (minv[j] < delta) {
              delta = minv[j];
              j1 = j;
        } } }
        for (int j = 0; j <= m; ++j) {
          if (used[j]) {
            u[p[j]] += delta;
            v[j] -= delta;
          }
          else {
            minv[j] -= delta;
        } }
        j0 = j1;
      } while (p[j0] != 0);
      do {
        int j1 = way[j0];
        p[j0] = p[j1];
        j0 = j1;
      } while (j0);
    }
    for (int j = 1; j <= m; ++j)
      ans[p[j]] = j; // odzyskiwanie wyniku
  }
};