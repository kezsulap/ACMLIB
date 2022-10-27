// usunac REPy trzeba
void xor_fft(ll* p, int n, bool inv) {
  for (int len = 1; 2 * len <= n; len <<= 1) {
    for (int i = 0; i < n; i += 2 * len) {
      REP(j, len) {
        ll u = p[i + j];
        ll v = p[i + len + j];
        p[i + j] = u + v;
        p[i + len + j] = u - v;
  } } }
  if (inv) {
    REP(i, n) {
      p[i] /= n; // uwaga gdy liczymy modulo!!
} } }
void and_fft(ll* p, int n, bool inv) {
  for (int len = 1; 2 * len <= n; len <<= 1) {
    for (int i = 0; i < n; i += 2 * len) {
      REP(j, len) {
        ll u = p[i + j];
        ll v = p[i + len + j];
        if (!inv) {
          p[i + j] = v;
          p[i + len + j] = u + v;
        } else {
          p[i + j] = -u + v;
          p[i + len + j] = u;
} } } } }
void or_fft(ll* p, int n, bool inv) {
  for (int len = 1; 2 * len <= n; len <<= 1) {
    for (int i = 0; i < n; i += 2 * len) {
      REP(j, len) {
        ll u = p[i + j];
        ll v = p[i + len + j];
        if (!inv) {
          p[i + j] = u + v;
          p[i + len + j] = u;
        } else {
          p[i + j] = v;
          p[i + len + j] = u - v;
} } } } }