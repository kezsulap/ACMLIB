const int mod = 119 << 23 | 1, nax = 1e5 + 44;
ll powe(ll b, ll e) {
	ll r = 1;
	while (e) {
		if (e & 1) r = r * b % mod;
		b = b * b % mod;
		e >>= 1;
	}
	return r;
}
ll inv(ll x) {
	assert(x);
	return powe(x, mod - 2);
}
ll fac[nax], fin[nax];
void mod_init() {
	fac[0] = 1;
	for (int i = 1; i < nax; ++i) fac[i] = fac[i - 1] * i % mod;
	fin[nax - 1] = inv(fac[nax - 1]);
	for (int i = nax - 2; i >= 0; --i) fin[i] = fin[i + 1] * (i + 1) % mod;
}
ll cho(int a, int b) {
	if (b < 0 || b > a) return 0;
	return fac[a] * fin[b] % mod * fin[a - b] % mod;
}
