#include<iostream>
using namespace std;

struct nodo{int info; nodo* next; nodo(int a=0, nodo*b=0){info=a; next=b;}};

nodo* faiL(int n) {
    if(n) {
        int x;
        cin >> x;
        return new nodo(x,faiL(n-1));
    }
    return 0;
}

void stampa(nodo*L) {
    if(L) {
        cout << L->info<<' ';
        stampa(L->next);
    }

    else
        cout<<endl;
}

nodo* clone(nodo*L) {
    if(L)
        return new nodo(L->info,clone(L->next));
    return 0;
}

// PRE = (Lista(L) ben formata e ordinata, x punta ad un nodo)
nodo* insOrd_ric(nodo* L, nodo* x) {
    if (!L) { // empty list
        x->next = 0;
        return x;
    } else {
        if (L->info >= x->info) {
            x->next = L;
            L = x;
            return x; // or: return L;
        } else {
            // PRE_RIC = (Lista(L) contiene almeno un nodo con campo info minore di quello di x)
            L->next = insOrd_ric(L->next, x); // L points to L->next until it finds x position
            // POST_RIC = (Lista(L) contiene almeno un nodo che punta o ad un altro nodo di vL(L) o al nodo x)
            return L; // returns list
        }
    }
}
// POST = (restituisce vL(L) con x aggiunto in modo che la nuova lista sia ancora ordinata)

// PRE = (Lista(L) ben formata e ordinata, x punta ad un nodo)
nodo* insOrd_iter(nodo* L, nodo*x) {
    bool ok = false; // boolean check
    
    if (!L) { // empty list
        x->next = 0;
        L = x; 
        ok = true;
    } else if (!L->next) { // only node
        if (L->info >= x->info) {
            x->next = L;
            L = x;
            ok = true;
        } else {
            x->next = 0;
            L->next = x;
            ok = true;
        }
    } else if (L->info >= x->info) { // x should be first node
        x->next = L;
        L = x;
        ok = true;
    }

    nodo* T = L; // stores full list
    while (L->next && !ok) { // R = (L(L) non vuota e ok vero sse x è stato inserito)
        if (L->next->info >= x->info) {
            x->next = L->next;
            L->next = x;
            ok = true; // exit loop
        } else if (!L->next->next && L->next->info <= x->info) { // x should be last node
            x->next = 0;
            L->next->next = x;
            ok = true; // exit loop
        } else {
            L = L->next; // go to the next node
        }
        
    }

    return T; // returns full lists
}
// POST = (restituisce vL(L) con x aggiunto in modo che la nuova lista sia ancora ordinata)

int main() {
    int m, x;
    cin >> m >> x;
    nodo*L=faiL(m);
    nodo*L1=clone(L);
    
    L=insOrd_ric(L,new nodo(x));
    L1=insOrd_iter(L1, new nodo(x));
    stampa(L);
    stampa(L1);
}

/*

DIMOSTRAZIONE DI CORRETTEZZA insOrd_ric:

CASO BASE: Lista vuota, viene aggiunto x e, visto che è l'unico elemento, la nuova lista è ordinata => vale POST.
PASSO INDUTTIVO: Vale PRE, per raggiungere la prima chiamata ricorsiva occorre che la lista non sia vuota, quindi avrà almeno un nodo
                 e con campo info minore di quello di x (altrimenti x sarebbe già stato inserito prima di questo), quindi vale PRE_RIC;
                 assumiamo che valga anche POST_RIC, quindi la lista contiene almeno un nodo che punta o ad un altro nodo e allora verrà
                 chiamata di nuovo la funzione, o ad x, il quale punterà a sua volta al resto della lista; si avrà, dunque, una nuova lista
                 ordinata contenente anche il nodo x => vale POST. 

*/
/*

DIMOSTRAZIONE DI CORRETTEZZA insOrd_iter:

1) Vale PRE, L ben formata ed ordinata e ok = false sse x non è stato inserito, ovvero se L ha più di un nodo => vale R.
2) Assumiamo che valga R per un'esecuzione del ciclo, allora L è non vuota: sse ok vero, il loop termina e si ha la POST, altrimenti,
   ci sono due possibilità:
    - L contiene solo due nodi: si analizza l'ultimo e x viene inserito prima se il suo campo info è minore di quello dell'ultimo nodo o dopo se maggiore;
    - L contiene più di due nodi: si analizza il successivo e x viene inserito prima se il suo campo info è minore di tale nodo, altrimenti si va avanti fin
      quando questa cosa non sarà vera o fin quando ci saranno solo due nodi (vedi sopra);
   In entrambi i casi vale POST.
3) Vale R e ok = true (x è stato inserito) e viene restituita l'intera lista ordinata con l'aggiunta del nodo x => vale POST.

*/
