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
 
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

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
    string s,l; cin >> s >> l;
    int n = sz(s), m = sz(l);
    //ACTG
    vector<vd> dna(4, vd(n,0));
    vector<vd> pattern(4, vd(m,0));

    for(int i = 0; i < n; i++){
        if(s[i] == 'A')dna[0][i]=1;
        if(s[i] == 'C')dna[1][i]=1;
        if(s[i] == 'T')dna[2][i]=1;
        if(s[i] == 'G')dna[3][i]=1;
    }
    for(int i = 0; i < m; i++){
        if(l[m-1-i] == 'A')pattern[0][i]=1;
        if(l[m-1-i] == 'C')pattern[1][i]=1;
        if(l[m-1-i] == 'T')pattern[2][i]=1;
        if(l[m-1-i] == 'G')pattern[3][i]=1;
    }

    vd ans = conv(dna[0],pattern[0]);
    for(int i = 1; i < 4; i++){
        vd temp = conv(dna[i],pattern[i]);
        for(int j = 0; j < sz(ans); j++)ans[j] += temp[j];
    }
    int res = m;
    for(int i = m-1; i < sz(ans)-m+1; i++){
        res = min(res, m- ((int)round(ans[i])));
    }
    //PRINT(ans); 
    cout << res << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve();
    return 0;
}
