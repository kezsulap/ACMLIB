#define REP(i,n) for(int i = 0; i < int(n); ++i)
/*Precision error max_ans/1e15 (2.5e18) for (long) doubles.
So integer rounding works for doubles with answers 0.5*1e15,
e.g. for sizes 2^20 and RANDOM positive integers up to 45k.
Those values assume DBL_MANT_DIG=53 and LDBL_MANT_DIG=64.
For input in [0, M], you can decrease everything by M/2.
If there are many small vectors, uncomment "BRUTE FORCE".*/
typedef double ld; // 'long double' is 2.2 times slower
struct C {
	ld real, imag;
	C operator * (const C & he) const {
		return C{real * he.real - imag * he.imag, real * he.imag + imag * he.real};
	}
	void operator += (const C & he) {real += he.real; imag += he.imag;} };
void dft(vector<C> & a, bool rev) {
	const int n = a.size();
	for(int i = 1, k = 0; i < n; ++i) {
		for(int bit = n / 2; (k ^= bit) < bit; bit /= 2);;;
		if(i < k) swap(a[i], a[k]);
	}
	for(int len = 1, who = 0; len < n; len *= 2, ++who) {
		static vector<C> t[30];
		vector<C> & om = t[who];
		if(om.empty()) {
			om.resize(len);
			const ld ang = 2 * acosl(0) / len;
			REP(i, len) om[i] = i%2 || !who?C{cos(i*ang), sin(i*ang)}:t[who-1][i/2];
		}
		for(int i = 0; i < n; i += 2 * len)
			REP(k, len) {
				 const C x = a[i+k], y = a[i+k+len]
						* C{om[k].real, om[k].imag * (rev ? -1 : 1)};
				a[i+k] += y;
				a[i+k+len] = C{x.real - y.real, x.imag - y.imag};
			}
	}
	if(rev) REP(i, n) a[i].real /= n;
}
template<typename T>vector<T> multiply(const vector<T> &a, const vector<T> &b, bool split = false) {
	if(a.empty() || b.empty()) return {};
	int n = a.size() + b.size();
	vector<T> ans(n - 1);
	/* if(min(a.size(),b.size()) < 190) { // BRUTE FORCE
		REP(i, a.size()) REP(j, b.size()) ans[i+j] += a[i]*b[j];
		return ans; } */
	while(n&(n-1)) ++n;
	auto speed = [&](const vector<C> & w, int i, int k) {
		int j = i ? n - i : 0, r = k ? -1 : 1;
		return C{w[i].real + w[j].real * r, w[i].imag
				- w[j].imag * r} * (k ? C{0, -0.5} : C{0.5, 0});
	};
	if(!split) { // standard fast version
		vector<C> in(n), done(n);
		REP(i, a.size()) in[i].real = a[i];
		REP(i, b.size()) in[i].imag = b[i];
		dft(in, false);
		REP(i, n) done[i] = speed(in, i, 0) * speed(in, i, 1);
		dft(done, true);
		REP(i, ans.size()) ans[i] = is_integral<T>::value ?
				llround(done[i].real) : done[i].real;
	}
	else {
		const int M = 1 << 15;
		vector <C> t[2];
		for (int x = 0; x < 2; ++x) {
			t[x].resize(n);
			const vector <T> & in = (x ? b : a);
			for (int i = 0; i < (int) in.size(); ++i)
				t[x][i] = C{ld(in[i] % M), ld(in[i] / M)};
			dft(t[x], false);
		}
		vector <C> d1(n), d2(n);
		for (int i = 0; i < n; ++i) {
			d1[i] += speed(t[0], i, 0) * speed(t[1], i, 0);
			d1[i] += speed(t[0], i, 1) * speed(t[1], i, 1) * C{0, 1};
			d2[i] += speed(t[0], i, 0) * speed(t[1], i, 1);
			d2[i] += speed(t[0], i, 1) * speed(t[1], i, 0);
		}
		dft(d1, true);
		dft(d2, true);
		for (int i = 0; i < n; ++i)
			d1[i].imag /= n;
		for (int i = 0; i < (int) ans.size(); ++i)
			ans[i] = (llround(d1[i].real) + llround(d2[i].real) % mod * M + llround(d1[i].imag) % mod * (M * M)) % mod;
	}
	return ans;
}
