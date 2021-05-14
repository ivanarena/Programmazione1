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

void stampa_LR_iter(nodo* L) {       
    int k=length(L);
  
	for(int i=0; i<k; i++) {
        cout<<L->info<<' ';
        L=L->next;
    }
	cout<<endl;
}

nodo* build1(int m) {
    if(m==0) return 0;
    int s;
    cin >>s;
    return new nodo(s,build1(m-1));
}

struct doppiaL {
    nodo *L,*S;
    doppiaL(nodo*a=0,nodo*b=0) {
        L=a;
        S=b;
    }
};

bool doubleCheck1(nodo* T, nodo* P) {
    if (!P) {
        return true;
    } else {
        if (T->info == P->info) {
            doubleCheck1(T->next, P->next);
        } else {
            return false;
        }
    }
}

doppiaL* checkMatch1(nodo* T, nodo* P) {
    if (!P) {
        return new doppiaL(T, P);
    } else {
        return checkMatch1(T->next, P->next);
    }
}

// PRE = (T e P sono liste ben definite)
doppiaL match1(nodo* T, nodo*P) {
    if (!T) {
        return doppiaL(T, 0); // match not found, t as original, p empty
    } else {
        if (doubleCheck1(T, P)) { // if pattern is matched
            return *checkMatch1(T, P); // returns unmatched nodes after pattern
        } else {
            doppiaL q; 
            q.L = T; // stores unmatched nodes before pattern

            // PRE_RIC = (q.L contiente tutti gli elementi non matchati fino all'inizio del pattern)
            q.L->next = match1(T->next, P).L; // joins unmatched b4 and after
            // POST_RIC = (q.L contiene tutti gli elementi non matchati)

            q.S = P; // stores pattern
            return q;
        }
    }
}
// POST = (se in T c’è un match P’ di P, la funzione restituisce un valore doppiaL q, con q.S=P’ e q.L=quello che resta di T una volta tolto P’, si considera il match P’ che inizia più a sinistra in T) && (se in T non c’è match di P, allora la funzione restituisce un valore doppiaL q con q.L=T e q.s=0)

nodo* clone(nodo*L) {
	if(!L) return 0;
	return new nodo(L->info,clone(L->next));
}

bool doubleCheck3(nodo* T, nodo* P) {
    if (!P) {
        return true;
    } else {
        if (T->info == P->info) {
            doubleCheck3(T->next, P->next);
        } else {
            return false;
        }
    }
}

nodo* checkMatch3(nodo* & T, nodo* P) {
    if (!P) {
        return P;
    } else {
        if (doubleCheck3(T, P)) {
            checkMatch3(T->next, P->next);
            nodo* Q = T;
            T = T->next;
            return Q;
        } else {
            return 0;
        }
    }
}

// PRE = (T e P sono ben formate)
nodo* match3(nodo*&T, nodo*P) {
    if (!T) {
        return 0;
    } else {
        if (checkMatch3(T, P)) {
            return P;
        } else {
            // PRE_RIC = (match non ancora trovato)
            match3(T->next, P);
            // POST_RIC = (match trovato)
        }
    }
}
// POST = (se c’è match restituisce il primo match P’ col return e quello che resta di T nel parametro T) && (se non c’è match T resta invariata e ritorna 0 col return)

int main() {
    int m,z;
    cin >> m >> z;

    nodo* L = build1(m);
    stampa_LR_iter(L);
    nodo* P = build1(z);
    stampa_LR_iter(P);
    
    nodo* L1 = clone(L);
    nodo* P1 = clone(P);
    
    doppiaL D = match1(L,P);  
    stampa_LR_iter(D.L);
    stampa_LR_iter(D.S);
    
    nodo* q = match3(L1,P1);  
    stampa_LR_iter(L1);
    stampa_LR_iter(q);
}

/*

DIMOSTRAZIONE DI CORRETTEZZA MATCH1

CASO BASE: T vuota, quindi q.S vuoto (nessun pattern matchato) e q.L contiene T originale => vale POST.
PASSO INDUTTIVO: vale PRE, else preso, if non preso quindi pattern non ancora trovato, allora q.L contiene
                nodi di T prima dell'inizio del match; vale POST_RIC, q.S contiene il pattern, q.L contiene 
                gli elementi di T al di fuori del pattern, vale POST.


DIMOSTRAZIONE DI CORRETTEZZA MATCH3

CASO BASE: T vuota, T resta invariata e restituisce 0, vale POST.
PASSO INDUTTIVO: vale PRE, match non ancora trovato, quando lo trova restituisce P col return e ha modificato T => vale POST.

*/