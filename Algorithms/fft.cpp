#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef complex<double> complejo;
const double pi = 3.14159265358979;

vector<complejo> fft(vector<complejo> a, bool inverse=false){
	int n = a.size();
	if(n == 1)
	return a;

	complejo wn, w;
	if(inverse)
	wn = complejo(cos(2*pi/n), -sin(2*pi/n));
	else
	wn = complejo(cos(2*pi/n), sin(2*pi/n));
	w = 1.0;

	vector<complejo> aEven(n/2), aOdd(n/2);
	vector<complejo> yEven, yOdd, y(n);

	for(int i=0,j1=0,j2=1; i<n/2; i++,j1+=2,j2+=2){
		aEven[i] = a[j1];
		aOdd[i] = a[j2];
	}

	yEven = fft(aEven, inverse);
	yOdd = fft(aOdd, inverse);

	for(int i=0,j=n/2; i<n/2; i++,j++){
		y[i] = yEven[i] + w*yOdd[i];
		y[j] = yEven[i] - w*yOdd[i];
		w *= wn;
	}
	if(inverse){
		for(int i=0; i<n; i++){ y[i] /= 2.0; }
	}

	return y;
}

vector<complejo> A, B, C, C1, C2, Z;
vector<long long> V1, V2, V3;

vector<long long> convolution(vector<long long> V1, vector<long long> V2){
	int n,pot;
	n = 2 * max(V1.size(), V2.size());
	pot = pow(2, int(log2(n)));
	if(n > pot)
	n = 2*pot;
	
	A.resize(n,0); 	B.resize(n,0);
	for(int i=0; i<V1.size(); i++){ A[i] = V1[i]; }
	for(int i=0,j=V2.size()-1; i<V2.size(); i++,j--){ B[i] = V2[j]; }
	C1 = fft(A);
	C2 = fft(B);
	C.resize(n);
	for(int i=0; i<n; i++){ C[i] = C1[i] * C2[i]; }
	Z = fft(C, true);

	V3.clear();
	for(int i=0; i<n; i++){
		double x = round(real(Z[i]));
		V3.push_back(x);
	}
	return V3;
}

vector<long long> ans;

int main(){
	ios_base::sync_with_stdio(0);cin.tie(NULL);
	int n,x,y,i;
	cin>>n>>x;
	V1.push_back(1);
	for(i=0; i<n; i++){
		cin>>y;
		if(y < x)
		V1.push_back(1);
		else
		V1[V1.size()-1]++;
	}
	for(i=0; i<V1.size(); i++){ V2.push_back(V1[i]); }
	V2[V2.size()-1] = V1[V1.size()-1]-1;
	convolution(V1, V2);
	for(i=V1.size()-1; i<(2*V1.size()) && ans.size() <= n; i++){ ans.push_back(V3[i]); }
	for(i=ans.size(); i<=n; i++){ ans.push_back(0); }

	for(i=0; i<V2.size(); i++){
		ans[0] -= V2[i]*V2[i];
		ans[0] += (V2[i]*(V2[i]-1))/2;
	}

	for(i=0; i<ans.size(); i++){
		if(i > 0)
		cout<<" ";
		cout<<ans[i];
	}
	cout<<endl;
}