#include <iostream>
using namespace std;

struct nodo{int info; nodo* next; nodo(int a=0, nodo* b=NULL){info=a; next=b;}};

int length(nodo*L) {
    if(L) return 1 + length(L->next);
    return 0;
}

void stampa_LR_iter(nodo*L) {   
    int k=length(L);
  
	for(int i=0; i<k; i++)
	    {cout<<L->info<<' '; L=L->next;}
	cout<<endl;
}

nodo* build1(int m)
{
   if(m==0) return 0;
   int s;
   cin >>s;
   return new nodo(s,build1(m-1));
}

struct doppiaL{nodo*L,*S; doppiaL(nodo*a=0,nodo*b=0){L=a; S=b;}};

bool found(nodo* T, nodo* P) { // consecutiveness not mandatory
    if (!P)
        return 1; // match found
    if (!T)
        return 0; // match not found
    if (T->info == P->info) 
        found(T->next, P->next); // match next element
    else
        found(T->next, P); // move to search match
}

// PRE = (T e P ben formate e pattern presente)
nodo* buildL(nodo* T, nodo* P) { // builds 
    if (!T) {
        return 0; // T ends along with P
    }
    if (!P) {
        return T; // P ends, every other element after pattern is unmatched, so returned
    } else {
        if (T->info != P->info) {
            nodo* u = new nodo(T->info); // creates new list of unmatched

            // PRE_RIC = (T = T - primoelem(T) ogni volta)
            u->next = buildL(T->next, P); // joins unmatched elements
            // POST_RIC = (u contiene T non matchata)

            return u;
        } else {
            buildL(T->next, P->next); // pattern found, now it will look for next pattern element
        }
    }
}
// POST = (restituisce u = T-P-primoelem(T))

// PRE = (Lista(P) e Lista(T) sono ben formate, vT=T)
doppiaL matchX1(nodo*T, nodo*P) {
    if (!found(T, P)) {
        return doppiaL(T,0);
    } else {
        if (T->info != P->info) {
            doppiaL D;
            D.L = T; // fills with first buildL element once
            D.S = P; // fills with pattern
            D.L->next = buildL(T->next, P); // fills with every other buildL element
            return D;
        }
    }
}
// POST = (La funzione restituisce sempre un valore doppiaL D come segue: se vT contiene m0,..,mk allora D.S=m0,..,mk e D.L contiene vT senza i nodi m0…mk, mentre se vT non contiene m0,..mk allora la funzione restituisce D.S=0 e D.L=vT)


int main() {
    int m,z;
    cin >> m>>z;
    nodo*L=build1(m);
    stampa_LR_iter(L);
    nodo*P=build1(z);
    stampa_LR_iter(P);
    
    doppiaL D= matchX1(L,P);  
    stampa_LR_iter(D.L);
    stampa_LR_iter(D.S);
  
}

/* 

DIMOSTRAZIONE DI CORRETTEZZA BUILDL:

CASO BASE: Lista T vuota, pattern non trovato e T resta come originale => vale POST.
PASSO INDUTTIVO: Vale PRE, T manca del primo nodo ogni volta, quindi vale PRE_RIC, vale POST_RIC, quindi viene restituito 
                u contenente T non matchata, u quindi è uguale a tutti gli elementi di T tranne il primo e quelli uguali al
                pattern in ordine, quindi vale POST.

*/