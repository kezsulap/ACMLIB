struct Coprimes {
	vector <ll> w, dp;
	int gdz(ll v) {
		if (v<=w.back()/v)
			return v-1;
		return w.size()-w.back()/v;
	}
	ll phi(ll n) { //sum [k = 1 to n] phi(k)
		for (ll i=1; i*i<=n; i++) {
			w.push_back(i);
			if ((n/i)!=i)
				w.push_back(n/i);
		}
		sort(w.begin(), w.end());
		for (ll i : w) {
			dp.push_back(i*(i+1)/2);
			for (ll j=1; j*j<=i; j++) {
				if (i>1) dp.back()-=dp[gdz(j)]*(i/j-i/(j+1));
				if (j>1 && j<=i/(j+1)) dp.back()-=dp[gdz(i/j)];
			}
		}
		return dp.back();
	}
	ll ask(ll v) { return dp[gdz(v)]; }//v==n/u for some u
}; //phi(10 ** 10) = 2726238982321888942
