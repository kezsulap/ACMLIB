int l = 0;
for (int i = 1; i < n; i++) {
	while (l > 0 && s[l] != s[i]) l = P[l-1];
	l += (s[l] == s[i]);
	P[i] = l;
} //Słowo indeksowane od 0, tablica P też
