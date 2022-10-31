struct suffix_automaton {
	vector<map<char,int>> edges;
	vi link, length;
	int last;
	suffix_automaton(string s) {
		edges.pb(map<char,int>());
		link.pb(-1);
		length.pb(0);
		last = 0;
		for (int i=0; i<siz(s); i++) {
			edges.pb(map<char,int>());
			length.pb(i+1);
			link.pb(0);
			int r = siz(edges) - 1;
			int p = last;
			while (p >= 0 && !edges[p].count(s[i])) {
				edges[p][s[i]] = r;
				p = link[p];
			}
			if (p != -1) {
				int q = edges[p][s[i]];
				if (length[p] + 1 == length[q]) {
					link[r] = q;
				}
				else {
					edges.pb(edges[q]);
					length.pb(length[p] + 1);
					link.pb(link[q]);
					int qq = siz(edges)-1;
					link[q] = link[r] = qq;
					while (p >= 0 && edges[p][s[i]] == q) {
						edges[p][s[i]] = qq;
						p = link[p];
					}
				}
			}
			last = r;
		}
	}
};
