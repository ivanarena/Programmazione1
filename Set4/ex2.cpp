#include<iostream>
using namespace std;

void leggi(int*X, int nelem) {
    for(int i=0; i < nelem; i++)
    cin >> X[i];
}

// PRE=(T ha s strati ed è completamente definite, F e indf specificano 
// una fetta esistente in T, k >=0 è un elemento esistente della fetta richiesta)
int& FETTE(int (*T)[6][5], int s, char F, int indf, int k) {
    if (F == 'H') {
        return T[k/s-1][indf][k%5]; // 0<=k/s-1<=2; indf corrisponde all'indice della riga; 0<=k%5<=4;
    } else { // if V
        return T[k/6][k%6][indf]; // 0<=k/6<=2 per ogni 0<=k<18; 0<=k%6<=5; indf corrisponde all'indice dell'elemento;
    }
}
// POST=(restituisce l’elemento k-esimo della fetta di T specificata da F e indf)

int main() {
    int A[3][6][5], nelem;
    leggi(**A,90);
    bool stop=false;
    while(!stop) {
        char c;
        cin >> c;
        if(c =='S')
    	    stop=true;
        else {
    	    int f,k;
    	    cin>>f>>k;
    	    cout << FETTE(A,3,c,f,k) << endl;
    	}
    }

}
