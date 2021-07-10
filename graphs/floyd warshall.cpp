#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf 1e9

const int maxNodos = 100;
int numeroNodos;
int Grafo[maxNodos][maxNodos];
int D[maxNodos][maxNodos];

void floydWarshall(){
	for(int i=0; i<numeroNodos; i++){
		for(int j=0; j<numeroNodos; j++){
			D[i][j] = Grafo[i][j];
		}
	}
	for(int k=0; k<numeroNodos; k++){
		for(int i=0; i<numeroNodos; i++){
			for(int j=0; j<numeroNodos; j++){
				if((D[i][k] + D[k][j]) < D[i][j])
				D[i][j] = D[i][k] + D[k][j];
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(NULL);
	int numeroAristas,x,y,s,t,w;
	cin>>numeroNodos>>numeroAristas;
	for(int i=0; i<numeroNodos; i++){
		for(int j=0; j<numeroNodos; j++){
			Grafo[i][j] = inf;
		}
		Grafo[i][i] = 0;
	}
	for(int i=0; i<numeroAristas; i++){
		cin>>x>>y>>w;
		x--; y--;
		if(w < Grafo[x][y]){
			Grafo[x][y] = w;
			Grafo[y][x] = w;
		}
	}
	floydWarshall();
	for(int i=0; i<numeroNodos; i++){
		for(int j=0; j<numeroNodos; j++){
			cout<<D[i][j]<<"\t";
		}
		cout<<endl;
	}
}