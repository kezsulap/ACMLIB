#include<ext/pb_ds/assoc_container.hpp> // ordered set
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; template <typename T> using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
ordered_set<int> s; s.insert(1); s.insert(2);
 s.order_of_key(1);   // Out: 0.
*s.find_by_order(1);  // Out: 2.
// unordered_map hash.
struct MyHash { std::size_t operator()(const MojTyp& x) { /* ... */ } };
bool operator==(const MojTyp& a, const MojType& b) { /* ... */ }
std::unordered_set<MojTyp, MyHash> secik;
// Find first / find next on bitset.
for (int pos = bs._Find_first(); pos != bs.size(); pos = bs._Find_next(pos))
  { /* Something with @pos. */ }
// Ratio liczba_elementów / liczba bucketów, domyślnie 1.0 (ustaw na INF, jeśli
secik.max_load_factor(0.25);  // chcesz używać tylko reserve).
// Maksuje liczbę bucketów do danej liczby, zalecana potęga 2,
secik.reserve(1<<15);  // np. (1 << 22) dla n = 1e6.
int secik.bucket_count(); // Zwraca obecna liczbe bucketow, sluzy do testowania.
// limit_denominator
import fractions
a = fractions.Fraction(3.141592).limit_denominator(7)  // a = Fraction(22, 7)
print(a.numerator, a.denominator)
// Zwraca (a * b) % (2**p - 1).
ull Mnoz(ull a, ull b) {
  constexpr int p = 61;
  constexpr ull mod = (1llu << p) - 1;
  const auto A = (__uint128_t) a * b;
  ull result = (ull) (A & mod) + (ull) (A >> p);
  if (mod <= result) {
    result -= mod;
  }
  return result;
}
// Szybsza unordered_mapa
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
sim, class m> using my_unordered_map = cc_hash_table<c, m, hash<c>>; // lub
gp_hash_table<int, int> mapka;
// Dobre hasze
static uint64_t splitmix64(uint64_t x) {
  x += 0x9e3779b97f4a7c15;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return x ^ (x >> 31);
}
// Działa dla wszystkich par (x, y), dla których (x - y) mieści się w typie int.
int FastMax(int x, int y) { return x - y >> 31 & (x ^ y) ^ x; }
int FastMin(int x, int y) { return x - y >> 31 & (x ^ y) ^ y; }
// Działa dla wszystkich x oprócz -2**31 (bo 2**31 się nie mieści w typie int).
int FastAbs(int x)        { return (x ^ x >> 31) - (x >> 31); }
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
using unt = unsigned int;
inline unt ros(unt m) {//Kolejna maska mająca tyle samo zapalonych bitów
	unt a = m & -m;
	unt b = ~((a - 1) ^ m);
	unt c = b & -b;
	unt d = (c >> (1 + __builtin_ctz(a))) - 1;
	return c | (m & ~(c - 1)) | d;
}
