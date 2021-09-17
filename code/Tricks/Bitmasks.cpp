using unt = unsigned int;
inline unt rev(unt m) {//Odwraca kolejność bitów: 10110000 -> 00001101
	const static unt s1 = (~0u) / 3, s2 = (~0u) / 5, s4 = (~0u) / 17, s8 = (~0u) / 257, s16 = (~0u) / 65537;
	#define her(i) m = ((m & s##i) << i) | ((m >> i) & s##i);
	her(1) her(2) her(4) her(8) her(16) //Dla ull jeszcze: her(32)
	return m;
}
inline ull rev(ull m) {//Odwraca kolejność bitów: 10110000 -> 00001101
	const static ull s1 = (~0ull) / 3, s2 = (~0ull) / 5, s4 = (~0ull) / 17, s8 = (~0ull) / 257, s16 = (~0ull) / 65537, s32 = (~0ull) / (1ll << 32 | 1);
	#define her(i) m = ((m & s##i) << i) | ((m >> i) & s##i);
	her(1) her(2) her(4) her(8) her(16) her(32)
	return m;
}

#define forbits(i,m)if(m)for(urs(m)i=ctz(m),i##nvj=m;i##nvj;i##nvj^=((urs(m))1<<i),i=i##nvj?ctz(i##nvj):0)
#define fordbits(i,m)if(m)for(urs(m)i=8*sizeof(m)-clz(m)-1,i##nxd=m;i##nxd;i##nxd^=((urs(m))1<<i),i=i##nxd?8*sizeof(m)-clz(i##nxd)-1:0)
#define ksets(t, m, k, n)for(t m=(((t)1<<(k))-1);m<((t)1<<(n));m=nux(m))
#define urs(r...)typename decay<decltype(r)>::type
#define hur(f,g)sim>int f(c a){if(sizeof(c)==8)return g##ll(a);return g(a);}
hur(popc,__builtin_popcount)hur(ctz,__builtin_ctz)hur(clz,__builtin_clz)
sim>inline c nux(c m){if(!m)return numeric_limits<c>::max();c A=m&-m;c B=~((A-1)^m);c C=B&-B;c D=(C>>(1+ctz(A)))-1;return C|(m&~(C-1))|D;}

sim> inline c rrh(c m) {
	c a = ~(m | m >> 1);
	c b = a & -a;
	return (m | b) &~ (b - 1);
}
sim> inline c lyl(c m) {
	c x = m & -m;
	return (m ^ x) | ((x << 1) / 3);
}
/*
	for (unt i = 0; i < (1u << n); i = rrh(i)) { //na unsigned intach działa dla n <= 31
		//i - maska bez dwóch sąsiednich zapalonych bitów; kolejność rosnąca
	}
	for (unt i = (1u << (n + 1)) / 3; ; i = lyl(i)) { //na unsigned intach działa dla n <= 30
		//m - maska bez dwóch sąsiednich zapalonych bitów; kolejność malejąca
		if (!i) break;
	}
*/

/*
	//Iterowanie się po maskach w takiej kolejności, że każde dwie kolejne różnią się jednym bitem
	//go(0)
	for (unt quq = 1, m = 0; quq < (1u << n); ++quq) {
		int i = __builtin_ctz(quq);
		m ^= (1 << i);
		//go(m) - kolejna maska
	}
	*/
