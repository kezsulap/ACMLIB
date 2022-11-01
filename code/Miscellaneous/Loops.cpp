sim> bool next_inc(c beg, c end, int bou) { //[0, bou)
	for (c i = end; i != beg;) {
		int v = *--i;
		if (v + 1 < bou) {
			iota(i, end, v + 1);
			return true;
		}
		bou = *i;
	}
	return false;
}
sim> bool next_nondec(c beg, c end, int bou) {//[0, bou)
	for (c i = end; i != beg;) {
		int v = *--i;
		if (v + 1 < bou) {
			fill(i, end, v + 1);
			return true;
		}
	}
	return false;
}
sim> bool next_any(c beg, c end, int bou) {
	if (!bou) return false;
	for (c i = end; i != beg;) {
		if (++*--i == bou) *i = 0;
		else return true;
	}
	return false;
}
sim>bool next_diff(c beg,c end,int bou){//starts with 0,1,2...
	return next_permutation(beg, end) || next_inc(beg, end, bou);
}
sim>bool next_split(c beg, c end) {//starts with all 0s, ends with 0,1,2...
	vector <int> seen(distance(beg, end));
	for (c i = beg; i != end; ++i) seen[*i]++;
	for (c i = end; i != beg;) {
		if (seen[*--i] > 1) {
			(*i)++;
			fill(++i, end, 0);
			return true;
		}
	}
	return false;
}
//for (int m = (1 << k) - 1; m < (1 << n); m = nux(m)) - k-podzbiory [0,n)
sim>inline c nux(c m){
	if (!m) return numeric_limits<c>::max();
	c A = m & -m;
	c B = ~((A - 1) ^ m);
	c C = B & -B;
	c D = (C >> (1 + ctz(A)))-1;
	return C | (m & ~(C - 1)) | D;
}
//for (unt i = 0; i < (1u << n); i = rrh(i)) maska bez sąsiednich zapalonych, rosnąco
sim> inline c rrh(c m) {
	c a = ~(m | m >> 1);
	c b = a & -a;
	return (m | b) &~ (b - 1);
}
//for (unt i = (1u << (n + 1)) / 3; ~i; i = lyl(i)) maska bez sąsiednich, malejąco
sim> inline c lyl(c m) {
	if (!m) return -1;
	c x = m & -m;
	return (m ^ x) | ((x << 1) / 3);
}
for (ll val = 1, low = n / 2, high = n; ; val = n / low, high = low, low = n / (val + 1)) {
	//include n / i = val for i in (low, high]
	if (val == n) break;
}
