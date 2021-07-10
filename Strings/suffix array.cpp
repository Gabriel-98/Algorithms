#include<bits/stdc++.h>
using namespace std;

template <typename T>
void clearAndResizeVector1D(int n, vector<T> &v){
	v.clear();
	v.resize(n);
}

template <typename T>
void clearAndResizeArray1D(int n, T *&v){
	v = (T*)malloc(sizeof(T) * n);
}

template <typename T>
void clearAndResizeArray2D(int n1, int n2, T **&v){
	v = (T**)malloc(sizeof(T) * n1 * n2);
	for(int i=0; i<n1; i++)
	v[i] = (T*)malloc(sizeof(T) * n2);
}

int charArraySize(char *arr){
	char *auxArr = arr;
	int size;
	for(size=0; (*auxArr) != 0; auxArr++, size++){}
	return size;
}

char* stringToCharArray(string str){
	char *arr = (char*)malloc(sizeof(char) * (str.size() + 1));
	for(int i=0; i<str.size(); i++)
	arr[i] = str[i];
	arr[str.size()] = 0;
	return arr;
}


class CharComparator{
	public:
		CharComparator(){}
		int compare(char a, char b){
			if(a < b) return -1;
			if(a > b) return 1;
			return 0;
		}
};




struct SuffixArray{
	int n, lg;
	CharComparator charComparator;
	
	int **prefixSorted;
	int **posInKLevel;
	int **counter;
	int *posInKLevelK;
	int *counterK;
	vector<char> text;

	SuffixArray();
	SuffixArray(string &text, CharComparator charComparator);

	void internalSort(int* prefixSorted, int ini, int fin, int level);
	bool internalCompare(int level, int a, int b);

	int longestCommonPrefixSize(int l1, int r1, int l2, int r2);
	int compareSubstrings(int l1, int r1, int l2, int r2);
	void sortSubstrings(vector<pair<int,int>> &substrings, int first, int last);
	int countEqualSubstrings(int l, int r);
	int find(char *str);
	int longestPrefixSizeInText(char *str);	// todavia no existe
	int count(char* str);
};

SuffixArray::SuffixArray(){
	n = 0;
	lg = 0;
	posInKLevel = NULL;
	counter = NULL;
	text.clear();
}

SuffixArray::SuffixArray(string &text, CharComparator charComparator){
	this->charComparator = charComparator;
	n = text.size();
	if(n == 1) lg = 1;
	else lg = log2(n-1) + 2;

	// Limpiar y redimensionar los vectores 1D y 2D
	clearAndResizeArray2D(lg, n, prefixSorted);
	clearAndResizeArray2D(lg, n, posInKLevel);
	clearAndResizeArray2D(lg, n, counter);
	clearAndResizeVector1D(n, this->text);

	for(int i=0; i<n; i++) this->text[i] = text[i];

	// primer letra
	for(int j=0; j<n; j++)
	prefixSorted[0][j] = j;
	internalSort(prefixSorted[0], 0, n, 0);
	counter[0][0] = 1;
	posInKLevel[0][prefixSorted[0][0]] = 0;
	for(int j=1; j<n; j++){
		posInKLevel[0][prefixSorted[0][j]] = j;
		if(text[prefixSorted[0][j]] == text[prefixSorted[0][j-1]])
		counter[0][j] = counter[0][j-1];
		else
		counter[0][j] = counter[0][j-1] + 1;	
	}

	// Subcadenas de longitud 2^i, i>1
	for(int i=1; i<lg; i++){
		posInKLevelK = posInKLevel[i-1];
		counterK = counter[i-1];

		for(int j=0; j<n; j++)
		prefixSorted[i][j] = prefixSorted[i-1][j];

		internalSort(prefixSorted[i], 0, n, i);
		counter[i][0] = 1;
		posInKLevel[i][prefixSorted[i][0]] = 0;
		for(int j=1; j<n; j++){
			posInKLevel[i][prefixSorted[i][j]] = j;

			if(internalCompare(i, prefixSorted[i][j], prefixSorted[i][j-1]))       // la primer cadena es igual a la segunda (ya que solo podia ser mayor o igual)
			counter[i][j] = counter[i][j-1];
			else
			counter[i][j] = counter[i][j-1] + 1;
		}
	}
}

