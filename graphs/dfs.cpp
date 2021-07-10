#include<bits/stdc++.h>
using namespace std;
#define endl '\n'

struct arista{
	int x, y, w;
	arista(int _x, int _y, int _w) : x(_x), y(_y), w(_w) {}
};

const int maxNodos = 101000;
int numeroNodos;
vector<int> Grafo[maxNodos];
vector<int> S(maxNodos), inicio(maxNodos), fin(maxNodos);
vector<int> sequence;

void dfs_visit(int x){
	S[x] = 1;
	for(int i=0; i<Grafo[x].size(); i++){
		int y = Grafo[x][i];
		if(S[y] == 0){
			sequence.push_back(x);
			dfs_visit(y);
		}
	}
	sequence.push_back(x);
}

void dfs(){
	for(int x=0; x<numeroNodos; x++){
		S[x] = 0;
		inicio[x] = -1;
		fin[x] = -1;
	}
	for(int x=0; x<numeroNodos; x++){
		if(S[x] == 0){
			dfs_visit(x);
		}
	}
	for(int i=0; i<sequence.size(); i++){
		int x = sequence[i];
		if(inicio[x] == -1)
		inicio[x] = i;
		fin[x] = i;
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
	dfs();
	for(int i=0; i<sequence.size(); i++){ cout<<sequence[i]+1<<" "; }	cout<<endl;
	for(int i=0; i<numeroNodos; i++){ cout<<i<<" \t-\t "<<inicio[i]<<" "<<fin[i]<<endl; }
}