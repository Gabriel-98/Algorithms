#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef complex<double> complejo;
const double pi = 3.14159265358979;

vector<complejo> fft(vector<complejo> a, bool inverse=false){
	int n = a.size();
	complejo wn, w;

	vector<complejo> y(n), ytemp(n);
	for(int i=0; i<n; i++){ y[i] = a[i]; }
	for(int i=n/2; i>=1; i/=2){
		for(int j=0; j<n; j++){
			ytemp[j] = y[j];
		}
		for(int j=0; j<i; j++){
			if(inverse)
			wn = complejo(cos(2*pi/(n/i)), -sin(2*pi/(n/i)));
			else
			wn = complejo(cos(2*pi/(n/i)), sin(2*pi/(n/i)));

			w = 1.0;
			int k1,k2;
			k1 = j;
			k2 = j+i;
			for(int l=j; l<(n/2); l+=i){
				complejo p1,p2;
				p1 = ytemp[k1] + w*ytemp[k2];
				p2 = ytemp[k1] - w*ytemp[k2];
				y[l] = p1;
				y[l+(n/2)] = p2;
				w *= wn;
				k1 += 2*i;
				k2 += 2*i;
			}
			if(inverse){
				//for(int k=0; k<n; k++){ y[k] /= 2.0; }
			}
		}
	}
	if(inverse){
		for(int i=0; i<n; i++){ y[i] /= n; }
	}
	return y;
}

vector<complejo> A, B, C, C1, C2, Z;
vector<int> V1, V2, V3;

vector<int> convolution(vector<int> V1, vector<int> V2){
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
