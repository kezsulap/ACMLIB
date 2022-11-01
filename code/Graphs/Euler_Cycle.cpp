vi ans;
set<int> S[N];
void rec(int v) { 
  while(!S[v].empty()) {
    auto u = *S[v].begin();
    S[v].erase(u);
    S[u].erase(v);
    rec(u);
    ans.pb(v);
  }
}
void eul() {
  vi deg;
  for(int i = 1; i <= n; ++i) if(S[i].size() % 2) deg.pb(i);
  if (siz(deg) == 0) {
    ans.pb(1);
    rec(1);
  } else if (siz(deg) == 2) {
    sort(all(deg));
    rec(deg[0]);
    reverse(all(ans));
    ans.pb(deg[1]); 
  } else assert(0); //Cycle doesn't exist
}

