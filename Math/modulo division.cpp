#include<bits/stdc++.h>
using namespace std;
#define endl '\n'

int x, y, mcd;

void extendedEuclid(int a, int b){
	if(b == 0){
		x = 1;
		y = 0;
		mcd = a;
	}
	else{
		extendedEuclid(b, a % b);
		x = y;
		y = (mcd - a*x) / b;
	}
}

// retorna (a/b) mod m
long long moduloDivision(long long a, long long b, long long modulo){
	if(a % b != 0)
	return -1;	// Division inexacta
	extendedEuclid(b,modulo);
	if(x < 0)
	x += modulo;
	return (x * (a / mcd)) % modulo;
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(NULL);
	int a,b,mod,ans;
	cin>>a>>b>>mod;
	ans = moduloDivision(a,b,mod);
	if(ans == -1)
	cout<<"La division es inexacta"<<endl;
	else
	cout<<ans<<endl;
}