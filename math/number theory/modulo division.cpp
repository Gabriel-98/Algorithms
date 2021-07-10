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

// retorna (a/b) mod m
// a*(b^(-1)) mod m
long long moduloDivision(long long a, long long b, long long modulo){
	long long x, y, mcd;
	extendedEuclid(b, modulo, x, y, mcd);
	if(x < 0)
	x += modulo;
	return (x * (a / mcd)) % modulo;
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(NULL);
	int a,b,mod,ans;
	cin>>a>>b>>mod;
	ans = moduloDivision(a,b,mod);
	cout<<ans<<endl;
}