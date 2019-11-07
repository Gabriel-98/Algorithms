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
vector<arista> Grafo[maxNodos];
vector<int> D(maxNodos), P(maxNodos);

void dijkstra(int s){
	int x,y,w;
	for(int i=0; i<numeroNodos; i++){
		D[i] = inf;
		P[i] = -1;
	}
	D[s] = 0;
	queue<int> Q;
	Q.push(s);
	while(!Q.empty()){
		x = Q.front();
		Q.pop();
		for(int i=0; i<Grafo[x].size(); i++){
			y = Grafo[x][i].y;
			w = Grafo[x][i].w;
			if(D[x] + w < D[y]){
				D[y] = D[x] + w;
				P[y] = x;
				Q.push(y);
			}

		}
	}
}

bool operator < (arista a, arista b){ return a.w > b.w; }

void dijkstra2(int s){
	int x,y;
	long long w;
	for(int i=0; i<numeroNodos; i++){
		D[i] = inf;
		P[i] = -1;
	}
	D[s] = 0;
	priority_queue<arista> PQ;
	for(int i=0; i<Grafo[s].size(); i++){
		y = Grafo[s][i].y;
		w = Grafo[s][i].w;
		PQ.push(arista(s,y,w));
	}
	while(!PQ.empty()){
		arista a = PQ.top();
		PQ.pop();
		x = a.x;	y = a.y;	w = a.w;
		if(w < D[y]){
			D[y] = w;
			P[y] = x;
			for(int i=0; i<Grafo[y].size(); i++){
				PQ.push(arista(y, Grafo[y][i].y, D[y] + Grafo[y][i].w));
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int numeroAristas,x,y,s,t,w;
	cin>>numeroNodos>>numeroAristas;
	for(int i=0; i<numeroAristas; i++){
		cin>>x>>y>>w;
		x--; y--;
		Grafo[x].push_back(arista(x,y,w));
	}
	dijkstra(0);
	for(int i=0; i<numeroNodos; i++){ cout<<D[i]<<" "; } cout<<endl;
}