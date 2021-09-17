#ifdef LOCAL 
#define loc(r...) r
#else
#define loc(...)
#endif
struct zet_p {
	int v;
	loc(long double w;)
	sim = int> zet_p(c r = 0) : v(r % mod) loc(, w(r)) {}
	loc(sim> zet_p(c a, long double b) : v(a % mod), w(b) {})
	#define rer(o, f) zet_p operator o (zet_p y) {return zet_p(v f loc(, w o y.w));} \
		zet_p & operator o##=(zet_p y) {ris = *this o y;}
	rer(+, +y.v) rer(-, -y.v) rer(*, * 1ll * y.v) rer(/, * inv(y.v))
	int get() {return ((unsigned int)v + mod) % mod;}
	zet_p operator-(){return zet_p(-v loc(, -w));}
	bool operator==(zet_p y) {return (v - y.v) % mod == 0;}
};
#define ccy(o) sim> zet_p operator o(c a, zet_p b) {return zet_p(a) o b;}
ccy(+) ccy(-) ccy(*) ccy(/)
sim> bool operator == (c a, zet_p b) {return zet_p(a) == b;}
loc(muu & operator<<(muu & d, zet_p y) {return d << "<" << y.get() << "=" << y.w << ">";})
