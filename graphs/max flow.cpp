#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef pair<int,int> par;
#define inf 1e9

struct arista{
	int x, y, capacidad, enviado, costo;
};


const int maxNodos = 110;
const int maxAristas = 5100;
int numeroNodos;
int numeroAristas;
vector<arista> aristas(maxAristas);
vector<int> grafo[maxNodos + 1];

// s = 0, t = n-1
par dijkstraMaxFlow(){
	vector<int> S(maxNodos,inf), flujo(maxNodos, inf), Parista(maxNodos,-1);
	queue<int> Q;
	int s = 0, t = numeroNodos-1;
	S[s] = 0;
	Q.push(s);
	while(!Q.empty()){
		int x = Q.front();
		Q.pop();
		for(int i=0; i<grafo[x].size(); i++){
			int pos = grafo[x][i];
			if(aristas[pos].x == x){		// arista original
				if(aristas[pos].enviado < aristas[pos].capacidad){
					int y = aristas[pos].y;
					int w = aristas[pos].costo;
					if(S[x] + w < S[y]){
						S[y] = S[x] + w;
						flujo[y] = min(flujo[x], aristas[pos].capacidad - aristas[pos].enviado);
						Parista[y] = pos;
						Q.push(y);
					}
				}
			}
			else{			// arista para revertir
				if(aristas[pos].enviado > 0){
					int y = aristas[pos].x;
					int w = -aristas[pos].costo;
					if(S[x] + w < S[y]){
						S[y] = S[x] + w;
						flujo[y] = min(flujo[x], aristas[pos].enviado);
						Parista[y] = pos;
						Q.push(y);
					}
				}
			}
		}
	}
	//for(int i=0; i<numeroNodos; i++)
	//cout<<i<<" "<<S[i]<<endl;


	if(S[t] != inf){
		int x = t;
		int costo = 0;
		while(x != s){
			if(aristas[Parista[x]].x != x){
				aristas[Parista[x]].enviado += flujo[t];
				costo += aristas[Parista[x]].costo * flujo[t];
				x = aristas[Parista[x]].x;				
			}
			else{
				aristas[Parista[x]].enviado -= flujo[t];
				costo -= aristas[Parista[x]].costo * flujo[t];
				x = aristas[Parista[x]].y;				
			}
		}

		//cout<<"flujo: "<<flujo[t]<<endl;
		return par(flujo[t], costo);
	}
	else
	return par(0, 0);
}


int maxFlowMinCost(){
	int costo = 0;
	par p = dijkstraMaxFlow();
	while(p.first != 0){
		costo += p.second;
		p = dijkstraMaxFlow();
	}
	return costo;
}


int main(){
	ios_base::sync_with_stdio(0);cin.tie(NULL);
	int n,q,op,l,r,v,cond = 1;
	cin>>n>>q;
	vector<int> ini(n+1, 1), fin(n+1, n);
	while(q--){
		cin>>op>>l>>r>>v;
		if(op == 1){
			for(int i=l; i<=r; i++)
			ini[i] = max(ini[i], v);
		}
		else{
			for(int i=l; i<=r; i++)
			fin[i] = min(fin[i], v);
		}
	}
	for(int i=1; i<=n; i++){
		if(ini[i] > fin[i]){
			cond = 0;
			break;
		}
	}

	if(cond == 0)
	cout<<-1<<endl;
	else{
		// construir la red
		numeroNodos = 2*n + 2;
		numeroAristas = 0;
		for(int i=1; i<=n; i++){
			aristas[numeroAristas].x = 0;
			aristas[numeroAristas].y = i;
			aristas[numeroAristas].capacidad = 1;
			aristas[numeroAristas].enviado = 0;
			aristas[numeroAristas].costo = 0;
			numeroAristas++;
		}
		for(int i=1; i<=n; i++){
			for(int j=ini[i]; j<=fin[i]; j++){
				aristas[numeroAristas].x = i;
				aristas[numeroAristas].y = n + j;
				aristas[numeroAristas].capacidad = 1;
				aristas[numeroAristas].enviado = 0;
				aristas[numeroAristas].costo = 0;
				numeroAristas++;
			}
		}
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				aristas[numeroAristas].x = n+i;
				aristas[numeroAristas].y = 2*n + 1;
				aristas[numeroAristas].capacidad = 1;
				aristas[numeroAristas].enviado = 0;
				aristas[numeroAristas].costo = j*j - (j-1)*(j-1);
				numeroAristas++;
			}
		}

		for(int i=0; i<numeroAristas; i++){
			grafo[aristas[i].x].push_back(i);
			grafo[aristas[i].y].push_back(i);
		}

		int ans = maxFlowMinCost();
		cout<<ans<<endl;
	}
}