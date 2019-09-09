#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);
typedef complex<double> base;
vector<long long> p1,p2,ans;
long long TC,deg=100000;

void fft(vector<base> &a, bool invert){
    long long n = a.size();
    for (long long i = 1, j = 0; i < n; ++i){
        long long bit = n >> 1;
        for (; j >= bit; bit >>= 1){
            j -= bit;
        }
        j += bit;
        if (i < j){
            swap(a[i], a[j]);
        }
    }
    for (long long len = 2; len <= n; len <<= 1){
        double ang = 2 * PI / len * (invert ? -1 : 1);
        base wlen(cos(ang), sin(ang));
        for (long long i = 0; i < n; i += len){
            base w(1);
            for (long long j = 0; j < len / 2; ++j){
                base u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert){
        for (long long i = 0; i < n; ++i){
            a[i] /= n;
        }
    }
}

void multiply(const vector<long long> &a, const vector<long long> &b, vector<long long> &res){
    vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    size_t n = 1;
    while (n < max(a.size(), b.size())){
        n <<= 1;
    }
    n <<= 1;
    fa.resize(n), fb.resize(n);
    fft(fa, false), fft(fb, false);
    for (size_t i = 0; i < n; ++i){
        fa[i] *= fb[i];
    }
    fft(fa, true);
    res.resize(n);
    for (size_t i = 0; i < n; ++i){
        res[i] = (long long)(fa[i].real() + 0.5);
    }
}

int main(){
    freopen("TC.txt", "r", stdin);
    freopen("AnsTC.txt", "w", stdout);
    p1.clear();
    p2.clear();
    ans.clear();
    for (long long j=0; j<=deg; j++){
        long long tmp;
        cin>>tmp;
        p1.push_back(tmp);
    }
    for (long long j=0; j<=deg; j++){
        long long tmp;
        cin>>tmp;
        p2.push_back(tmp);
    }
    multiply(p1, p2, ans);
    for (long long i=0; i<2*deg+1; i++){
        if (i==2*deg){
            cout<<ans[i]<<"\n";
        } else {
            cout<<ans[i]<<' ';
        }
    }
    fclose(stdout);
    fclose(stdin);
}