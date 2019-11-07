#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef pair<vector<int>, vector<int>> vector2;

const int maxN1 = 11000;
const int maxN2 = 2000;
int DP[maxN1][maxN2];


vector2 lcs(string cad1, string cad2){
	vector<int> pos1, pos2;
	for(int i=0; i<cad1.size(); i++){
		for(int j=0; j<cad2.size(); j++){
			DP[i][j] = 0;
			if(i == 0 || j == 0){
				if(cad1[i] == cad2[j])
				DP[i][j] = 1;
			}
			if(i-1 >= 0){
				if(DP[i-1][j] > DP[i][j])
				DP[i][j] = DP[i-1][j];
			}
			if(j-1 >= 0){
				if(DP[i][j-1] > DP[i][j])
				DP[i][j] = DP[i][j-1];
			}
			if(i-1 >= 0 && j-1 >= 0 && (cad1[i] == cad2[j])){
				if(DP[i-1][j-1] + 1 > DP[i][j])
				DP[i][j] = DP[i-1][j-1] + 1;
			}
		}
	}
	int i,j;
	i = cad1.size()-1;
	j = cad2.size()-1;
	while(i >= 0 && j >= 0 && DP[i][j] >= 1){
		if(cad1[i] == cad2[j]){
			pos1.push_back(i);
			pos2.push_back(j);
			i--;
			j--;
		}
		else{
			if(i-1 >= 0 && DP[i-1][j] == DP[i][j])
			i--;
			else if(j-1 >= 0 && DP[i][j-1] == DP[i][j])
			j--;
			else{
				i--; j--;
			}
		}
	}
	reverse(pos1.begin(), pos1.end());
	reverse(pos2.begin(), pos2.end());
	return vector2(pos1, pos2);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	string cad1, cad2;
	cin>>cad1>>cad2;
	vector2 ans = lcs(cad1, cad2);
	cout<<"longitud: "<<ans.first.size()<<endl;
	for(int i=0; i<ans.first.size(); i++){ cout<<ans.first[i]<<" "; } cout<<endl;
	for(int i=0; i<ans.second.size(); i++){ cout<<ans.second[i]<<" "; } cout<<endl;
}