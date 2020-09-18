#ifndef LOCAL
#pragma GCC optimize ("O3")
#endif
#include <bits/stdc++.h>
using namespace std;
#define sim template < class c
#define ris return * this
#define mor > muu & operator << (
#define R22(r) sim > typename \
  enable_if<1 r sizeof dud<c>(0), muu&>::type operator<<(c g) {
sim > struct rge { c b, e; };
sim > rge<c> range(c b, c e) { return {b, e}; }
sim > auto dud(c* r) -> decltype(cerr << *r);
sim > char dud(...);
struct muu {
#ifdef LOCAL
stringstream a;
~muu() { cerr << a.str() << endl; }
R22(<) a << boolalpha << g; ris; }
R22(==) ris << range(begin(g), end(g)); }
sim, class b mor pair < b, c > r) { ris << "(" << r.first << ", " << r.second << ")"; }
sim mor rge<c> u) {
  a << "[";
  for (c i = u.b; i != u.e; ++i)
    *this << ", " + 2 * (i == u.b) << *i;
  ris << "]";
}
template <class...c mor tuple<c...> x) {//Wymaga kompilowania lokalnie z -std=c++1z
	int q = 0;
	a << "[";
	apply([&](c...y){
		((*this << ", " + 2 * !q++ << y), ...);
	}, x);
	ris << "]";
}
#define qel(t) sim, class d, class...e mor t<c,d,e...> x){ris << *(d*)&x;}
qel(stack) qel(queue) qel(priority_queue)
#else
sim mor const c&) { ris; }
#endif
};
#define imie(r...) "[" #r ": " << (r) << "] "
#define imask(r...) "[" #r ": " << bitset<8 * sizeof(r)>(r) << "] "
#define arr(a, i) "[" #a imie(i) ": " << a[i] << "] "
#define arr2(a, i, j) "[" #a imie(i) imie(j) ": " << a[i][j] << "] "
#define debug muu() << __FUNCTION__ << "#" << __LINE__ << ": "
