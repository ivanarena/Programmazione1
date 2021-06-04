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

nodoE *conc(nodoE *a, nodoE *b)
{
    if (!a)
        return b;
    a->next = conc(a->next, b);
    return a;
}

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

// PRE=(albero(T) ben formato, P contiene dimP>=0 elementi)
nodoE *PM(nodo *T, int *&P, int &dimP) 
{
    if (!dimP || !T) { // pattern finito
        return 0;
    } else {
        nodoE *a = 0;
        if (T->info == *P) { // pattern trovato
            P++;
            dimP--;
            a = new nodoE(T);
        }
        // PRE_RIC = (0<=dimP<=vdimP, a = P[0] sse T->info == P[0])
        a = conc(a, PM(T->left, P, dimP)); // concatena list(a) a sé stessa ricorsivamente
        a = conc(a, PM(T->right, P, dimP)); // in ordine prefisso
        // POST_RIC = (lista(a) contiene vdimP-dimP nodi matchati)
        return a;
    }

}
// POST=(se n0, n1, …,n(k-1), con k<=dimP, sono i nodi di T che matchano il massimo possibile di P percorrendo T in ordine prefisso, allora PM restituisce una lista di k nodoE che puntano a n0,..,n(k-1)).

int main()
{
    int dim, dimP;
    cin >> dim >> dimP;
    nodo *r = 0;
    int *A = new int[dim];
    for (int i = 0; i < dim; i++)
        cin >> A[i];
    r = buildTree(A, 0, dim);
    stampa_l(r);
    cout << endl;

    int *P = new int[dimP];
    for (int i = 0; i < dimP; i++)
        cin >> P[i];

    nodoE *z = PM(r, P, dimP);
    stampaE(z);
}

/* DIMOSTRAZIONE DI CORRETTEZZA PM

CASO BASE: albero(T) vuoto, restituisce 0 che è uguale al numero di nodi matchati => vale POST.
PASSO INDUTTIVO: Vale PRE, se sottoalbero(T) non vuoto e pattern non matchato interamente, 0<=dimP<=vdimP e a = P[0] sse
                 il primo elemento di P è stato matchato, vale PRE_RIC; assumiamo vera POST_RIC, allora alla fine viene
                 restituita la lista(a), contenente i nodi matchati => vale POST.

*/