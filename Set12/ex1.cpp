#include <iostream>
using namespace std;

struct nodo
{
    int info;
    nodo *next;
    nodo(int a = 0, nodo *b = 0)
    {
        info = a;
        next = b;
    }
};

nodo *faiL(int arr[], int dim)
{
    if (dim)
    {
        return new nodo(*arr, faiL(arr + 1, dim - 1));
    }
    else
        return 0;
}

nodo *clone(nodo *L)
{
    if (!L)
        return 0;
    return new nodo(L->info, clone(L->next));
}

void stampaL(nodo *L)
{
    if (!L)
        cout << endl;
    else
    {
        cout << L->info << ' ';
        stampaL(L->next);
    }
}

// PRE=(L(L) ben formata, k>=y, vL=L)
nodo* elimI(nodo*L, int &n, int k, int y) {
    if (!L || (n == k)) { // L vuota o trovati k nodi con info=y
        return L;
    } else {
        if (L->info == y) {
            n++;
            // PRE_RIC = (L(L) ben formata, 0<=n<=k)
            L->next = elimI(L->next, n, k, y); 
            // POST_RIC = (sse ci sono k nodi con campo info=y ogni nodo di L punta al primo nodo successivo con campo info != y)
            if (n == k) { 
                nodo *D = L;
                L = L->next;
                delete D;
            }
            return L;
        } else {
            // PRE_RIC = (L(L) ben formata, 0<=n<=k)
            L->next = elimI(L->next, n, k, y);
            // POST_RIC = (sse ci sono k nodi con campo info=y ogni nodo di L punta al primo nodo successivo con campo info != y)
            return L;
        }
    }
}
// POST=(se vL contiene almeno k nodi con info=y, allora L è ottenuta da vL eliminando i primi k nodi con info=y di vL, altrimenti, L=vL) &&( se nodi di vL vengono cancellati, essi vanno deallocati)

// PRE=(L(L) ben formata, k>=y, vL=L)
nodo* elimF(nodo*L, int &n, int k, int y) {
    if (!L) {
        if (n >= k) { // controlla se ci sono almeno k nodi con campo info = y
            n = 0; // azzera n per contare k nodi con campo info = y dalla fine
        } else {
            n = k; // rende n maggiore di k per evitare la condizione di eliminazione
        }
        return L;
    } else {
        if (L->info == y) {
            n++;
            // PRE_RIC = (L(L) ben formata)
            L->next = elimF(L->next, n, k, y);
            // POST_RIC = (se L(L) contiene k o più nodi con campo info = y allora n-k nodi a partire dall'ultimo saranno eliminati, altrimenti vL=L)
            if (n < k) {
                n++;
                nodo *D = L;
                L = L->next;
                delete D;
            }
            return L;
        } else {
            // PRE_RIC = (L(L) ben formata)
            L->next = elimF(L->next, n, k, y);
            // POST_RIC = (se L(L) contiene k o più nodi con campo info = y allora n-k nodi a partire dall'ultimo saranno eliminati, altrimenti vL=L)
            return L;
        }
    }
}
// POST=(se vL contiene almeno k nodi con info=y, allora L è ottenuta da vL eliminando gli ultimi k nodi con info=y di vL, altrimenti, L=vL) && (se nodi di vL vengono cancellati, essi vanno deallocati)

int main()
{
    int dim;
    cin >> dim;
    int *arr = new int[dim];
    for (int i = 0; i < dim; i++)
        cin >> arr[i];
    nodo *L = faiL(arr, dim);
    nodo *L1 = clone(L);

    int n = 0, k, y;
    cin >> k >> y;
    L = elimI(L, n, k, y);
    n = 0;
    L1 = elimF(L1, n, k, y);
    stampaL(L);
    stampaL(L1);
}

/* DIMOSTRAZIONE DI CORRETTEZZA elimI 

CASO BASE: lista vuota, viene restituita L, cioè 0, nessun nodo viene rimosso => vale POST.
PASSO INDUTTIVO: Vale PRE, se L non vuota allora si entra nell'else e vale PRE_RIC; supponiamo vera POST_RIC, allora ogni nodo di L
                 punta al primo nodo successivo con campo info != y sse ci sono almeno k nodi con campo info=y (altrimenti L=vL), quindi
                 saranno eliminati tutti i nodi con tale proprietà => vale POST.

*/

/* DIMOSTRAZIONE DI CORRETTEZZA elimF 

CASO BASE: lista vuota, viene restituita L, cioè 0, nessun nodo viene rimosso => vale POST.
PASSO INDUTTIVO: Vale PRE, se L non vuota allora si entra nell'else e vale PRE_RIC; supponiamo vera POST_RIC, allora sse ci sono almeno
                 k nodi con campo info=y, verranno eliminati n-k nodi a partire dall'ultimo andando a ritroso, altrimenti viene restituita
                 L=vL => vale POST.

*/