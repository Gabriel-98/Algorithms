#include<bits/stdc++.h>
using namespace std;
#define endl '\n'

const int maxNodos = 101000;
int numeroNodos;
vector<int> Grafo[maxNodos];


vector<int> topologicalSort(){
	int x,y;
	queue<int> Q;
	vector<int> inputEdges(maxNodos, 0), sequence;
	for(x=0; x<numeroNodos; x++){
		for(int i=0; i<Grafo[x].size(); i++){
			inputEdges[Grafo[x][i]]++;
		}
	}
	for(x=0; x<numeroNodos; x++){
		if(inputEdges[x] == 0)
		Q.push(x);
	}
	while(!Q.empty()){
		x = Q.front();
		Q.pop();
		sequence.push_back(x);
		for(int i=0; i<Grafo[x].size(); i++){
			y = Grafo[x][i];
			if(inputEdges[y] > 0){
				inputEdges[y]--;
				if(inputEdges[y] == 0)
				Q.push(y);
			}
		}
	}
	for(x=0; x<numeroNodos; x++){
		if(inputEdges[x] > 0)
		return {};
	}
	return sequence;
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(NULL);
	int numeroAristas,x,y,i;
	cin>>numeroNodos>>numeroAristas;
	for(i=0; i<numeroAristas; i++){
		cin>>x>>y;
		Grafo[x].push_back(y);
	}
	vector<int> ans = topologicalSort();
	for(i=0; i<ans.size(); i++){ cout<<ans[i]<<" "; }	cout<<endl;
}