#include<iostream>
using namespace std;

// PRE = length è un intero valido per T e P
void leggi(int* A, int length) {
    for (int i = 0; i < length; i++) {
        cin >> A[i];
    }
}
// POST = Riempie un array A di length elementi

// PRE = (T ha LT elementi e P ne ha LP, LT e LP sono > 0)
int match(int* T, int LT, int* P, int LP) {
    int count=0, index;
    for (int i=0; i<LT; i++) { // R1 = (0<=i<=LT) e index è l'indice del primo elemento del sotto-array di T uguale a P sse esiste, altrimenti è -1
        if (T[i] == P[0]) { // controlla il primo elemento di P
            for (int j=i; j<i+LP; j++) { // R2 = (i<=j<=i+LP) && (count conta gli elementi consecutivi di T uguali ai rispettivi di P) 
                if (T[j] == P[j-i]) { // controlla i successivi elementi di T
                    count++;
                }
                if (count == LP) {
                    index = i; // stores index
                    return index;
                }
            }
            // POST = restituisce l'indice dove comincia il sotto-array di T uguale a P sse lo trova
            count = 0; // resets counter
        }
    }
    index = -1; // match not found
    return index;
}
// POST = (se c'è un match di P in T allora la funzione restituisce 
// l'indice minimo di tale indice, altrimenti restituisce -1)

int main() {
    int T[50], P[10], LT, LP;
    cin >> LT >> LP;
    leggi(T,LT);
    leggi(P,LP);
    cout << "inizio match=" << match(T,LT,P,LP) << endl;  
    return 0;
}   

/* DIMOSTRAZIONE DI CORRETTEZZA

(1.1) j=i, count conta i T uguali ai rispetti p -> count = 0;
(1.2) j=i, count conta i T uguali ai rispetti p -> count = 0, i++, se trova un P in T allora count++;
(1.3) j<=i+LP, count trova tre T consecutivamente uguali ai rispettivi P -> count = LP, restituisce indice

(2.1) PRE && i=0 -> vale R
(2.2) i=0 vale R -> i<=LT vale R 
(2.3) i=LT && R -> vale POST

*/