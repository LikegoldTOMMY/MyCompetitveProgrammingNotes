//Topic: Strongly Connected Components
#include <bits/stdc++.h>
#define PB push_back
#define MP makepair
#ifndef ONLINE_JUDGE
#define DEBUG(x) cout << #x << " = " << (x) << endl
#else
#define DEBUG(x)
#endif
#define FOR(n) for(int i = 0; i < (n); i++)
#define SORTA(v) sort((v).begin(), (v).end())
#define SORTD(v) sort((v).rbegin(), (v).rend())
#define PRINT(v) for(auto x: (v))cout << x << " "; cout << endl;
#define TWO(n) (1 << (n))
#define INPUT(v) for(auto &x : (v))cin >> x;
#pragma GCC optimize("Ofast,no-stack-protector,fast-math",3)
 
typedef long long ll;
using namespace std;

ll modulo = 1000000007;

vector<int> val, comp, z, cont;
int Time, ncomps;

template<class G> int dfs(int j, G& g){
	int low = val[j] = ++Time, x; z.push_back(j);
	for (auto e : g[j]) if (comp[e] < 0)
		low = min(low, val[e] ?: dfs(e,g));
 
	if (low == val[j]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != j);
		cont.clear();
		ncomps++;
	}
	return val[j] = low;
}

vector<bool> vis;
map<int,int> inv_ord;
vector<int> v;
vector<set<int>> cg;
vector<int> order;



template<class G> void scc(G& g) {
	int n = g.size();
	val.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
	for(int i = 0; i < n; i++)if (comp[i] < 0) dfs(i, g);
}

vector<int> topoSort(const vector<set<int>>& gr) {
	vector<int> indeg(gr.size()), q;
	for (auto& li : gr) for (int x : li) indeg[x]++;
	for(int i = 0; i < gr.size(); i++) if(indeg[i] == 0) q.push_back(i);
	for(int j = 0; j < q.size(); j++) for (int x : gr[q[j]])
		if (--indeg[x] == 0) q.push_back(x);
	return q;
}

void cdfs(int node, int goal){
    vis[node] = true;
    for(auto next : cg[node]){
        if(inv_ord[next] <= inv_ord[goal] && !vis[next])cdfs(next,goal);
    }
}

void solve(){
    int n,k; cin >> k >> n;
    vector<set<int>> g(n);
    v = vector<int>(k); INPUT(v);
    for(int i = 0; i < k; i++)v[i]--;
    int m; cin >> m;
    while(m--){
        ll a,b; cin >> a >> b;
        a--; b--;
        g[a].insert(b);
    }
    scc(g);
    cg = vector<set<int>>(ncomps);
    for(int i = 0; i < n; i++){
        for(auto next : g[i]){
            if(comp[i] != comp[next])cg[comp[i]].insert(comp[next]);
        }
    }
    ll ans = 2;
    order = topoSort(cg);
    vis = vector<bool>(ncomps,0);

    for(int i = 0; i < ncomps; i++){
        inv_ord[order[i]] = i;
    }
    for(int i = 1; i < k; i++){
        if(g[v[i-1]].count(v[i])){
            ans += 2; continue;
        }
        else if(comp[v[i]] == comp[v[i-1]]){
            ans ++; continue;
        }  
        if(inv_ord[comp[v[i]]] < inv_ord[comp[v[i-1]]])break;
        vis[comp[v[i-1]]]=0;
        cdfs(comp[v[i-1]],comp[v[i]]);
        if(vis[comp[v[i]]])ans++;
        else break;
    }
    cout << ans << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve();
    return 0;
}
