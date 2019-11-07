#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

vector<int> prefixFunctionKMP(string cadena){
	vector<int> prefixFunction(cadena.size());
	prefixFunction[0] = 0;
	for(int i=1,j=0; i<cadena.size(); i++){
		while(j > 0 && cadena[i] != cadena[j]){
			j = prefixFunction[j-1];
		}
		if(cadena[i] == cadena[j])
		j++;
		prefixFunction[i] = j;
	}
	return prefixFunction;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	string cadena;
	cin>>cadena;
	vector<int> prefixFunction = prefixFunctionKMP(cadena);
	for(int i=0; i<prefixFunction.size(); i++){
		cout<<prefixFunction[i]<<" ";
	}
	cout<<endl;
}