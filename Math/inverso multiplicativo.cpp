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

int inverso_multiplicativo(int n, int p){
	extendedEuclid(n,p);
	return x;
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(NULL);
	int im = inverso_multiplicativo(2,5);
	//cout<<mcd<<" "<<x<<" "<<y<<endl;
	cout<<x<<" "<<y<<endl;
}