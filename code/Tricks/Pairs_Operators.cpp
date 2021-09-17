//Operatory na parach: (a, b) + c = (a + c, b + c), (a, b) + (c, d) = (a + c, b + d), a + (b, c) = (a + b, a + c)
//(a, b) += (c, d) -> (a + c, b + d) (a, b) += c -> (a + c, b + c)
//Automatycznie przenosi się na operatory na większych krotkach, np (a, (b, c)) * (e, (f, g)) = (a * e, (b, c) * (f, g)) = (a * e, (b * f, c * g))
//((a, b), c) % (d, (e, f)) = ((a, b) % d, c % (e, f)) = ((a % d, b % d), (c % e, c % f))
//Typ zwracanej pary jest wybierany na podstawie typów element operator element. np.
// (int, long long) + (long long, unsigned int) = (long long, unsigned long long)
// (bitset, int) >> (int, long long) = (bitset, long long)
// (string, int) + (char *, double) = (string, double)
#define f first
#define s second
#define vsv sim, class d, class e
#define nop(o,c,r,l...) auto operator o(c a, r b)-> decltype(make_pair(l)) {return {l};}
//enable_if jest potrzebne tylko, jeśli chcemy mieć operator <<, w przeciwnym wypadku można po prostu: vsv> nop ...
#define pcg(o) \
/*para + para*/ vsv, class f> nop(o, pair <c u d>, pair <e u f>, a.f o b.f, a.s o b.s) \
/*liczba + para*/ vsv,class = typename enable_if<!is_same<c, muu>::value>::type> nop(o, c, pair<d u e>, a o b.f, a o b.s) \
/*para + liczba*/ vsv> nop(o, pair<c u d>, e, a.f o b, a.s o b)
#define clp(o) pcg(o) \
/*para += liczba*/ vsv> void operator o##= (pair <c,d> & a, e b) {a.f o##= b; a.s o##= b;} \
/*liczba += para*/ vsv, class f> void operator o##= (pair <c,d> & a, pair <e,f> b) {a.f o##= b.f; a.s o##= b.s;}
#define syd(o) sim, class d> auto operator o(pair<c, d> e) -> decltype(make_pair(o e.f, o e.s)) {return {o e.f, o e.s};}
#define u ,
//clp: razem z odpowiednim operatorem przypisania, pcg: bez niego, syd: operator jednoargumentowy
clp(+) clp(-) clp(*) clp(/) clp(%) clp(^) clp(|) clp(>>) clp(<<) clp(&) pcg(&&) pcg(||) syd(-) syd(+) syd(~) syd(!)
#undef u