bool SuffixArray::internalCompare(int level, int a, int b){
	if(level == 0)
	return charComparator.compare(text[a], text[b]) <= 0;
	else{
		int pot = 1<<(level-1);

		// Se compara la primera mitad de las cadenas
		if(counterK[posInKLevelK[a]] != counterK[posInKLevelK[b]])
		return counterK[posInKLevelK[a]] < counterK[posInKLevelK[b]];

		// Se compara la segunda mitad de las cadenas
		// Primero se determina si ambas cadenas tienen almenos un caracter en la segunda mitad
		if(a+pot >= n && b+pot >= n) return true;    // Las cadenas son iguales
		if(a+pot >= n) return true;                               // La primer cadena es menor
		if(b+pot >= n) return false;                               // La segunda cadena es menor
		return counterK[posInKLevelK[a+pot]] <= counterK[posInKLevelK[b+pot]];
	}
}

void SuffixArray::internalSort(int *prefixSorted, int ini, int fin, int level){
	int *aux = (int*)malloc(sizeof(int) * n);
	for(int pot=1; pot<(fin-ini); pot*=2){
		for(int i=ini; i<fin; i+=2*pot){
			int l,r,l1,r1,l2,r2;
			l = i;	r = min(fin-1, i+2*pot-1);
			l1 = l; r1 = l+pot-1;
			l2 = l+pot; r2 = r;

			while(l <= r){
				if(l1 > r1) aux[l++] = prefixSorted[l2++];
				else if(l2 > r2) aux[l++] = prefixSorted[l1++];
				else if(internalCompare(level, prefixSorted[l1], prefixSorted[l2])) aux[l++] = prefixSorted[l1++];
				else aux[l++] = prefixSorted[l2++];
			}

			int lim = min(fin-1,i+2*pot-1);
			for(int j=i; j<=lim; j++)
			prefixSorted[j] = aux[j];
		}
	}
	free(aux);
}

int SuffixArray::longestCommonPrefixSize(int l1, int r1, int l2, int r2){
	int ans = 0;
	if(min(r1-l1, r2-l2) <= 16){
		for(int i=l1,j=l2; i<r1 && j<r2; i++,j++,ans++){
			if(charComparator.compare(text[i],text[j]) != 0)
			break;
		}
	}
	else{
		int level = log2(n);
		int pow2 = 1<<level;
		for(; l1<r1 && l2<r2;){
			while(pow2 > (r1-l1) || pow2 > (r2-l2)){
				pow2 >>= 1;
				level--;
			}

			int p1 = posInKLevel[level][l1];
			int p2 = posInKLevel[level][l2];
			if(counter[level][p1] == counter[level][p2]){
				ans += pow2;
				l1 += pow2;
				l2 += pow2;
			}
			else{
				r1 = l1 + pow2 - 1;
				r2 = l2 + pow2 - 1;
			}
		}
	}
	return ans;
}

int SuffixArray::compareSubstrings(int l1, int r1, int l2, int r2){
	int inc = longestCommonPrefixSize(l1,r1,l2,r2);
	l1 += inc;
	l2 += inc;

	if(l1 == r1 && l2 == r2) return 0;
	if(l1 == r1) return -1;
	if(l2 == r2) return 1;

	return charComparator.compare(text[l1], text[l2]);
}

void SuffixArray::sortSubstrings(vector<pair<int,int>> &substrings, int first, int last){
	vector<pair<int,int>> aux(last-first);
	for(int pow2=1; pow2 < (last-first); pow2*=2){
		for(int i=first; i<last; i+=2*pow2){
			int l, r, l1, r1, l2, r2;
			l = i; r = min(last-1, i+2*pow2-1);
			l1 = l; r1 = l+pow2-1;
			l2 = l+pow2; r2 = r;

			while(l <= r){
				if(l1 > r1) aux[l++ - first] = substrings[l2++];
				else if(l2 > r2) aux[l++ - first] = substrings[l1++];
				else if(compareSubstrings(substrings[l1].first, substrings[l1].second, substrings[l2].first, substrings[l2].second) <= 0) aux[l++ - first] = substrings[l1++];
				else aux[l++ - first] = substrings[l2++];
			}

			int lim = min(last-1, i+2*pow2-1);
			for(int j=i; j<=lim; j++)
			substrings[j] = aux[j - first];
		}
	}
}

int SuffixArray::countEqualSubstrings(int l, int r){
	// O(log^2(n))
	int p1, p2;

	// busqueda binaria sobre el prefixSorted[0] para hallar el primer sufijo que tiene
	// como prefijo a la cadena de entrada
	int first, last;
	first = 0;
	last = posInKLevel[lg-1][l];
	while(first < last){
		int middle = (first + last) / 2;
		
		int idStr = prefixSorted[lg-1][middle];
		int comp = compareSubstrings(idStr, min(n, idStr + r-l), l, r);
		if(comp < 0) first = middle + 1;
		else last = middle;
	}
	p1 = first;

	// busqueda binaria sobre  el prefixSorted para hallar el ultimo sufijo que tiene
	// como prefijo a la cadena de entrada
	first = posInKLevel[lg-1][l];
	last = n-1;
	while(first < last){
		int middle = (first + last + 1) / 2;
		
		int idStr = prefixSorted[lg-1][middle];
		int comp = compareSubstrings(idStr, min(n, idStr + r-l), l, r);
		if(comp <= 0) first = middle;
		else last = middle - 1;
	}
	p2 = first;

	return p2+1-p1;
}

