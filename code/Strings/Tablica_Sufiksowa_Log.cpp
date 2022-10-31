/* TABLICA SUFIKSOWA O(n*log(n)) i O(n*log^2(n)).                             */
/* Sortuje leksykograficznie wszystke sufiksy słowa.                          */
/* Dodatkowo liczy pomocnicze tablice rank i lcp.                             */
/* Wszystko indeksujemy od 1, ale podajemy wskaźnik na 0                      */

struct suffix_array {
  vector<pair<pii, int>> wek;   // do log^2
  vi ran;                       // do log
  vi ile;                       // do log
  vi kol;
  
  //n to limit na długość słowa
  suffix_array(int n) {
    wek.resize(n + 1, mp(mp(-1, -1), -1));
    ran.resize(2 * n + 1);  
    ile.resize(n + 2);
    kol.resize(n + 2);
  }

  void sa_log_2(char *tab, int n, int *sa, int *ran, int *lcp) {
    int le = 0;
    for (int i = 1; i <= n; i++)
      ran[i] = tab[i];
    for (int h = 1; h <= n; h *= 2) {
      for (int i = 1; i <= n; i++)
        wek[i].st.st = ran[i];
      for (int i = 1; i + h <= n; i++)
        wek[i].st.nd = ran[i + h];
      for (int i = n - h + 1; i <= n; i++)
        wek[i].st.nd = 0;
      for (int i = 1; i <= n; i++)
        wek[i].nd = i;
      sort(wek.begin() + 1, wek.begin() + 1 + n);
      le = 0;
      for (int i = 1; i <= n; i++) {
        if (wek[i].st != wek[i - 1].st)
          le++;
        ran[wek[i].nd] = le;
      }
    }
    for (int i = 1; i <= n; i++)
      sa[ran[i]] = i;
    le = 0;
    for (int i = 1; i <= n; i++) {
      le = max(0, le - 1);
      if (ran[i] == n) {
        lcp[n] = 0;
        continue;
      }
      while (tab[i + le] == tab[sa[ran[i] + 1] + le])
        le++;
      lcp[ran[i]] = le;
    }
  }

  inline void bucketSort(int *val, int *tab, int n) {
    for (int i = 1; i <= n; ++i) {
      ile[1 + val[i]]++;
      kol[i] = tab[i];
    }
    for (int i = 1; i <= n; ++i) ile[i] += ile[i - 1];
    for (int i = 1; i <= n; ++i) {
      tab[++ile[val[kol[i]]]] = kol[i];
    }
    fill(all(ile), 0);
  }

  void sa_log(char *tab, int n, int *sa, int *rank, int *lcp) {
    vector <int> num(256);
    for (int i = 1; i <= n; ++i) num[(int) tab[i]] = 1;
    for (int i = 1; i < 256; ++i) num[i] += num[i - 1];
    for (int i = 1; i <= n; ++i) ran[i] = num[(int) tab[i]], sa[i] = i;

    for (int len = 1; len <= n; len *= 2) {
      bucketSort(ran.data() + len, sa, n);
      bucketSort(ran.data(), sa, n);
      
      int nval = 0;
      for (int i = 1; i <= n; ++i) {
        rank[sa[i]] = nval += (i == 1 || 
        ran[sa[i]] != ran[sa[i - 1]] || 
        ran[sa[i] + len] != ran[sa[i - 1] + len]);
      }
      for (int i = 1; i <= n; ++i) ran[i] = rank[i];
      if (nval == n) break;
    }
    
    int le = 0;
    for (int i = 1; i <= n; i++) {
      le = max(0, le - 1);
      if (rank[i] == n) {
        lcp[n] = 0;
        continue;
      }
      while (i + le <= n && tab[i + le] == tab[sa[rank[i] + 1] + le]) le++;
      lcp[rank[i]] = le;
    }
  }
};
