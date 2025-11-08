//Topic: Fast Fourier Transform
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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

ll modulo = 1000000007;

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}
vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
	vector<C> in(n), out(n);
	copy(all(a), begin(in));
	rep(i,0,sz(b)) in[i].imag(b[i]);
	fft(in);
	for (C& x : in) x *= x;
	rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}

void solve(){
    ll k,n,m; cin >> k >> n >> m;
    vd a(2*k+1,0),b(2*k+1,0);
    while(n--){
        double x; cin >> x;  a[x]+=1;
    }
    while(m--){
        double x; cin >> x; b[x]+=1;
    }
    vd c = conv(a,b);
    for(int i = 2; i <=2*k; i++ )cout << ((long long) round(c[i]))  << " ";
    cout << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve();
    return 0;
}
