#define X real()
#define Y imag()
typedef complex<ll> P;
struct line {
    ll a,b,c;
    line(ll a_ = 0, ll b_ = 0, ll c_ = 0): a(a_), b(b_), c(c_) {} // <= 10^9
    line (P const &A, P const &B): a(A.Y-B.Y), b(B.X-A.X), c(A.X*B.Y-A.Y*B.X) {} //pts <= 10^6
    line operator - () const {return line(-a, -b, -c); }
    bool up() const { return a?(a<0):(b>0);}
};
inline ll wek(line const &a, line const &b) {return a.a*b.b-a.b*b.a;}
inline bool rown(line a, line b) {return wek(a,b) == 0;}
inline bool pokr(line a, line b) {return rown(a,b) && a.a*b.c == b.a*a.c && a.b*b.c == b.b*a.c;}
inline bool podobne(line a, line b) {return rown(a,b) && a.up() == b.up();}
inline complex<ld> prosta_prosta(line a, line b) {
    ll det = wek(a,b);
    ll x =  -a.c*b.b+b.c*a.b;
    ll y =  -a.a*b.c+a.c*b.a;
    return complex<ld>(x,y)/(ld)det;
}
inline ll weaker (line a, line b) { // czy a jest slabsze niz b
    assert(rown(a,b));
    if (abs(a.a) > abs(a.b)) return a.c*abs(b.a) -  b.c*abs(a.a);
    else return a.c*abs(b.b) -  b.c*abs(a.b);
}
struct Comp {
    bool operator()(const line& a, const line& b) const {
        if (a.up() != b.up()) return a.up() > b.up();
        return wek(a,b) > 0;
    }
};
const ld EPS = 1e-12;
struct przeciecie_polplaszczyzn {
    bool empty, pek;
    set<line, Comp> S;
    typedef set<line, Comp>::iterator iter;
    przeciecie_polplaszczyzn() : empty(false), pek(false) {};
    iter next(iter it){return (++it == S.end() ? S.begin() : it);}
    iter prev(iter it){return (it == S.begin() ? --S.end() : --it);}
    bool hide(line a, line b, line c) {
        if (rown(a,b)) {
            if (weaker(a, -b) < 0) empty = true;
            return false; 
        }
        if (wek(a,b) < 0) swap(a,b);
        complex<ld> r = prosta_prosta(a,b);
        ld v = r.X * c.a + r.Y * c.b + c.c;
        if (wek(a,c) >=0  && wek(c,b) >=0 && v > -EPS) return true;
        if (wek(a,c) < 0  && wek(c,b) < 0) {
            if (v < -EPS) empty = true;
            else if (v < EPS) pek = true;
        }
        return false;
    }
    void add(line l) {
        if (empty) return;
        if (l.a == 0 && l.b == 0) {
            if (l.c < 0) empty = true;
            return;
        }
        iter it = S.lower_bound(l);
        //rownolegle
        if(it != S.end() && podobne(*it, l)) {
            if (weaker(l, *it)>=0) return;
            iter del = it;
            it = next(it);
            S.erase(del);
        }
        //*it>p
        if(siz(S) >= 2 && it == S.end()) it = S.begin();
        while(siz(S) >= 2 && hide(l, *next(it), *it)) {
            iter del = it;
            it = next(it);
            S.erase(del);
        }
        //*it<p
        if(siz(S) >= 2) it = prev(it);
        while(siz(S) >= 2 && hide(l, *prev(it), *it)) {
            iter del = it;
            it = prev(it);
            S.erase(del);
        }
        if(S.size() < 2 || !hide(*it, *next(it), l)) S.insert(l);
    }
    /*	 0 - puste	 1 - punkt	 2 - odcinek	 3 - półprosta	 4 - prosta
         5 - dodatnie (może nieskończone) pole (S.size() daje wowczas liczbę boków) */
    int type() {
        if(empty) return 0;
        if(siz(S) <= 4){
            vector<line> res(all(S));
            if (siz(res) == 2 && rown(res[0], res[1]) && weaker(res[0], -res[1])<0) return 0; 
            for (int i = 0; i < siz(res); ++i) for (int j = 0; j < i; ++j) if(pokr(res[i], res[j]))  {
                if(siz(res) == 2) return 4;
                if(siz(res) == 3) return 3;
                if(siz(res) == 4 && pokr(res[0], res[2]) && pokr(res[1], res[3])) return 1;
                return 2;
            }
            if(siz(res) == 3 && pek) return 1;
        }
        return 5;
    }
};
