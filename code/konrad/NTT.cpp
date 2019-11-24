#define rep(i,n) for(int i = 0; i < int(n); ++i)
const ll mod = 998244353, omega = 31, deg = 23; //ord(omega) mod = 2^deg
//const ll mod = 27ll << 56 | 1, omega = 11, deg = 56;
//const ll mod = 65537, omega = 3, deg = 16;
#define rep(i,n) for(int i = 0; i < int(n); ++i)
ll powe(ll b, ll e) {
	ll r = 1;
	while (e) {
		if (e & 1) r = r * b % mod;
		b = b * b % mod;
		e >>= 1;
	}
	return r;
}
//rev = false: evaluate at powers of omega ^ (2^deg / n)
//rev = true: interpolate
void dft(vector<ll> & a, bool rev) {
	assert(a.size() <= 1llu << deg);
	const int n = a.size();
	for(int i = 1, k = 0; i < n; ++i) {
		for(int bit = n / 2; (k ^= bit) < bit; bit /= 2);;;
		if(i < k) swap(a[i], a[k]);
	}
	for(int len = 1, who = 0; len < n; len *= 2, ++who) {
		static vector<ll> t[30] = {{1, mod - 1}};
		vector<ll> & om = t[who];
		if(om.empty()) {
			om.resize(len + 1);
			ll eps = powe(omega, 1 << (deg - who - 1));
			om[0] = 1;
			om[1] = eps;
			for (int i = 2; i <= len; ++i) om[i] = i%2 ?
				om[i - 1] * eps % mod : t[who-1][i/2];
		}
		for(int i = 0; i < n; i += 2 * len)
			rep(k, len) {
				const ll x = a[i+k], y = a[i+k+len] * (rev ? mod - om[len - k] : om[k]) % mod;
				a[i+k] += y;
				if (a[i + k] >= mod) a[i + k] -= mod;
				a[i+k+len] = x - y;
				if (a[i + k + len] < 0) a[i + k + len] += mod;
			}
	}
	if (rev) {
		int r = __builtin_ctz(n);
		for (int i = 0; i < n; ++i) for (int j = 0; j < r; ++j) {
			if (a[i] % 2) a[i] += mod;
			a[i] /= 2;
		}
	}
}
vector <ll> mul(vector <ll> a, vector <ll> b) {
	int ret_size = a.size() + b.size() - 1;
	vector <ll> ans(a.size() + b.size() - 1);
	int n = a.size() + b.size();
	while (n & (n - 1)) n++;
	a.resize(n);
	b.resize(n);
	dft(a, false);
	dft(b, false);
	for (int i = 0; i < n; ++i) a[i] = a[i] * b[i] % mod;
	dft(a, true);
	a.resize(ret_size);
	return a;
}

