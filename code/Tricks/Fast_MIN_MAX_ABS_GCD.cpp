#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int FastMax(int x, int y) { return x - y >> 31 & (x ^ y) ^ x; }
int FastMin(int x, int y) { return x - y >> 31 & (x ^ y) ^ y; }
// Działa dla wszystkich x oprócz -2**31 (bo 2**31 się nie mieści w typie int).
int FastAbs(int x)        { return (x ^ x >> 31) - (x >> 31); }
int FastGCD(int a, int b) {
	int r = 0;
	while (a && b) {
		int x = __builtin_ctz(a);
		int y = __builtin_ctz(b);
		int z = FastMin(x, y);
		r += z;
		a >>= x;
		b >>= y;
		int c = FastAbs(a - b);
		a = FastMin(a, b);
		b = c;
	}
	return (a + b) << r;
}

static uint64_t splitmix64(uint64_t x) {
  x += 0x9e3779b97f4a7c15;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return x ^ (x >> 31);
}
int main() {
	ll ans = 0;
	uint64_t v = splitmix64(0);
	const int M = (1 << 30) - 1;
	for (int i = 0; i < 10000000; ++i) {
		int a = v & M;
		v = splitmix64(v);
		int b = v & M;
		v = splitmix64(v);
		ans ^= FastGCD(a, b);
	}
	printf("%lld\n", ans);
}
