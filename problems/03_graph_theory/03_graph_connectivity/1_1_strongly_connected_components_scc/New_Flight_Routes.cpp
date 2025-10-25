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
template<class G> void scc(G& g) {
	int n = g.size();
	val.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
	for(int i = 0; i < n; i++)if (comp[i] < 0) dfs(i, g);
}
 
vector<bool> vis;
vector<int> indeg, outdeg;
vector<vector<int>> cg;
 
int dfs_sink(int node){
    vis[node] = true;
    if(outdeg[node] == 0){
        return node;
    }
    for(auto next : cg[node]){
        if(vis[next])continue;
        int sink =  dfs_sink(next);
        if(sink != -1)return sink;
    }
    return -1;
}
 
void solve(){
    int n, m; cin >> n >> m; 
    vector<vector<int>> g(n);
    while(m--){
        int a,b; cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
    }
    scc(g);
    if(ncomps == 1){
        cout << 0 << endl;
        return;
    }
    vector<int> rapp(ncomps);
    cg = vector<vector<int>>(ncomps);
    indeg = vector<int>(ncomps,0);
    outdeg = vector<int>(ncomps,0);
 
    for(int i = 0; i < n; i++){
        rapp[comp[i]] = i;
        for(auto next : g[i]){
            if(comp[next] != comp[i]){
                cg[comp[i]].push_back(comp[next]);
                indeg[comp[next]]++;
                outdeg[comp[i]]++;
            }
        }
    }
 
    vector<int> sink,source;
    for(int i = 0; i < ncomps; i++){
        if(indeg[i] == 0)source.push_back(i);
        if(outdeg[i] == 0)sink.push_back(i);
    }
 
    int ans = max(sink.size(), source.size());
    cout << ans << endl;
 
    vector<pair<int,int>> sp;
    vector<int> u_so, u_si;
    vis = vector<bool>(ncomps,0);
    for(auto so: source){
        ll si = dfs_sink(so);
        if(si != -1)sp.push_back({so,si});
        else u_so.push_back(so);
    }
    for(auto si : sink)if(!vis[si])u_si.push_back(si);
    
    int np = sp.size();
 
    for(int i = 0;i < np; i++){
        cout << rapp[sp[i].second]+1 << " " << rapp[sp[(i+1)%np].first]+1 << endl;
    }
 
    int mi = min(u_so.size(), u_si.size());
    for(int i = 0; i < mi; i++){
        cout << rapp[u_si[i]]+1 << " " << rapp[u_so[(i+1)%mi]] + 1 << endl;
    }
 
    int f_si=-1, f_so=-1;
    if(np != 0){
        f_so = sp[0].first;
        f_si = sp[0].second;
    }
    else{
        f_si = sink[0];
        f_so = source[0];
    }
    for(int i = mi; i < u_si.size(); i++){
        int si = u_si[i];
        cout << rapp[si]+1 << " " << rapp[f_so]+1 << endl;
    }
    for(int i = mi; i < u_so.size(); i++){
        int so = u_so[i];
        cout << rapp[f_si]+1 << " " << rapp[so]+1 << endl;
    }
}   
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve();
    return 0;
}