#include <iostream>
using namespace std;

struct nodo
{
    int info;
    nodo *left;
    nodo *right;

    nodo(int x = 0, nodo *l = 0, nodo *r = 0)
    {
        info = x;
        left = l;
        right = r;
    }
};

// FUNZIONI AUSILIARIE FORNITE
nodo *buildTree(int arr[], int i, int n)
{

    if (i >= n)
    {
        return NULL;
    }
    nodo *root = new nodo(arr[i]);
    // insert left child
    root->left = buildTree(arr, 2 * i + 1, n);
    // insert right child
    root->right = buildTree(arr, 2 * i + 2, n);

    return root;
}

int height(nodo *root)
{
    if (!root)
    {
        return -1;
    }
    return 1 + max(height(root->left), height(root->right));
}

void stampa_l(nodo *r)
{
    if (r)
    {
        cout << r->info << '(';
        stampa_l(r->left);
        cout << ',';
        stampa_l(r->right);
        cout << ')';
    }
    else
        cout << '_';
}

void sc(int *C)
{
    cout << *C << ' ';
    if (*C != -1)
        sc(C + 1);
}

struct nodoE
{
    nodo *info;
    nodoE *next;
    nodoE(nodo *a = 0, nodoE *b = 0)
    {
        info = a;
        next = b;
    }
};

void stampaE(nodoE *x)
{
    if (x)
    {
        cout << x->info->info << ' ';
        stampaE(x->next);
    }
    else
        cout << endl;
}

// PRE = (alb(T) ben formato, dimP>=0)
bool checkMatch(nodo *T, int *P, int dimP) {
    if (!dimP) { // match found
        return true;
    }
    if (!T) { // path is over
        return false;
    } else {
        if (T->info == *P) {
            if (checkMatch(T->left, P+1, dimP-1)) {
                return true;
            } else if (checkMatch(T->right, P+1, dimP-1)) {
                return true;
            }
        } else {
            return false;
        }
    }
       
}   
// POST = (restituisce true sse trova un cammino contiguo, false altrimenti)

// PRE = (T è il sottoalbero contenente il match, dimP > 0)
nodoE *buildE(nodo *T, int *P, int dimP) {
    if (!dimP) { // match finito 
        return 0;
    }
    if (T->info == *P) {
        nodoE *L = new nodoE(T);
        if (checkMatch(T->left, P+1, dimP-1)) {
            L->next = buildE(T->left, P+1, dimP-1);
        } else {
            L->next = buildE(T->right, P+1, dimP-1);
        }
        return L;
    }
}
// POST = (restituisce lista(L) formata dai nodi matchati da T in poi)

// PRE = (albero(T) ben formato, P contiene dimP>=0 elementi)
nodoE *PM1(nodo *T, int *P, int dimP) {
    if (!T) {
        return 0;
    } else {
        if (checkMatch(T, P, dimP)) {
            return buildE(T, P, dimP);
        } else {
            // PRE_RIC = (alb(T) ben formato)
            nodoE *a = PM1(T->left, P, dimP);
            // POST_RIC = (sse il match è stato trovato restituisce una lista contenente i nodi matchati, altrimenti restituisce 0)
            if (a) {
                return a;
            }
            // PRE_RIC = (alb(T) ben formato)
            nodoE *b = PM1(T->right, P, dimP);
            // POST_RIC = (sse il match è stato trovato restituisce una lista contenente i nodi matchati, altrimenti restituisce 0)
            return b;
        }
    }
}
/* POST = (se in T esiste un cammino che contiene un match di P completo e contiguo, allora PM1 restituisce
una lista di dimP nodi di tipo nodoE che puntano ai nodi del cammino più a sinistra su cui esiste un tale
match di P, altrimenti PM1 restituisce 0 ).*/

int main()
{
    int dim, dimP;
    cin >> dim >> dimP;
    nodo *r = 0;
    int *A = new int[dim];
    for (int i = 0; i < dim; i++)
    {
        cin >> A[i];
        r = buildTree(A, 0, dim);
    }
    stampa_l(r);
    cout << endl;
    int *P = new int[dimP];
    for (int i = 0; i < dimP; i++)
        cin >> P[i];
    nodoE *z = PM1(r, P, dimP);
    if (z)
    {
        cout << "trovato match: ";
        stampaE(z);
    }
    else
        cout << "nessun match" << endl;
}

/* DIMOSTRAZIONE DI CORRETTEZZA PM1

CASO BASE: albero(T) vuoto, match non trovato, restituisce 0 => vale POST.
PASSO INDUTTIVO: Vale PRE, in particolare, se albero(T) non vuoto e match non trovato sulla radice si effettua la chiamata
                 ricorsiva con T sottoalbero ben formato, quindi vale PRE_RIC; supponiamo vera POST_RIC, allora sse il match
                 è stato trovato, altrimenti viene resituito 0, viene restituita una lista contenente i nodi di T matchati => vale POST.

*/