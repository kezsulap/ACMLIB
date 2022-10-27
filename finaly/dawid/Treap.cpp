struct node {
  node *L, *R;
  int ind, prior, sub, lazy; // sub opcjonalne
  node(int ind) : L(0), R(0), ind(ind), prior(rand()), sub(1), lazy(0) {}
};
void rev(node* v) { // przykladowy update, odwraca kolejnosc w poddrzewie
  v->lazy ^= 1;
  swap(v->L, v->R);
}
void push(node* v) { // opcjonalne
  if (v->lazy) {
    if (v->L) rev(v->L);
    if (v->R) rev(v->R);
    v->lazy = 0;
} }
node* attach(node* v, node* l, node* r) {
  v->L = l; // jesli chcemy trzymac ojca to update w tej funkcji
  v->R = r;
  v->sub = 1 + (l ? l->sub : 0) + (r ? r->sub : 0); // opcjonalne
  return v;
}
node* merge(node* v, node* u) {
  if (!u) return v;
  if (!v) return u;
  push(v);
  push(u);
  if (v->prior > u->prior) return attach(v, v->L, merge(v->R, u));
  else return attach(u, merge(v, u->L), u->R);
}
pair<node*, node*> split_size(node* v, int k) { // (prefiks rozmiaru k, reszta)
  if (!v) return mp(v, v);
  int lewo = v->L ? v->L->sub : 0;
  push(v);
  if (lewo >= k) {
    auto s = split_size(v->L, k);
    return mp(s.st, attach(v, s.nd, v->R));
  } else {
    auto s = split_size(v->R, k - lewo - 1);
    return mp(attach(v, v->L, s.st), s.nd);
} }
pair<node*, node*> split_lex(node *v, int k) { // (ind <= k, reszta)
  if (!v) return mp(v, v);
  if (k < v->ind) {
    auto s = split_lex(v->L, k);
    return mp(s.st, attach(v, s.nd, v->R));
  } else {
    auto s = split_lex(v->R, k);
    return mp(attach(v, v->L, s.st), s.nd);
} }
int find_pos(node *v, int val) { // -1 jesli nie ma
  if (!v) return -1;
  int lewo = v->L ? v->L->sub : 0;
  if (v->ind == val) return 1 + lewo;
  if (val < v->ind) return find_pos(v->L, val);
  else return 1 + lewo + find_pos(v->R, val);
}