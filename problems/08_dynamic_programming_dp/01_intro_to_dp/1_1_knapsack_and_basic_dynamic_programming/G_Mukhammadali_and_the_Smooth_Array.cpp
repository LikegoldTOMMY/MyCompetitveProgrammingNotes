//Topic: Knapsack and basic dynamic programming
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
const ll INF = __LONG_LONG_MAX__ - 17;

ll modulo = 1000000007;



void solve(){
    ll n; cin >> n;
    vector<ll> v(n),c(n); INPUT(v); INPUT(c);
    vector<ll> sv = v; SORTA(sv);
    vector<ll> dp(n),next(n);

    for(int i = 0; i < n; i++){
        dp[i] = ((v[0] == sv[i]) ? 0 : c[0]);
    }

    for(int i = 1; i < n; i++){
        ll prefix_min = dp[0];
        for(int j = 0; j < n; j++){
            prefix_min = min(prefix_min, dp[j]);
            if(v[i] == sv[j])next[j] = prefix_min;
            else next[j] = prefix_min  + c[i];
        }
        dp = next;
    }
    ll ans = INF;
    for(auto x : dp) ans = min(ans,x);
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
