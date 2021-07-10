#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf 1e9

struct arista{
	int x, y, w;
	arista(int _x, int _y, int _w) : x(_x), y(_y), w(_w) {}
};

const int maxNodos = 101000;
int numeroNodos;
vector<int> Grafo[maxNodos];
vector<int> D(maxNodos), P(maxNodos);

void bfs(int s){
	queue<int> Q;
	for(int i=0; i<numeroNodos; i++){
		D[i] = inf;
		P[i] = -1;
	}
	D[s] = 0;
	Q.push(s);
	while(!Q.empty()){
		int x = Q.front();
		Q.pop();
		for(int i=0; i<Grafo[x].size(); i++){
			int y = Grafo[x][i];
			if(D[y] == inf){
				D[y] = D[x] + 1;
				P[y] = x;
				Q.push(y);
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int numeroAristas,x,y;
	cin>>numeroNodos>>numeroAristas;
	for(int i=0; i<numeroAristas; i++){
		cin>>x>>y;
		x--; y--;
		Grafo[x].push_back(y);
		Grafo[y].push_back(x);
	}
	bfs(0);
	for(int i=0; i<numeroNodos; i++){ cout<<D[i]<<" "; }	cout<<endl;
	for(int i=0; i<numeroNodos; i++){ cout<<P[i]<<" "; }	cout<<endl;
}