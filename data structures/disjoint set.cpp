#include<bits/stdc++.h>
using namespace std;
#define endl '\n'

struct DSU{
	int n;
	int numeroConjuntos;
	vector<list<int>> conjuntos;
	vector<int> idConjunto;

	DSU();
	DSU(int n);

	int find(int x);
	void merge(int id1, int id2);
	int numberOfSets();
};

DSU::DSU(){
	n = 0;
	numeroConjuntos = 0;
}

DSU::DSU(int n){
	this->n = n;
	this->numeroConjuntos = n;
	conjuntos.resize(n);
	idConjunto.resize(n);
	for(int i=0; i<n; i++){
		conjuntos[i].push_back(i);
		idConjunto[i] = i;
	}
}

int DSU::find(int x){
	return idConjunto[x];
}

void DSU::merge(int id1, int id2){
	if(id1 != id2){
		if(conjuntos[id1].size() >= 1 && conjuntos[id2].size() >= 1)
		numeroConjuntos--;
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
}

int DSU::numberOfSets(){
	return numeroConjuntos;
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	DSU dsu(15);
	cout<<dsu.find(8)<<endl;
	dsu.merge(dsu.find(7),dsu.find(8));
	dsu.merge(dsu.find(5),dsu.find(8));
	dsu.merge(dsu.find(7),dsu.find(5));
	dsu.merge(dsu.find(9),dsu.find(11));
	dsu.merge(dsu.find(9),dsu.find(12));
	dsu.merge(dsu.find(12),dsu.find(7));
	cout<<dsu.find(5)<<" "<<dsu.find(7)<<" "<<dsu.find(8)<<endl;
	cout<<dsu.numberOfSets()<<endl;
}