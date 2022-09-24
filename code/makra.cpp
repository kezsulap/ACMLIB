#ifndef LOCAL
#pragma GCC optimize ("O3")
#endif
#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define endl '\n'
#define siz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()
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
	a << "(";
	apply([&](c...y){
		((*this << ", " + 2 * !q++ << y), ...);
	}, x);
	ris << ")";
}
#define qel(t) sim, class d, class...e mor t<c,d,e...> x){ris << *(d*)&x;}
qel(stack) qel(queue) qel(priority_queue)
#else
sim mor const c&) { ris; }
#endif
};
#define imie(r...) "[" #r ": " << (r) << "] "
#define range(b, e) "[[" #b ", " #e "): " << range(b, e) << "] "
#define imask(r...) "[" #r ": " << bitset<8 * sizeof(r)>(r) << "] "
#define arr(a, i) "[" #a imie(i) ": " << a[i] << "] "
#define arr2(a, i, j) "[" #a imie(i) imie(j) ": " << a[i][j] << "] "
#define arr3(a, i, j, k) "[" #a imie(i) imie(j) imie(k) ": " << a[i][j][k] << "] "
#define arr4(a, i, j, k, x) "[" #a imie(i) imie(j) imie(k) imie(x) ": " << a[i][j][k][x] << "] "
#define fun(f, x...) "[" #f << make_tuple(x) << ": " << f(x) << "] "
#define debug muu() << __FUNCTION__ << "#" << __LINE__ << ": "
using ll = long long; using ld = long double; using pii = pair <int, int>; using vi = vector <int>;
using vpii = vector<pii>; using ull = unsigned long long; using unt = unsigned int; using pdd = pair <ld, ld>;
using pll = pair <ll, ll>; using vll = vector <ll>; using mii = map <int, int>;
sim> void mini(c &a, const c &b) {if (a > b) a = b;} sim> void maxi(c &a, const c &b) {if (a < b) a = b;}

int32_t main() {
	// ios_base::sync_with_stdio(0);
	// cin.tie(0);
}

// struct foo {int a, int b};
// muu &operator<<(muu &d, const foo &f) {
	// return d << "foo(" << f.a << ", " << f.b << ")";
// }
// int main() {
	// vector <pair <int, int> > a = {{1, 2}, {2, 3}, {3, 4}};
	// int b = 2;
	// debug imie(a) imask(10) arr(a, b) fun(atan2, 1, 3) range(a.begin(), a.begin() + 2);
// }
