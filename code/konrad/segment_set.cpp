#define root this->node_begin()
#define none this->node_end()
#define V get_metadata().in
#define L get_l_child()
#define R get_r_child()
//struct Mal potrzebny tylko jesli Op::T ma nietrywialny konstruktor
	template <class c> struct Mal : allocator<c> {
		template <class U> struct rebind { using other = Mal<U>; };
	};
	template <class...c> struct Mal<detail::rb_tree_node_<c...> > :
	allocator<detail::rb_tree_node_<c...> > {
		using v = typename Mal::value_type;
		v* allocate(int) {
			v* ans = allocator<v>::allocate(1);
			new (&ans->get_metadata()) typename v::metadata_type;
			return ans;
		}
	};
//Jesli nie potrzebujemy find_by_order i order_of_key, to wystarczy:
	template <class c> struct Baz {mutable c in;};
//i wszedzie dalej pomijamy parametr bool ord, oraz w update wyroznione linie
	template <class c, bool b> struct Baz {
		mutable int size;
		mutable c in;
		operator int() const {return size;}
		void reset() const {size = 1;}
		void inc(int x) const {size += x;}
	};
	template <class c> struct Baz <c, 0> {
		mutable c in;
		void reset() const {}
		void inc(const Baz&) const {}
	};
template <class Op, bool ord> struct Foo {
//W C++11/14 trzeba: template <class A, class B, class C, class D> struct Bar : tree_order_statistics_node_update<A,B,C,D> {
	template <class... X> struct Bar : tree_order_statistics_node_update<X...> {
		using T = typename Op::T;
		using metadata_type = Baz<T, ord>;
		template <class c, class d> void operator()(c n, d end) const {
			n.V = Op::conv(**n);
			n.get_metadata().reset(); //Tylko jak potrzebujemy ordered_seta
			auto l = n.L, r = n.R;
			if (l != end) {
				n.V = Op::mer(l.V, n.V);
				n.get_metadata().inc(l.get_metadata()); //j.w.
			}
			if (r != end) {
				n.V = Op::mer(n.V, r.V);
				n.get_metadata().inc(r.get_metadata()); //j.w.
			}
		}
	};
};
template <class c, class k, class Op, class cmp = less<c>, bool ord = false> 
struct seg_map : tree<c, k, cmp, rb_tree_tag, Foo<Op, ord>::template Bar, Mal<c>> { //Jesli nie uzywamy structa Mal, to po prostu pomijamy ostatni parametr
	using T = typename Op::T;    using C = typename seg_map::const_iterator;
	using N = typename seg_map::node_const_iterator;
	T mer(const T&a, const T&b, bool d) const { return d ? Op::mer(a, b) : Op::mer(b, a); }
	N go(N n, bool d) const {return d ? n.R : n.L;}
	T whole() const { return this->empty() ? Op::neu() : root.V; }
	T read(C it, bool d) const {
		N n = from_it(it);
		T ans = Op::neu();
		if (go(n, d) != none) ans = go(n, d).V;
		while (n != root) {
			N p = P(n);
			if (go(p, !d) == n) {
				ans = mer(ans, Op::conv(**p), d);
				if (go(p, d) != none) ans = mer(ans, go(p, d).V, d);
			}
			n = p;
		}
		return ans;
	}
	T read_pref(C it) const {//[begin, it)
		if (it == this->begin()) return Op::neu();
		if (it == this->end()) return whole();
		return read(it, 0);
	}
	T read_suf(C it) const {//[it, end)
		if (it == this->begin()) return whole();
		if (it == this->end()) return Op::neu();
		return read(--it, 1);
	}
//Dla l > r wynik jest nieokreslony, ale wykona sie w O(log n) i nie bedzie RE
	T read(C l, C r) const { //[l, r)
		if (l == this->begin()) return read_pref(r);
		if (r == this->end()) return read_suf(l);
		N b = from_it(--l), e = from_it(r);
		T B = Op::neu(), E = Op::neu();
		if (!anc(b, e) && e.L != none) E = e.L.V;
		if (!anc(e, b) && b.R != none) B = b.R.V;
		int d = dep(b) - dep(e);
		while (b != e) {
			bool D = d > 0;
			D ? d-- : d++;
			N &m = D ? b : e, &o = D ? e : b;
			T &v = D ? B : E;
			N p = P(m);
			if (p != o && go(p, !D) == m) {
				v = mer(v, Op::conv(**p), D);
				N u = go(p, D);
				if (u != none && u != o) v = mer(v, u.V, D);
			}
			m = p;
		}
		return mer(B, E, 1);
	}
	N P(N x) const {return {x.m_p_nd->m_p_parent};}
	N from_it(C x) const {return {x.m_p_nd};}
	int dep(N x) const {
		int ans = 0;
		while (x != root) {
			ans++;
			x = P(x);
		}
		return ans;
	}
	bool anc(N x, N y) const {
		for (;;) {
			if (x == y) return 1;
			if (x == root) return 0;
			x = P(x);
		}
	}
	template <class Fun> C get_side(C it, Fun pred, bool dir) const {
		T acc = Op::neu();
		N n = from_it(it);
		for (;;) {
			acc = mer(acc, **n, dir);
			if (!pred(acc)) return dir ? *n : ++*n;
			if (go(n, dir) != none) {
				T t1 = mer(acc, go(n, dir).V, dir);
				if (pred(t1)) acc = t1;
				else {
					n = go(n, dir);
					for (;;) {
						if (go(n, !dir) != none) {
							T t2 = mer(acc, go(n, !dir).V, dir);
							if (!pred(t2)) {
								n = go(n, !dir);
								continue;
							}
							acc = t2;
						}
						acc = mer(acc, **n, dir);
						if (!pred(acc)) return dir ? *n : ++*n;
						n = go(n, dir);
					}
				}
			}
			for (;;) {
				if (n == root) return dir ? this->end() : this->begin();
				N p = P(n);
				if (go(p, !dir) == n) {
					n = p;
					break;
				}
				n = p;
			}
		}
	}
//Zwraca najdalszy it taki, ze pred(read(beg, it)), lub it = beg, jesli takiego nie ma. Zaklada, ze jesli jakis przedzial spelnia pred, to jego podprzedzial tez
	template <class Fun> C get_right(C beg, Fun pred) const {
		if (beg == this->end()) return beg;
		return get_side(beg, pred, 1);
	}
	template <class Fun> C get_left(C end, Fun pred) const { //j.w, tylko z read(it, end)
		if (end == this->begin()) return end;
		return get_side(--end, pred, 0);
	}
//Jesli wartosci agregowane zaleza od typu ta ktory jest mapowanie, to po kazdej edycji wartosci (takze wrzuceniu nowej) nalezy wywolac update lub po wszystkich edycjach wywolac update_all
	void update(C pos) { 
		N n = from_it(pos);
		for (;;) {
			seg_map::node_update::operator()(n, none);
			if (n == root) break;
			n = P(n);
		}
	}
	void dfs(N n) {
		if (n == none) return;
		dfs(n.L); dfs(n.R);
		seg_map::node_update::operator()(n, none);
	}
	void update_all() { dfs(root); }
};
template <class c, class Op, class cmp=less<c>, bool ord = false>
using seg_set = seg_map<c, null_type, Op, cmp, ord>;
struct Sum { //Przykladowy typ definiujacy operacje
	using T = ll; //typ wyniku dla przedzialu
	static T neu() {return 0;}; //element neutralny dzialania
//rzutuje typ wartosci na typ wynikowy (w przypadku mapy para: klucz, wartosc)
	static T conv(pii x) { return x.second; }
	static T mer(T a, T b) {return a + b;}
};
//Zeby sie skompilowalo z flaga -D_GLIBCXX_DEBUG, to typ trzymany w kontenerze (tylko typ klucza dla mapy) musi miec zdefiniowany operator<<(ostream &, nasz_typ), przy czym, jesli ten typ jest w namespace std, to operator tez musi byc. 
