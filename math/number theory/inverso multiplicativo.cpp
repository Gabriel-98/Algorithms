#include<bits/stdc++.h>
using namespace std;
#define endl '\n'

// ax + by = mcd
// datos de entrada: a, b
// datos de salida: x, y, mcd
void extendedEuclid(long long a, long long b, long long &x, long long &y, long long &mcd){
	if(b == 0){
		x = 1;
		y = 0;
		mcd = a;
	}
	else{
		extendedEuclid(b, a % b, x, y, mcd);
		x = y;
		y = (mcd - a*x) / b;
	}
}

// [a*im mod p] = mcd(a,p)
// [a*(a^(-1)) mod p] = mcd(a,p)
// im = a^(-1)  
long long inverso_multiplicativo(long long n, long long mod){
	long long x, y, mcd;
	extendedEuclid(n, mod, x, y, mcd);
	if(x < 0)
	x += mod;
	return x;
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(NULL);
	int im = inverso_multiplicativo(5654,848178);
	cout<<im<<endl;
}