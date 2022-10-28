const int mod = 1e9 + 7; // const ll mod = (ll)1e18 + 3;
template <class c> void add_self(c & a, c b) { a += b; if(a >= mod) a -= mod; }
template <class c> void sub_self(c & a, c b) { a -= b; if(a < 0) a += mod; }
int mul(int a, int b) { return (ll) a * b % mod; }
ll mul(ll a, ll b) {return (__int128) a * b % mod; }
template <class c> c my_pow(c a, c b) {/*...*/}
template <class c> c my_inv(c a) { return my_pow<c>(a, mod - 2); }
template <class c> c negative (c a) {return (mod - a) % mod;}
template <class F> struct Massey {
	vector<F> start, coef; // 3 optional lines
	vector<vector<F>> powers;
	F memo_inv;
	// Start here and write the next ~25 lines until "STOP"
	int L; // L == coef.size() <= start.size()
	Massey(vector<F> in) { // O(N^2)
		L = 0;
		const int N = in.size();
		vector<F> C{1}, B{1};
		for(int n = 0; n < N; ++n) {
			// assert(0 <= in[n] && in[n] < mod); // invalid input
			B.insert(B.begin(), 0);
			F d = 0;
			for(int i = 0; i <= L; ++i)
				add_self(d, mul(C[i], in[n-i]));
			if(d == 0) continue;
			vector<F> T = C;
			C.resize(max(B.size(), C.size()));
			for(int i = 0; i < (int) B.size(); ++i)
				sub_self(C[i], mul(d, B[i]));
			if(2 * L <= n) {
				L = n + 1 - L;
				B = T;
				d = my_inv(d);
				for(F & x : B) x = mul(x, d);
			}
		}
		cerr << "L = " << L << "\n";
		assert(2 * L <= N - 2); // NO RELATION FOUND :(
		// === STOP ===
		for(int i = 1; i < (int) C.size(); ++i)
			coef.push_back(negative(C[i]));
		assert((int) coef.size() == L);
		for(int i = 0; i < L; ++i)
			start.push_back(in[i]);
		while(!coef.empty() && coef.back() == 0) { coef.pop_back(); --L; }
		if(!coef.empty()) memo_inv = my_inv(coef.back());
		powers.push_back(coef);
	}
	vector<F> mul_cut(vector<F> a, vector<F> b) {
		vector<F> r(2 * L - 1);
		for(int i = 0; i < L; ++i)
			for(int j = 0; j < L; ++j)
				add_self(r[i+j], mul(a[i], b[j]));
		while((int) r.size() > L) {
			F value = mul(r.back(), memo_inv); // div(r.back(), coef.back());
			const int X = r.size();
			add_self(r[X-L-1], value);
			for(int i = 0; i < L; ++i)
				sub_self(r[X-L+i], mul(value, coef[i]));
			assert(r.back() == 0);
			r.pop_back();
		}
		return r;
	}
	F get(ll k) { // O(L^2 * log(k))
		if(k < (int) start.size()) return start[k];
		if(L == 0) return 0;
		k -= start.size();
		vector<F> vec = coef;
		for(int i = 0; (1LL << i) <= k; ++i) {
			if(i == (int) powers.size())
				powers.push_back(mul_cut(powers.back(), powers.back()));
			if(k & (1LL << i))
				vec = mul_cut(vec, powers[i]);
		}
		F total = 0;
		for(int i = 0; i < L; ++i)
			add_self(total, mul(vec[i], start[(int)start.size()-1-i]));
		return total; } };
