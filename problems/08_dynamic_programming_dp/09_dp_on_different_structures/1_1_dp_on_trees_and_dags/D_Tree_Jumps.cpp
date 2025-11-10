//Topic: DP on Trees
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

ll mod = 998244353;


void solve(){
    int n; cin >> n;
    vector<vector<int>> tree(n), layers(n);
    for(int i = 0; i < n-1; i++){
        int x; cin >> x; 
        tree[x-1].push_back(i+1);
    }
    vector<int> dist(n,0);
    dist[0] = 0;
    queue<int> q; q.push(0);
    int maxh= 0;
    while(!q.empty()){
        int node = q.front(); q.pop();
        layers[dist[node]].push_back(node);
        for(auto next : tree[node]){
            dist[next] = dist[node]+1;
            maxh = max(maxh,dist[next]);
            q.push(next);
        }
    }
    vector<ll> layer_sum(maxh+2,0),dp(n,0);
    if(maxh == 0){cout << "1\n"; return;}
    dp[0] = 1; layer_sum[0] = 1;
    for(int i = 0; i <= maxh; i++){
        for(auto node : layers[i]){
            if(i != 0)dp[node] = (layer_sum[i-1]+dp[node])%mod;
            layer_sum[i] = (layer_sum[i] + dp[node])%mod;
            for(auto next : tree[node])dp[next] = (dp[next] + mod - dp[node])%mod;
        }
    }
    ll ans = mod;
    for(auto x: dp)ans = (ans+x)%mod;
    cout << ans << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t;
    cin >> t;
    while(t--)solve();
    return 0;
}
