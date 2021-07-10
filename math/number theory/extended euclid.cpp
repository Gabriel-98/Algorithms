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

int main(){
	ios_base::sync_with_stdio(0);cin.tie(NULL);
	long long a, b, x, y, mcd;
	a = 146;
	b = 388;
	extendedEuclid(a, b, x, y, mcd);
	cout<<mcd<<" "<<x<<" "<<y<<endl;
}