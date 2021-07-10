#include<bits/stdc++.h>
using namespace std;
#define endl '\n'

struct arista{
	int x, y, w;
	arista(int _x, int _y, int _w) : x(_x), y(_y), w(_w) {}
};

int functionSortArista(arista a, arista b){ return a.w < b.w; }

const int maxNodos = 101000;
int numeroNodos;
vector<arista> Grafo[maxNodos];
vector<arista> GrafoMST[maxNodos];
list<int> conjuntos[maxNodos];
vector<int> idConjunto(maxNodos);

void inicializarDisjointSet(int n){
	for(int i=0; i<n; i++){
		conjuntos[i].push_back(i);
		idConjunto[i] = i;
	}
}

int buscar(int x){ return idConjunto[x]; }

void mezclar(int id1, int id2){
	if(conjuntos[id1].size() >= conjuntos[id2].size()){
		for(list<int>::iterator it=conjuntos[id2].begin(); it!=conjuntos[id2].end(); it++){
			int x = *it;
			conjuntos[id1].push_back(x);
			idConjunto[*it] = id1;
		}
		conjuntos[id2].clear();
	}
	else{
		for(list<int>::iterator it=conjuntos[id1].begin(); it!=conjuntos[id1].end(); it++){
			int x = *it;
			conjuntos[id2].push_back(x);
			idConjunto[*it] = id2;
		}
		conjuntos[id1].clear();
	}
}

int kruskal(){
	int costo = 0;
	vector<arista> aristas;
	for(int x=0; x<numeroNodos; x++){
		for(int i=0; i<Grafo[x].size(); i++){
			aristas.push_back(Grafo[x][i]);
		}
	}
	inicializarDisjointSet(numeroNodos);
	sort(aristas.begin(), aristas.end(), functionSortArista);
	for(int i=0; i<aristas.size(); i++){
		int x = aristas[i].x, y = aristas[i].y, w = aristas[i].w;
		if(buscar(x) != buscar(y)){
			mezclar(buscar(x), buscar(y));
			GrafoMST[x].push_back(arista(x,y,w));
			GrafoMST[y].push_back(arista(y,x,w));
			costo += w;
		}
	}
	return costo;
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int numeroAristas,x,y,s,t,w;
	cin>>numeroNodos>>numeroAristas;
	for(int i=0; i<numeroAristas; i++){
		cin>>x>>y>>w;
		x--; y--;
		Grafo[x].push_back(arista(x,y,w));
		Grafo[y].push_back(arista(y,x,w));
	}
	int costo = kruskal();
	cout<<"costo: "<<costo<<endl;
	for(int i=0; i<numeroNodos; i++){
		cout<<i<<" \t->\t ";
		for(int j=0; j<GrafoMST[i].size(); j++){
			cout<<"("<<GrafoMST[i][j].y<<","<<GrafoMST[i][j].w<<") ";
		}
		cout<<endl;
	}
}