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

int main(){
	ios_base::sync_with_stdio(0);cin.tie(NULL);
	extendedEuclid(73,194);
	cout<<mcd<<" "<<x<<" "<<y<<endl;
}

/*
int main(){
	ios_base::sync_with_stdio(0);cin.tie(NULL);
	int k,n,a,b,c;
	cin>>a>>b>>c;
	extendedEuclid(a,b);
	if(a < b){
		k = a;
		a = b;
		b = k;
	}
	if(c % mcd != 0)
	cout<<"No"<<endl;
	else{
		x *= c / mcd;
		y *= c / mcd;
		// Restingir a ser mayor o igual a 0
		n = abs(y) / (a/mcd);
		if(abs(y) % (a/mcd) != 0)
		n++;
		x -= (b/mcd) * n;
		y += (a/mcd) * n;
		if(a*x + b*y == c && x >= 0)
		cout<<"Yes"<<endl;
		else
		cout<<"No"<<endl;
	}
}
*/