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

vector<int> topoSort(const vector<set<int>>& gr) {
	vector<int> indeg(gr.size()), q;
	for (auto& li : gr) for (int x : li) indeg[x]++;
	for(int i = 0; i < gr.size(); i++) if(indeg[i] == 0) q.push_back(i);
	for(int j = 0; j < q.size(); j++) for (int x : gr[q[j]])
		if (--indeg[x] == 0) q.push_back(x);
	return q;
}

vector<int> val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
	int low = val[j] = ++Time, x; z.push_back(j);
	for (auto e : g[j]) if (comp[e] < 0)
		low = min(low, val[e] ?: dfs(e,g,f));

	if (low == val[j]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != j);
		f(cont); cont.clear();
		ncomps++;
	}
	return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
	int n = g.size();
	val.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
	for(int i = 0; i < n; i++)if (comp[i] < 0) dfs(i, g, f);
}

void solve(){
    ll n, m; cin >> n >> m; 
    vector<ll> c(n); INPUT(c);
    vector<vector<int>> g(n);
    while(m--){
        int a,b; cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
    }
    auto print_scc = [](vector<int>& scc_nodes) { };
    scc(g,print_scc);
    vector<ll> coin(ncomps,0);
    
vector<set<int>> compressed(ncomps);
    for(int i = 0; i < n; i++){
        ll curr_comp = comp[i];
        coin[curr_comp] += c[i];
        for(auto next : g[i]){
            if(curr_comp != comp[next])compressed[curr_comp].insert(comp[next]);
        }
    }
    
    vector<int> indeg(ncomps);
    for(auto& li : compressed)for (int x : li) indeg[x]++;
    
    stack<int> sp;
    for(int i = 0; i < ncomps; i++){
        if(indeg[i] == 0)sp.push(i);
    }

    vector<ll> dp(ncomps,0);
    vector<int> ord = topoSort(compressed);
    for(auto node: ord){
        dp[node] += coin[node];
        for(auto next: compressed[node]){
            dp[next] = max(dp[next], dp[node]);
        }
    }
    //PRINT(dp);
    ll ans = 0;
    for(auto x: dp)ans = max(ans,x);

    cout << ans << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve();
    return 0;
}
