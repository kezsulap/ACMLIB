// szybkie, faktoryzuje liczby z przedzialu [1e18, 1e18 + 1e5] w 9s na cfie
namespace rho {
const int maxv = 50;
const int maxp = 1e6 + 7; // preprocesujemy rozklad do maxp - 1
int ptot;
int d[maxp];
int pr[maxp];
vector<ll> ans;  // rozklad, czyscimy zazwyczaj po kazdym wywolaniu decompose()
inline ll mod(ll a, ll n) {
  if (a >= n) a -= n;
  return a;
}
inline ll add(ll a, ll b, ll n) {
  a += b;
  mod(a, n);
  return a;
}
inline ll mul(ll x, ll y, ll p) { // uwaga, ta funkcja rzuca overflow, tak ma byc
  ll ret = x * y - (ll)((ld)x * y / p + 0.5) * p;
  return ret < 0 ? ret + p : ret;
}
ll fast(ll x, ll k, ll p) {
  ll ret = 1 % p;
  for (; k > 0; k >>= 1, x = mul(x, x, p)) (k & 1) && (ret = mul(ret, x, p));
  return ret;
}
bool rabin(ll n) {
  if (n == 2) return 1;
  if (n < 2 || !(n & 1)) return 0;
  ll s = 0, r = n - 1;
  for (; !(r & 1); r >>= 1, ++s)
    ;
  for (int i = 0; pr[i] < n && pr[i] < maxv; ++i) {
    ll cur = fast(pr[i], r, n), nxt;
    for (int j = 0; j < s; ++j) {
      nxt = mul(cur, cur, n);
      if (nxt == 1 && cur != 1 && cur != n - 1) return false;
      cur = nxt;
    }
    if (cur != 1) return false;
  }
  return true;
}
ll factor(ll n) {
  static ll seq[maxp];
  while (true) {
    ll x = rand() % n, y = x, c = rand() % n;
    ll *px = seq, *py = seq, tim = 0, prd = 1;
    while (true) {
      *py++ = y = add(mul(y, y, n), c, n);
      *py++ = y = add(mul(y, y, n), c, n);
      if ((x = *px++) == y) break;
      ll tmp = prd;
      prd = mul(prd, abs(y - x), n);
      if (!prd) return gcd(tmp, n);
      if ((++tim) == maxv) {
        if ((prd = gcd(prd, n)) > 1 && prd < n) return prd;
        tim = 0;
      }
    }
    if (tim && (prd = gcd(prd, n)) > 1 && prd < n) return prd;
  }
}
void decompose(ll n) {  // glowna funkcja
  if (n < maxp) {
    while (n > 1) ans.pb(d[n]), n /= d[n];
  } else if (rabin(n))
    ans.pb(n);
  else {
    ll fact = factor(n);
    decompose(fact), decompose(n / fact);
  }
}
void init() {  // wywolujemy przed pierwsza faktoryzacja, raz na caly program
  d[1] = 1;
  for (int i = 2; i * i < maxp; ++i)
    if (!d[i])
      for (int j = i * i; j < maxp; j += i) d[j] = i;
  for (int i = 2; i < maxp; ++i)
    if (!d[i]) {
      d[i] = i;
      pr[ptot++] = i;
    }
}
}  // namespace rho
