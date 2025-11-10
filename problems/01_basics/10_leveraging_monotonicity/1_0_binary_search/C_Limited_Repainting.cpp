//Topic: Binary Search
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

bool good(int n, int k, string& s,vector<ll> &v, ll m){
    int ops = 0;
    int i = 0;
    while(i < n){
        if(s[i] == 'B' && v[i] > m){
            ops++;
            while(i < n && (v[i] <= m || s[i] == 'B'))i++;
        }
        i++;
    }
    return ops <= k;
}

void solve(){
    int n,k; cin >> n >> k;
    string s; cin >> s;
    vector<ll> v(n); INPUT(v);
    ll l = 0, r = 10e9+1,ans = r;
    
    while(l <= r){
        ll m = l + (r-l)/2;
        if(good(n,k,s,v,m)){
            r = m-1;
            ans = min(ans,m);
        }
        else l = m+1;
    }
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
