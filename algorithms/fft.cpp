#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef complex<double> complejo;
const double pi = 3.14159265358979;

vector<complejo> fft(vector<complejo> &a, bool inverse=false){
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

void convolution(vector<long long> V1, vector<long long> V2, vector<long long> &V3){
	vector<complejo> A, B, C, C1, C2, Z;

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
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(NULL);
	int n1,n2;
	vector<int> alp = {'A', 'C', 'T', 'G'};
	string cad1, cad2;
	cin>>cad1>>cad2;
	n1 = cad1.size();
	n2 = cad2.size();

	vector<int> acu(n1,0);
	vector<long long> V1, V2, V3;
	V1.resize(n1); V2.resize(n2);
	for(int l=0; l<alp.size(); l++){
		for(int i=0; i<n1; i++){
			if(cad1[i] == alp[l]) V1[i] = 1;
			else V1[i] = 0;
		} 
		for(int i=0; i<n2; i++){
			if(cad2[i] == alp[l]) V2[i] = 1;
			else V2[i] = 0;
		}
		convolution(V1, V2, V3);

		for(int i=n2-1; i<=n1-1; i++)
		acu[i] += V3[i];
	}

	int mayor = 0;
	for(int i=n2-1; i<n1; i++)
	mayor = max(mayor, acu[i]);

	int ans = n2 - mayor;
	cout<<ans<<endl;
}