int SuffixArray::find(char *str){
	int size = charArraySize(str);
	int auxLG = log2(size) + 1;

	// crear los vectores para los counter de la cadena de entrada
	vector<vector<int>> auxCounter(auxLG);
	auxCounter[0].clear(); auxCounter[0].resize(size);
	for(int i=1; i<auxLG; i++){
		auxCounter[i].clear();
		auxCounter[i].resize((auxCounter[i-1].size()) / 2);
	}

	// Se halla el vector counter correspondiente a la primer letra de cada sufijo
	// de la cadena de entrada
	for(int j=0; j<size; j++){
		int first = 0, last = n-1;
		auxCounter[0][j] = -1;
		while(first <= last && auxCounter[0][j] == -1){			
			int middle = (first + last) / 2;
			int idStr = prefixSorted[0][middle];
			int comp = charComparator.compare(text[idStr], str[j]);
			if(comp < 0) first = middle+1;
			else if(comp > 0) last = middle-1;
			else{
				last = middle;
				auxCounter[0][j] = counter[0][middle];
			}

			if(first == last && first == middle)
			break;
		}
	}

	// Se halla el vector counter para las subcadenas de la cadena de entrada
	// que inician en 2^i y tienen longitud 2^i
	for(int i=1,pow2=1; i<auxLG; i++, pow2*=2){
		for(int j=0; j < auxCounter[i].size(); j++){
			int first = 0, last = n-1;
			auxCounter[i][j] = -1;
			while(first <= last && auxCounter[i][j] == -1){
				int middle = (first + last) / 2;
				int idStr = prefixSorted[i][middle];
				int comp;
				if(counter[i-1][posInKLevel[i-1][idStr]] < auxCounter[i-1][2*j]) comp = -1;
				else if(counter[i-1][posInKLevel[i-1][idStr]] > auxCounter[i-1][2*j]) comp = 1;
				else{
					if((idStr + pow2 >= n) && (2*j+1 >= auxCounter[i-1].size())) comp = 0;
					else if(idStr + pow2 >= n) comp = -1;
					else if(2*j+1 >= auxCounter[i-1].size()) comp = 1;
					else{
						if(counter[i-1][posInKLevel[i-1][idStr + pow2]] < auxCounter[i-1][2*j+1]) comp = -1;
						else if(counter[i-1][posInKLevel[i-1][idStr + pow2]] > auxCounter[i-1][2*j+1]) comp = 1;
						else comp = 0;
					}
				}

				if(comp < 0) first = middle + 1;
				else if(comp > 0) last = middle - 1;
				else auxCounter[i][j] = counter[i][middle];

				if(first == last && first == middle)
				break;
			}
		}
	}

	
	// Se determina si es imposible que exita una subcadena igual en el texto
	for(int i=auxLG-1,j=0; i>=0; i--,j=(j+1)*2){
		if(auxCounter[i][j] == -1)
		return -1;
	}

	// busqueda binaria para determinar la primer cadena
	int first = 0, last = n-1, ans = -1;
	while(first <= last){
		int middle = (first + last) / 2;
		int idStr = prefixSorted[auxLG-1][middle];
		int comp = 0;

		for(int i=auxLG-1, j=0, inc=0; i>=0 && j<auxCounter[i].size() && comp == 0; i--,j=(j+1)*2){
			if(counter[i][posInKLevel[i][idStr + inc]] < auxCounter[i][j]) comp = -1;
			else if(counter[i][posInKLevel[i][idStr + inc]] > auxCounter[i][j]) comp = 1;
			inc += 1<<i;
		}

		if(comp < 0) first = middle + 1;
		else if(comp > 0) last = middle - 1;
		else{
			last = middle;
			ans = idStr;
		}

		if(first == last && first == middle)
		break;
	}

	// clear
	for(int i=0; i<auxCounter.size(); i++)
	auxCounter[i].clear();
	auxCounter.clear();

	return ans;
}

int SuffixArray::count(char *str){
	int size = charArraySize(str);
	int first = find(str);
	int last = first + size;
	if(first == -1) return 0;
	else return countEqualSubstrings(first, last);
}