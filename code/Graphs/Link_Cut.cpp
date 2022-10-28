struct Splay {
  Splay *l = 0, *r = 0, *p = 0;
  bool flip = false; // Wywal jak nie używasz make_root.
  void update() {
		//update anything stored for nodes
    assert(!flip and (!l or !l->flip) and (!r or !r->flip)); }
  void touch() { //Do any lazy prop here
    if (flip) { 
      swap(l, r);
      if (l) l->flip = !l->flip;
      if (r) r->flip = !r->flip;
      flip = false;
    }
  }
  bool sroot() { return !p or (p->l != this and p->r != this); }
  void connect(Splay* c, bool left) { (left ? l : r) = c; if (c) c->p = this; }
  void rotate() {
    Splay* f = p; Splay* t = f->p;
    const bool isr = f->sroot();
    const bool left = (this == f->l);
    f->connect(left ? r : l, left);
    connect(f, !left);
    if (isr) p = t;
    else t->connect(this, f == t->l);
    f->update();
  }
  void push(){sroot()?touch():p->push();if (l) l->touch();if (r) r->touch();}
  void splay() {
    push();
    while (!sroot()) {
      Splay* x = p->p;
      if (!p->sroot()) (((p->l == this) == (x->l == p)) ? p : this)->rotate();
      rotate();
    }   
    update();
  }
  Splay* expose(){//v będzie korzeniem splaya zawierającego ścieżkę do korzenia
    Splay *q = this, *x = 0;//prawe dziecko będzie nullem. Jak zejdziemy w dół, 
    while (q) {  // to potem trzeba zrobić splay().
      q->splay();// LCA(u, v): u->expose(); return v->expose();
      q->r = x;  q->update();
      x = q;  q = q->p;
    }
    splay();
    return x;
  }
  Splay* root() {  // Zwraca roota drzewowego (nie splejowego!).
    expose();
    Splay* s = this;
    while (s->touch(), s->l) s = s->l;
    s->splay();
    return s;
  }
  void cut() {  // Usuwa krawędź znajdującą się nad danym wierzchołkiem.
    expose(); assert(l /* Nie jest rootem. */);
    Splay* s = l;
    while (s->touch(), s->r) s = s->r;
    s->splay();  s->r->p = 0;  s->r = 0;
  }
  void link(Splay* to) {
    expose(); assert(!l /* Jest rootem. */);
    p = to;
  }
  // Sprawia, że wierzchołek jest rootem w logicznym i w splayowym drzewie.
  void make_root() { expose(); flip = !flip; touch(); }
};
