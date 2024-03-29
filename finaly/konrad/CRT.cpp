void eukl(ll &x, ll &y, ll a, ll b) {
	if (!a) { x = 0; y = 1; return; }
	eukl(y, x, b % a, a);
	x -= y * (b / a);
}
ll mno(ll a, ll b, ll mod) {/*...*/}
pll crt2(ll p, ll a, ll q, ll b) { //x==p(mod a),x==q(mod b)
	if (a==-1) return {-1, -1};// Zarówno wynik, jak i argumenty są
	ll x, y;                 // postaci x = first (mod second).
	eukl(x, y, a, b);        // Jeśli kongruencja jest niespełnialna
	ll nwd=x*a+y*b;          // to zwraca (-1, -1).
	if ((p%nwd)!=(q%nwd))
		return {-1, -1};
	a/=nwd; b/=nwd;
	ll nww=a*b;
	ll ret=mno(x*a, q/nwd, nww)+mno(y*b, p/nwd, nww);
	if ((ret%=nww)<0) ret+=nww;
	return {ret*nwd+(p%nwd), nww*nwd};
}
