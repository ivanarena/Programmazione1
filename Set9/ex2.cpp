#include<iostream>
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

nodo* build1(int m) {
  if(m==0) return 0;
  int s;
  cin >>s;
  return new nodo(s,build1(m-1));
}
 
struct doppiaL{nodo*L,*S; doppiaL(nodo*a=0,nodo*b=0){L=a; S=b;}};

bool check(nodo* & T, nodo* P) {
  if (!P) {
    return true;
  } else {
    if (T->info == P->info) {
      check(T->next, P->next);
    } else {
      return false;
    }
  }
}

nodo* found(nodo* & T, nodo* P) {
  if (!P) {
    nodo* R = T;
    T = 0;
    return R;
  } else {
    found(T->next, P->next);
  }
}

// PRE = (L(T) e L(P) ben formate)
nodo* match3b(nodo* & T, nodo* P) {
  if (!T) { // match not found
    return T;
  } else {
    if (check(T, P)) { // match found
      return found(T, P);
    } else {
      nodo* q = new nodo(T->info); // stores every unmatched T node before pattern
      T = T->next; // T becomes T minus the first node (every time), it will eventually become equal to pattern

      // PRE_RIC = (L(T) = vL(T)-primo nodo, L(q) = primo nodo di L(T))
      q->next = match3b(T, P); // q points unmatched T nodes after pattern 
      // POST_RIC = (L(T) = L(P), L(q) = L(T)-L(P) sse pattern trovato)

      return q; // returns unmatched nodes
    }
  }
}
// POST = ((restituisce L(q) = vL(T)-L(P)) && (L(T) = L(P)) sse il pattern è stato trovato, altrimenti L(T) = vL(T) e restituisce vL(T))

int main() {
  int m,z;
  cin >> m >> z;
  nodo*L=build1(m);
  stampa_LR_iter(L);
  nodo*P=build1(z);
  stampa_LR_iter(P);

  nodo* q = match3b(L,P);  
  stampa_LR_iter(q);
  stampa_LR_iter(L);
}

/*

DIMOSTRAZIONE DI CORRETTEZZA

CASO BASE: Lista vuota, match non trovato => restituisce T = 0. VERO
IPOTESI INDUTTIVA: - Vale PRE, T=T->next quindi L(T) = vL(T) senza il primo nodo, che va in L(q), vale PRE_RIC
                   - Vale POST_RIC, (1) pattern non trovato restituisce T, vale POST, (2) pattern trovato
                     L(T) = L(P), L(q) = L(T) senza pattern, allora vale POST.

*/