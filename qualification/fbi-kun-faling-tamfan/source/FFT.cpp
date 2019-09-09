#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);
typedef complex<double> base;
vector<int> plya,plyb,ans;

void fft (vector<base> & a, bool invert) {
	int n = (int) a.size();
	for (int i=1, j=0; i<n; ++i) {
		int bit = n >> 1;
		for (; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}
	for (int len=2; len<=n; len<<=1) {
		double ang = 2*PI/len * (invert ? -1 : 1);
		base wlen (cos(ang), sin(ang));
		for (int i=0; i<n; i+=len) {
			base w (1);
			for (int j=0; j<len/2; ++j) {
				base u = a[i+j],  v = a[i+j+len/2] * w;
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert)
		for (int i=0; i<n; ++i)
			a[i] /= n;
}
 
void multiply (const vector<int> &a, const vector<int> &b, vector<int> &res){
    vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n = 1;
	while (n < max (a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize (n),  fb.resize (n);
	fft (fa, false),  fft (fb, false);
	for (size_t i=0; i<n; ++i)
		fa[i] *= fb[i];
	fft (fa, true);
	res.resize (n);
	for (size_t i=0; i<n; ++i)
		res[i] = int (fa[i].real() + 0.5);
}

int main(){
	cout<<"Give me 100000 fantastic numbers!\n";
	for (int i=0; i<=100000; i++){
		int tmp;
		cin>>tmp;
		plyb.push_back(tmp);	
	}
    freopen("magic_numbers.txt", "r", stdin);
	for (int i=0; i<=100000; i++){
		int tmp;
		cin>>tmp;
		plya.push_back(tmp);
	}

	multiply(plya, plyb, ans);
	for(int i=0; i<=200000; i++){
		int tmp;
		cin>>tmp;
		if(tmp!=ans[i]){
			cout<<tmp<<' '<<ans[i]<<' '<<"NO FLAGS FOR U PLEBS!!!\n";
			return 0;
		}
	}
	fclose(stdin);
	cout<<"Verdict : Accepted"<<endl;
	return 0;
}