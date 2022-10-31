struct MinCost {
	struct kra {
		int cel, *prze1, *prze2;
		ll koszt;
	};
	int n=0, zr, uj;
	const ll inf=1e9;
	vector <vector <kra>> graf;
	vi bylo, aktu;
	vector <ll> odl;
	void vert(int v) {
		if (v>n) {
			n=v;
			graf.resize(n);
			bylo.resize(n);
			aktu.resize(n);
			odl.resize(n);
		}
	}
	void add_edge(int v, int u, int prze, ll koszt) {
		vert(v+1); vert(u+1);
		kra ret1{u, new int(prze), new int(0), koszt};
		kra ret2{v, ret1.prze2, ret1.prze1, -koszt};
		graf[v].pb(ret1);
		graf[u].pb(ret2);
	}
	void spfa() {
		for (int i=0; i<n; i++) {
			aktu[i]=1;
			odl[i]=inf;
		}
		aktu[zr]=odl[zr]=0;
		queue <int> kol;
		kol.push(zr);
		while(!kol.empty()) {
			int v=kol.front();
			kol.pop();
			if (aktu[v])
				continue;
			aktu[v]=1;
			for (kra i : graf[v]) {
				if (*i.prze1 && odl[v]+i.koszt<odl[i.cel]) {
					odl[i.cel]=odl[v]+i.koszt;
					aktu[i.cel]=0;
					kol.push(i.cel);
				}
			}
		}
	}
	int dfs(int v) {
		if (v==uj)
			return 1;
		bylo[v]=1;
		for (int i=0; i< siz(graf[v]); i++) {
			if (!bylo[graf[v][i].cel] && (*graf[v][i].prze1) &&
			odl[v]+graf[v][i].koszt==odl[graf[v][i].cel] && dfs(graf[v][i].cel)) {
				(*graf[v][i].prze1)--;
				(*graf[v][i].prze2)++;
				return 1;
			}
		}
		return 0;
	}
	pair <int,ll> flow(int zrzr, int ujuj) {
		zr=zrzr; uj=ujuj;
		vert(zr+1); vert(uj+1);
		pair <int,ll> ret{0, 0};
		while(1) {
			spfa();
			for (int i=0; i<n; i++)
				bylo[i]=0;
			if (!dfs(zr))
				break;
			ret.st++;
			ret.nd+=odl[uj];
		}
		return ret;
	}
};
