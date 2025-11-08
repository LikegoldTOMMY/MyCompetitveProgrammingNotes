//Topic: Fast Fourier Transform
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef complex<double> base;

const double PI = acos(-1.0);
vector<int> order;

void fft(vector<base> &a, bool invert) {
    int n = a.size();
    for(int i = 0; i < n; i++)
        if (order[i] < i)
            swap(a[i], a[order[i]]);
    
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        base wlen(cos(ang), sin(ang));
        int half = len >> 1;
        vector<base> w(half);
        base w0(1);
        for(int i = 0; i < half; i++)
            w[i] = w0, w0 *= wlen;
        
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < half; j++) {
                base u = a[i + j];
                base v = a[i + j + half] * w[j];
                a[i + j] = u + v;
                a[i + j + half] = u - v;
            }
        }
    }
    
    if (invert)
        for (int i = 0; i < n; i++)
            a[i] /= n;
}

void precalc(int n, int L) {
    order.resize(n);
    for(int i = 0; i < n; i++) {
        int res = 0;
        for(int j = 0; j < L; j++)
            if (i & (1 << j))
                res |= 1 << (L - j - 1);
        order[i] = res;
    }
}

vector<int> fft_mul(const vector<int>& a, const vector<int>& b) {
    vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    int L = 0;
    
    // Find the smallest power of 2 that can hold the result
    while(n < (int)(a.size() + b.size())) {
        n <<= 1;
        L++;
    }
    
    fa.resize(n);
    fb.resize(n);
    precalc(n, L);
    
    fft(fa, false);
    fft(fb, false);
    
    for(int i = 0; i < n; i++)
        fa[i] *= fb[i];
    
    fft(fa, true);

    vector<int> res(n);
    for(int i = 0; i < n; i++) {
        // Key insight: clamp to 0 or 1 since we only care about existence
        res[i] = (int)(fa[i].real() + 0.5) > 0 ? 1 : 0;
    }

    return res;
}

void solve() {
    int n, k;
    cin >> n >> k;
    
    vector<int> present(1001, 0); // Assuming values up to 1000
    int max_val = 0;
    
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        present[x] = 1;
        max_val = max(max_val, x);
    }
    
    // Trim the polynomial to actual needed size
    vector<int> poly(present.begin(), present.begin() + max_val + 1);
    
    vector<int> result = {1}; // Start with x^0
    
    // Binary exponentiation
    while(k > 0) {
        if(k & 1) {
            result = fft_mul(result, poly);
        }
        poly = fft_mul(poly, poly);
        k >>= 1;
    }
    
    // Output all indices where coefficient is 1
    for(int i = 0; i < (int)result.size(); i++) {
        if(result[i] > 0) {
            cout << i << " ";
        }
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}