#include<bits/stdc++.h>
using namespace std;
#define endl '\n'

struct SegmentTreeLP{

	long long n;
	vector<long long> vect;
	vector<long long> T;
	vector<long long> finalized;
	vector<long long> propagation;

	long long funcion(long long a, long long b){
		return a + b;
	}

	long long funcionIntervalo(int pos, int x, int y, long long valor){
		return T[pos] + (y+1-x)*valor;
	}

	void funcionPropagation(int pos, long long valor){
		if(finalized[pos] == 0)
		propagation[pos] = valor;
		else
		propagation[pos] += valor;
	}

	void build(vector<long long> V){
		vect.clear();
		vect.resize(V.size());
		for(int i=0; i<vect.size(); i++){
			vect[i] = V[i];
		}
		n = log2(V.size()-1) + 2;
		n = pow(2,n);
		T.clear();
		T.resize(n,0);
		finalized.clear();
		finalized.resize(n,0);
		propagation.clear();
		propagation.resize(n,0);
		build2(1,0,vect.size()-1);
	}

	void build2(int pos, int i, int j){
		if(i==j)
		T[pos] = vect[i];
		else{
			build2(2*pos, i, (i+j)/2);
			build2(2*pos+1, (i+j+2)/2, j);
			T[pos] = funcion(T[2*pos], T[2*pos+1]);
		}
	}

	void update(int i, int j, long long valor){
		update2(1,0,vect.size()-1, i,j, valor);
	}

	void update2(int pos, int x, int y, int i, int j, long long valor){
		if(i<=x && y<=j){
			funcionPropagation(pos, valor);
			T[pos] = funcionIntervalo(pos, x,y, propagation[pos]);
			finalized[pos] = 0;
			if(2*pos < n){
				funcionPropagation(2*pos, propagation[pos]);
				finalized[2*pos] = 1;
			}
			if(2*pos+1 < n){
				funcionPropagation(2*pos+1, propagation[pos]);
				finalized[2*pos+1] = 1;
			}
		}
		else if(!(x>j || y<i)){
			if(finalized[pos] == 1){
				if(2*pos < n){
					funcionPropagation(2*pos, propagation[pos]);
					finalized[2*pos] = 1;
				}
				if(2*pos+1 < n){
					funcionPropagation(2*pos+1, propagation[pos]);
					finalized[2*pos+1] = 1;
				}
				T[pos] = funcionIntervalo(pos, x,y, propagation[pos]);
			}
			T[pos] = funcionIntervalo(pos, max(i,x),min(j,y), valor);
			finalized[pos] = 0;
			update2(2*pos, x,(x+y)/2, i,j, valor);
			update2(2*pos+1, (x+y+2)/2,y, i,j, valor);
		}
	}

	long long query(int i, int j){
		return query2(1, 0,vect.size()-1, i,j);
	}

	long long query2(int pos, int x, int y, int i, int j){
		if(j<x || i>y)
		return 0;
		else if(i<=x && y<=j){
			if(finalized[pos] == 1){
				T[pos] = funcionIntervalo(pos, x,y, propagation[pos]);
				finalized[pos] = 0;
				if(2*pos < n){
					funcionPropagation(2*pos, propagation[pos]);
					finalized[2*pos] = 1;
				}
				if(2*pos+1 < n){
					funcionPropagation(2*pos+1, propagation[pos]);
					finalized[2*pos+1] = 1;
				}
			}
			return T[pos];
		}
		else{
			if(finalized[pos] == 1){
				if(2*pos < n){
					funcionPropagation(2*pos, propagation[pos]);
					finalized[2*pos] = 1;
				}
				if(2*pos+1 < n){
					funcionPropagation(2*pos+1, propagation[pos]);
					finalized[2*pos+1] = 1;
				}
				T[pos] = funcionIntervalo(pos, x,y, propagation[pos]);
				finalized[pos] = 0;
			}
			return funcion(query2(2*pos, x,(x+y)/2, i,j), query2(2*pos+1, (x+y+2)/2,y, i,j));
		}
	}

	void print(){
		for(int i=1; i<n; i++){
			cout<<"\t"<<i<<" "<<T[i]<<endl;
		}
	}
};


vector<long long> V;
struct SegmentTreeLP st;

int main(){
	ios_base::sync_with_stdio(0);cin.tie(NULL);
	long long t,n,q,op,x,y,k,i;
	cin>>t;
	while(t--){
		cin>>n>>q;
		V.clear();
		V.resize(n+1,0);
		st.build(V);
		while(q--){
			cin>>op>>x>>y;
			if(op == 0){
				cin>>k;
				st.update(x,y,k);
			}
			else
			cout<<st.query(x,y)<<endl;
		}
	}
}
