sim> bool next_inc(c beg, c end, int bou) {
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
sim> bool next_nondec(c beg, c end, int bou) {
	bou--;
	for (c i = end; i != beg;) {
		int v = *--i;
		if (v < bou) {
			fill(i, end, v + 1);
			return true;
		}
	}
	return false;
}
sim> bool next_any(c beg, c end, int bou) {
	if (!bou) return false;
	for (c i = end; i != beg;) {
		++*--i;
		if (*i == bou) *i = 0;
		else return true;
	}
	return false;
}
sim> bool next_diff(c beg, c end, int bou) {
	return next_permutation(beg, end) || next_inc(beg, end, bou);
}
sim> bool next_split(c beg, c end) {
	int n = distance(beg, end);
	vector <int> seen(n);
	for (c i = beg; i != end; ++i) seen[*i]++;
	for (c i = end; i != beg;) {
		--i;
		if (--seen[*i]) {
			(*i)++;
			i++;
			fill(i, end, 0);
			return true;
		}
	}
	return false;
}
#define INCS__(b, e, v) for (int ___ = (v),_ = distance(b, e) <= ___, __ = 1; _ && (__ ? (iota(b, e, 0), 1) : next_inc(b, e, ___)); __ = 0)
#define DIFFS__(b, e, v) for (int ___ = (v), _ = distance(b, e) <= ___, __ = 1; _ && (__ ? (iota(b, e, 0), 1) : next_diff(b, e, ___)); __ = 0)
#define NONDECS__(b, e, v) for (int ___ = (v), _ = (fill(b, e, 0), 1); (___ || b == e) && (_ || next_nondec(b, e, ___)); _ = 0)
#define ANYS__(b, e, v) for (int ___ = (v), _ = (fill(b, e, 0), 1); (___ || b == e) && (_ || next_any(b, e, ___)); _ = 0)
#define INCS(r...) INCS__(r)
#define DIFFS(r...) DIFFS__(r)
#define NONDECS(r...) NONDECS__(r)
#define ANYS(r...) ANYS__(r)
#define SPLITS(r...) for (int _ = (fill(r, 0), 1); _ || next_split(r); _ = 0)
