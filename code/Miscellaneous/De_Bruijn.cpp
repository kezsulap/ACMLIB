//Generuje słowo cykliczne, Działa dla alph >= 2
vi de_bruijn(int len, int alph){
	vi res, lyn{0};
	while (lyn[0] != alph - 1){
		int r = siz(lyn);
		if (len % r == 0)
			for (int c : lyn)
				res.pb(c);
		for (int i = r; i <= len - 1; ++i)
			lyn.pb(lyn[i - r]);
		while (lyn.back() == alph - 1)
			lyn.pop_back();
		lyn.back()++;
	}
	res.pb(alph - 1);
	return res;
}
