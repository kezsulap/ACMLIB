struct Matching {
	int n, tim = 0, top = 0;
	vi mat, fa, s, q, pre, vis, head;
	vpii e;
	Matching(int N) : n(N + 1), mat(n, -1), fa(n), s(n), q(n), pre(n), vis(n),
		head(n, -1) {}
	void edge_impl(int x, int y) {e.eb(y, head[x]);head[x] = siz(e) - 1;}
	void add_edge(int x, int y) {edge_impl(x, y), edge_impl(y, x);}
	int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
	int lca(int x, int y) {
		for (++tim, x = find(x), y = find(y); ; swap(x, y)) {
			if (~x) {
				if (vis[x] == tim) return x;
				vis[x] = tim;
				x = ~mat[x] ? find(pre[mat[x]]) : -1;
			}
		}
	}
	void blossom(int x, int y, int l) {
		while (find(x) != l) {
			pre[x] = y;
			if (s[mat[x]] == 1) s[q[top++] = mat[x]] = 0;
			if (fa[x] == x) fa[x] = l;
			if (fa[mat[x]] == mat[x]) fa[mat[x]] = l;
			y = mat[x];
			x = pre[y];
		}
	}
	bool match(int x) {
		iota(all(fa), 0);
		fill(all(s), -1);
		s[q[0] = x] = 0;
		top = 1;
		for (int i = 0; i < top; ++i) {
			for (int t = head[q[i]]; ~t; t = e[t].nd) {
				int y = e[t].st;
				if (s[y] == -1) {
					pre[y] = q[i];
					s[y] = 1;
					if (mat[y] == -1) {
						for (int u = y, v = q[i], lst; ~v; u = lst, v = ~u ? pre[u] : -1)
							lst = mat[v], mat[v] = u, mat[u] = v;
						return true;
					}
					s[q[top++] = mat[y]] = 0;
				}
				else if (!s[y] && find(y) != find(q[i])) {
					int l = lca(y, q[i]);
					blossom(y, q[i], l);
					blossom(q[i], y, l);
				}
			}
		}
		return false;
	}
	int run() {
		int size = 0;
		for (int i = 0; i < n; ++i)
			if (mat[i] == -1 && match(i))
				size++;
		return size;
	}
};
