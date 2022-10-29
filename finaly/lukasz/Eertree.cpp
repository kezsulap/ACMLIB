const int maxn=1000*1000+7, alfa=26;
int len[maxn], link[maxn], to[maxn][alfa];
int sz, last, n;
char s[maxn];
void init() {
	s[n++]=len[1]=-1;
	link[0]=1;
	sz=2;
}
int get_link(int v) {
	while(s[n-len[v]-2]!=s[n-1]) v=link[v];
	return v;
}
void add_letter(char c) {
	s[n++]=c-='a';
	last=get_link(last);
	if(!to[last][c]) {
		len[sz]=len[last]+2;
		link[sz]=to[get_link(link[last])][c];
		to[last][c]=sz++;
	}
	last=to[last][c];
}
int main() {
	init();
	//~ for(int i=1; i<=nn; i++)
		//~ add_letter(tekst[i]);
}
