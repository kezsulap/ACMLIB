//Mnożenie long longów modulo (jak nie ma __int128)
//zakłada, że |a|, |b| < m
//dla m <= 1e12: float
//dla m <= 1e17: double
//dla m > 1e17: long double
using ll = long long;
ll __attribute__ ((no_sanitize_undefined)) mul(ll a,ll b, ll m) {
	ll q = ((double)a * b / m);
	ll r = (a*b - q*m) % m;  //ma się przekręcać
	if (r < 0)
		r += m;
	return r;
}
