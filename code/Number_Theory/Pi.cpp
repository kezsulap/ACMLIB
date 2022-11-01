struct Primes {//Pi(10^10) = 455052511
	vector <ll> w, dp;
	int gdz(ll v) {
		if (v <= w.back() / v) return v - 1;
		return w.size() - w.back() / v;
	}
	ll pi(ll n) {
		for (ll i = 1; i * i <= n; i++) {
			w.pb(i);
			if (n / i != i) w.push_back(n/i);
		}
		sort(all(w));
		for (ll i : w) dp.push_back(i-1);
		for (ll i = 1; (i + 1) * (i + 1) <= n; i++) {
			if (dp[i] == dp[i - 1]) //Might not work when calculating modulo or sum of
				continue; //some weird function over primes, meant to skip if i + 1 is not prime
			for (int j = siz(w) - 1; w[j] >= (i + 1) * (i + 1); j--)
				dp[j] -= dp[gdz(w[j] / (i + 1))] - dp[i - 1];
		}
		return dp.back();
	}
	ll ask(ll v) { return dp[gdz(v)]; }//Działa tylko jak v==n/u for some u
}; //Sum upto(10^10) mod 1e9+7 = 35972319
