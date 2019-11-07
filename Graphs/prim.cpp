#include<bits/stdc++.h>
using namespace std;
#define endl '\n'

struct arista{
	int x, y, w;
	arista(int _x, int _y, int _w) : x(_x), y(_y), w(_w) {}
};

const int maxNodos = 101000;
int numeroNodos;
vector<arista> Grafo[maxNodos];
vector<arista> GrafoMST[maxNodos];
vector<int> S(maxNodos);

bool operator < (arista a, arista b){ return a.w > b.w; }

int prim(){
	int x, y, w, costo = 0;
	priority_queue<arista> PQ;
	for(int i=0; i<numeroNodos; i++){ S[i] = 0; }
	for(int i=0; i<Grafo[0].size(); i++){
		PQ.push(Grafo[0][i]);
	}
	S[0] = 1;
	while(!PQ.empty()){
		arista a = PQ.top();
		PQ.pop();
		x = a.x;	y = a.y;	w = a.w;
		if(S[x] == 0 || S[y] == 0){
			if(S[x] == 0){
				for(int i=0; i<Grafo[x].size(); i++){
					PQ.push(Grafo[x][i]);
				}
			}
			else if(S[y] == 0){
				for(int i=0; i<Grafo[y].size(); i++){
					PQ.push(Grafo[y][i]);
				}
			}
			S[x] = 1;	S[y] = 1;
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
	int costo = prim();
	cout<<"costo: "<<costo<<endl;
	for(int i=0; i<numeroNodos; i++){
		cout<<i<<" \t->\t ";
		for(int j=0; j<GrafoMST[i].size(); j++){
			cout<<"("<<GrafoMST[i][j].y<<","<<GrafoMST[i][j].w<<") ";
		}
		cout<<endl;
	}
}