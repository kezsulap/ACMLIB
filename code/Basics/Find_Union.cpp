struct FU {
	vi u;
	FU(int n) : u(n + 1) {iota(u.begin(), u.end(), 0);}
	int find(int x) {
		if (u[x] == x) return x;
		return u[x] = find(u[x]);
	}
	void onion(int a, int b) {
		u[find(a)] = find(b);
	}
};
