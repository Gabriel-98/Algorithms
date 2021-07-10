/*
Estrurctura: Trie
El trie almacena un conjunto de claves
Esta estructura con
Cada nodo del trie contiene un vector que contiene todos los simbolos del alfabeto, y
*/
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'


const int numeroSimbolos = 26;

class Nodo{
	private:
		int idSimbolo;
		bool esTerminal;
		int nivel;
		Nodo *children[numeroSimbolos];
	public:
		Nodo();
		Nodo(int idSimbolo, int nivel, bool esTerminal);
		void setFinalizador();
		Nodo* getChild(int idSimbolo);
		void newChild(int idSimbolo, Nodo *child);
		int getIdSimbolo();
		int accepted();
		int getNivel();
};

class Trie{
	private:
		Nodo *raiz;
		int numeroNodos;
		int numeroPalabras;
		int traductor[256];
		vector<char> alp = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
					'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
		
	public:
		const int numeroSimbolos = 26;
		Trie();
		void insert(string cad);
		int find(string cad);
		void print();
		void print2(Nodo *p);
		void printWords();
		int size();
};

Nodo::Nodo(){
	this->esTerminal = false; 
	this->nivel = -1;
	for(int i=0; i<numeroSimbolos; i++){
		children[i] = NULL;
	}
}

Nodo::Nodo(int idSimbolo, int nivel, bool esTerminal){
	this->idSimbolo = idSimbolo;
	this->nivel = nivel;
	this->esTerminal = esTerminal;
	for(int i=0; i<numeroSimbolos; i++){
		children[i] = NULL;
	}
}

void Nodo::setFinalizador(){
	esTerminal = true;
}

Nodo* Nodo::getChild(int idSimbolo){
	return children[idSimbolo];
}

void Nodo::newChild(int idSimbolo, Nodo *child){
	children[idSimbolo] = child;
}

int Nodo::getIdSimbolo(){
	return idSimbolo;
}

int Nodo::accepted(){
	return esTerminal;
}

int Nodo::getNivel(){
	return nivel;
}

Trie::Trie(){
	for(int i=0; i<256; i++){
		traductor[i] = -1;
	}
	for(int i=0; i<alp.size(); i++){
		traductor[alp[i]] = i;
	}
	raiz = new Nodo(-1, 0, false);
	numeroNodos = 0;
	numeroPalabras = 0;
}

void Trie::insert(string cad){
	int i=0;
	Nodo *p, *q, *r;
	p = raiz;
	q = p;
	numeroPalabras++;
	for(int i=0; i<cad.size(); i++){
		r = new Nodo(traductor[cad[i]], i+1, i + 1 == cad.size());
		if(q == raiz)
		q = p->getChild(traductor[cad[i]]);
		
		if(q == NULL){
			p->newChild(traductor[cad[i]], r);
			numeroNodos++;
		}
		
		p = p->getChild(traductor[cad[i]]);
		if(i < cad.size())
		q = p->getChild(traductor[cad[i+1]]);
	}
	p->setFinalizador();
}

int Trie::find(string cad){
	int i=0;
	Nodo *p = raiz;
	for(i=0; i < cad.size() && p != NULL; i++){
		p = p->getChild(traductor[cad[i]]);
	}
	return i == cad.size() && p != NULL && p->accepted();
}

void Trie::print2(Nodo *p){
	if(p != NULL){
		if(p != raiz)
		cout<<alp[p->getIdSimbolo()];
		for(int i=0; i<numeroSimbolos; i++){
			print2(p->getChild(i));
		}
	}	
}

void Trie::print(){
	print2(raiz);
	cout<<endl;
}

void Trie::printWords(){
	Nodo *p,*q;
	stack<Nodo *> S;
	string word = "";
	S.push(raiz);
	while(!S.empty()){
		p = S.top();
		S.pop();
		for(int i=numeroSimbolos-1; i>=0; i--){
			q = p->getChild(i);
			if(q != NULL)
			S.push(q);
		}
		if(p != raiz){
			if(p->getNivel() == word.size() + 1)
			word.push_back(alp[p->getIdSimbolo()]);
			else{
				while(p->getNivel() < word.size() + 1){
					word.pop_back();
				}
				word.push_back(alp[p->getIdSimbolo()]);
			}
		}
		if(p->accepted())
		cout<<word<<endl;
	}
}

int Trie::size(){
	return numeroPalabras;
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(NULL);
	Trie trie = Trie();
	trie.insert("bear");
	trie.insert("bell");
	trie.insert("bid");
	trie.insert("bull");
	trie.insert("buy");
	trie.insert("sell");
	trie.insert("stock");
	trie.insert("stop");
	trie.print();
	trie.printWords();
}