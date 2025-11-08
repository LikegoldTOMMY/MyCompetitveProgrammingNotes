//Topic: DP on Trees and DAG
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

pair<vector<int>,vector<int>> find_order(int n, vector<vector<int>> &tree, int root){
    vector<bool> vis(n,0);
    vector<int> subtree(n,1);
    queue<int> q; q.push(root);
    vis[root] = true;
    vector<int> ord;
    while(!q.empty()){
        int node = q.front(); q.pop();
        ord.push_back(node);
        for(auto next : tree[node]){
            if(!vis[next]){
                vis[next] = true;
                q.push(next);
            }
        }
    }
    vis = vector<bool>(n,0);
    //PRINT(ord);
    for(int i = n-1; i >= 0; i--){
        vis[ord[i]] = true;
        for(auto next: tree[ord[i]])if(!vis[next])subtree[next] += subtree[ord[i]];
    }
    return {ord,subtree};
}


void solve(){
    int n, k; cin >> n >> k;
    vector<vector<int>> tree(n);
    for(int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b;
        a--; b--;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    auto [order,subtree_size] = find_order(n,tree,0);
    vector<ll> dp(n,0);
    vector<bool> vis(n,0);
    for(auto node: order){
        if(subtree_size[node] >= k)dp[0]++;
    }
    for(auto node: order){
        vis[node] = true;
        for(auto next : tree[node]){
            if(!vis[next]){
                dp[next] += dp[node] + (subtree_size[next] < k) - (n - subtree_size[next] < k);
            }
        }
    }
    //PRINT(dp);
    cout << accumulate(dp.begin(),dp.end(),0ll) << endl;;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t;
    cin >> t;
    while(t--)solve();
    return 0;
}
