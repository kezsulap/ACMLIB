#include "Dinic.cpp"
struct GomoryHu { // #define int ll//jeśli long longi potrzebne
  vector<vpii> graph, tree;
  vector<vi> nodes;
  vector<bool> visited;            //wymaga naszego dinica
  vi groupId, contrId;             //numeracja od zera
  int wnode, n;
  GomoryHu(int N) : graph(N), visited(N), groupId(N), contrId(N), tree(N), n(N) {}
  void addEdge(int u, int v, int cap) {
    graph[u].eb(v, cap);
    graph[v].eb(u, cap);
  }
  void dfs(int v, int type) {
    visited[v] = true; contrId[v] = type;
    for (auto P : tree[v]) { if (!visited[P.st]) { dfs(P.st, type); } }
  }
  vector <pair<pii,int>> run() {
    vi allNodes(n);
    iota(all(allNodes), 0);
    nodes = vector<vi>{allNodes};
    tree = vector<vpii>(n);
    fill(all(groupId), 0);
    for (int step = 1; step < n; step++) {
      Flow flow;
      for (int i = 0; i < siz(nodes); i++) {
        if (siz(nodes[i]) > 1) { wnode = i; break; }
      }
      fill(all(visited), false);
      visited[wnode] = true;
      for (auto P : tree[wnode]) { dfs(P.st, nodes[P.st][0]); }
      for (int v = 0; v < n; v++) {
        int a = groupId[v] == wnode ? v : contrId[groupId[v]];
        for (auto& P : graph[v]) {
          int b = groupId[P.st] == wnode ? P.st : contrId[groupId[P.st]];
          if (a != b) { flow.add_edge(a, b, P.nd); }
        }
      }
      int a = nodes[wnode][0], b = nodes[wnode][1], f = flow.dinic(a, b);
      auto pom = flow.cut();
      vector <bool> cut(n, false);
      for (int i : pom)
        cut[i]=1;
      for (int v = 0; v < step; v++) {
        if (v == wnode) { continue; }
        for (auto& P : tree[v]) {
          if (P.st == wnode && !cut[contrId[v]]) { P.st = step; }
        }
      }
      vpii PA, PB;
      for (auto& P : tree[wnode]) { (cut[contrId[P.st]] ? PA : PB).pb(P); }
      tree[wnode] = PA; tree[step] = PB;
      tree[wnode].eb(step, f);
      tree[step].eb(wnode, f);
      vi A, B;
      for (int v : nodes[wnode]) {
        (cut[v] ? A : B).pb(v);
        if (!cut[v]) { groupId[v] = step; }
      }
      nodes[wnode] = A;
      nodes.pb(B);
    }
    vector <pair<pii,int>> res;
    for (int i = 0; i < n; i++)
      for (auto P : tree[i])
        if (nodes[i][0]<nodes[P.st][0])
          res.pb({{nodes[i][0], nodes[P.st][0]}, P.nd});
    return res;
  }
}; // #undef int
