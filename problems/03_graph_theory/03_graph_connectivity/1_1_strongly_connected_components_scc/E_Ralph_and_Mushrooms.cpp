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

vector<int> topoSort(const vector<vector<pair<int,ll>>>& gr) {
    int n = gr.size();
    vector<int> indeg(n), q;
    for (int i = 0; i < n; i++)
        for (auto& p : gr[i])
            indeg[p.first]++;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0)
            q.push_back(i);
    for (int j = 0; j < q.size(); j++)
        for (auto& p : gr[q[j]])
            if (--indeg[p.first] == 0)
                q.push_back(p.first);
    return q;
}
vector<int> val, comp, z, cont;
int Time, ncomps;
template<class G> int dfs(int j, G& g) {
	int low = val[j] = ++Time, x; z.push_back(j);
	for (auto e : g[j]) if (comp[e.first] < 0)
		low = min(low, val[e.first] ?: dfs(e.first,g));

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

ll calc_w(ll w){
    ll l = 0, r = w+2;
    ll ans = 0;
    while(l <= r){
        ll m = l + (r-l)/2;
        ll s = (m*(m+1))/2;
        if(s <= w){
            l = m+1;
            ans = max(ans,m);
        }
        else r = m-1;
    }
    //cout << w << " : " << (ans*(ans+1))/2 << endl;
    return w*(ans+1) - (ans*(ans+1)*(ans+2))/6 ;
}

void solve(){
    int n, ed; cin >> n >> ed;
    vector<vector<pair<int,ll>>> g(n);
    while(ed--){
        int a,b; ll c; cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({b,c});
    }
    int s; cin >> s;
    s--;
    scc(g);
    vector<ll> mush(ncomps);
    vector<vector<pair<int,ll>>> cg(ncomps);

    for(int i = 0; i < n; i++){
        int c = comp[i];
        for(auto next : g[i]){
            if(comp[next.first] == c){
                mush[c] += calc_w(next.second);
            }
            else{
                cg[c].push_back({comp[next.first], next.second});
            }
        }
    }
    vector<ll> dp(ncomps,0);
    vector<int> order = topoSort(cg);
    queue<int> q; q.push(comp[s]);
    vector<bool> vis(ncomps,0);
    while(!q.empty()){
        int node = q.front(); q.pop();
        vis[node] = true;
        for(auto e : cg[node]){
            if(!vis[e.first]){
                q.push(e.first);
                vis[e.first] = true;
            }
        }
    }
    int i = 0;
    while(order[i] != comp[s])i++;
    while(i < ncomps){
        int node = order[i];
        if(vis[node]){
            dp[node] += mush[node];
            for(auto e : cg[node]){
                dp[e.first] = max(dp[e.first], dp[node] + e.second);
            }
            
        }
        i++;
    }
    ll ans = 0;
    for(int i = 0; i < ncomps; i++)ans = max(ans, dp[i]);
    cout << ans << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve();
    return 0;
}
