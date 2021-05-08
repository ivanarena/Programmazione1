#include<iostream>
using namespace std;

struct nodo {
    int info;
    nodo* next;
    nodo(int a=0, nodo* b=NULL) {
        info=a;
        next=b;
    }
};

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

nodo* build1(int m) {
   if(m==0) return 0;
   int s;
   cin >> s;
   return new nodo(s,build1(m-1));
}

// PRE_1 = (Lista(L) ben formata, vLista(L)=Lista(L))
nodo* del1(nodo* L, int z) {
    if (!L) {
        return 0;
    }
    if (L->info == z) { // rimuove z
        nodo* X = del1(L->next, z);
        delete L;
        return X;
    } else {
        L->next = del1(L->next, z);
        return L;
    }
}
// POST_1 = (restituisce una lista composta dai nodi di vLista(L) che non hanno campo info=z nell’ordine che hanno in vLista(L)) && (dealloca gli altri nodi di vLista(L))

// PRE_2=(LIsta(L) ben formata, non vuota, e L->info != z, sia vLista(L)=Lista(L))
void del2(nodo*L, int z) {
    if (L->next) {
        if (L->next->info == z) {
            nodo* X = L->next;
            L->next = X->next;
            delete X;
            del2(L, z);
        } else {
            del2(L->next, z);
        }
    }   
    
}
// POST_2=(Lista(L) è ottenuta da vLista(L) eliminando i nodi con info=z e tenendo gli altri mantenendo il loro ordine) &&(i nodi con info=z sono deallocati)

// PRE_3=(Lista(L) ben formata, vLista(L)=Lista(L))
void del3(nodo*&L, int z) {
    if (L) {
        if (L->info == z) {
            nodo* X = L;
            L = L->next;
            delete X; 
            del3(L, z);
        } else {
            del3(L->next, z);
        }
    }
}
// POST_3=(Lista(L) è ottenuto da vLista(L) eliminando i nodi con info=z e mantenendo gli altri nello stesso ordine che avevano in vLista(L) && (i nodi eliminati sono deallocati)

int main() {
    int m,z;
    cin >> m;
    
    nodo*Y = build1(m);
    stampa_LR_iter(Y);
    
    cin >> z;
    Y=del1(Y,z);
    stampa_LR_iter(Y);
    
    cin >> z;
    del2(Y,z);
    stampa_LR_iter(Y);
    
    cin >> z;
    del3(Y,z);
    stampa_LR_iter(Y);
}

/* 

CORRETTEZZA DEL1:
- CASO BASE: L vuota => restituisce 0, vale POST
- HP INDUTT.: 

CORRETTEZZA DEL2:
- CASO BASE: L contiene un solo nodo con info diverso da z => vL=L (non ci sono nodi con info = n), vale POST
- HP INDUTT.:

CORRETTEZZA DEL3:
- CASO BASE: L vuota => vL = L e nessun nodo, vale POST
- HP INDUTT.:

15
1 2 3 1 2 5 6 3 1 2 1 2 1 0 0
1
0
5

*/