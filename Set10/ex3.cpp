#include<iostream>
using namespace std;

struct nodo{
	int info;
	nodo* left;
	nodo* right;

	nodo(int x=0, nodo* l=0, nodo* r=0){
		info = x;
		left = l;
		right = r;
	}
};

// FUNZIONI AUSILIARIE FORNITE
nodo* buildTree(int arr[], int i, int n)  {

    if (i >= n) {
    	return NULL;
    }
    nodo* root = new nodo(arr[i]);
    // insert left child
    root->left = buildTree(arr, 2 * i + 1, n);
    // insert right child
    root->right = buildTree(arr, 2 * i + 2, n);

    return root;

}


void stampa_l(nodo *r) {
  if(r)
    {
      cout<<r->info<<'(';
      stampa_l(r->left);
      cout<<',';
      stampa_l(r->right);
      cout<<')';
    }
  else
    cout<< '_';
}

void sc(int*C) {
    cout<<*C<<' ';    
    if(*C!=-1)
    sc(C+1);
}

// PRE = (albero(r) ben formato,0<=n<=k, k>0)
int stampaASPre(nodo*r, int n, int k) {
    if (!r) {
        return n;
    } else {
        if (n == 0) {
            cout << r->info << " ";
            n = k;
        }
        n--;
        // PRE_RIC1 = (albero(r->left) ben formato, 0<=n<=k && k>0)
        n = stampaASPre(r->left, n, k);
        // POST_RIC1 = (n = numero di nodi da saltare && 0<=n<k && k>0)

        // PRE_RIC2 = (albero(r->right) ben formato, 0<=n<=k && k>0)
        return stampaASPre(r->right, n, k);
        // POST_RIC2 = (n = numero di nodi da saltare && 0<=n<k && k>0)
    }
}
/* POST=(considerando I nodi di albero(r) in ordine prefisso, salta n nodi e poi stampa quello successivo e
dopo ne salta k-1 e poi stampa il successivo, restituisce col return un intero m tale che (k-1)-m è il numero
di nodi che sono stati saltati dopo l’ultimo stampato). */

// PRE = (albero(r) ben formato,0<= n<=k, k>0)
int stampaASInf(nodo*r, int n, int k) {
    if (!r) {
        return n;
    } else {
        // PRE_RIC1 = (albero(r->left) ben formato, 0<=n<=k && k>0)
        n = stampaASInf(r->left, n, k);
        // POST_RIC1 = (n = numero di nodi da saltare && 0<=n<k && k>0)
        if (n == 0) {
            cout << r->info << " ";
            n = k;
        }
        n--;
        // PRE_RIC2 = (albero(r->right) ben formato, 0<=n<=k && k>0)
        return stampaASInf(r->right, n, k);
        // POST_RIC2 = (n = numero di nodi da saltare && 0<=n<k && k>0)
    }
}
/* POST = (considerando I nodi di albero(r) in ordine infisso, salta n nodi e poi stampa quello successivo e
dopo ne salta k-1 e poi stampa il successivo, restituisce col return un intero m tale che (k-1)-m è il numero
di nodi che sono stati saltati dopo l’ultimo stampato). */

int main() {
    int dim;
    cin >> dim;
    int* a = new int[dim];
    for (int i=0; i<dim; i++)
        cin >> a[i];
    nodo* root = NULL;
    root = buildTree(a, 0, dim);
    stampa_l(root);
    int k;  
    cin>>k;

    cout << endl;    

    int a1 = stampaASPre(root, k-1, k);
    cout << "con avanzo " << a1 << endl;
    int b1 =  stampaASInf(root, k-1, k);
    cout << "con avanzo " << b1 << endl;
   
}

/* DIMOSTRAZIONE DI CORRETTEZZA stampaASPre:

CASO BASE: albero(r) vuoto, restitusce n = k-1 cioè due nodi da saltare => vale POST.
PASSO INDUTTIVO: Vale PRE, se albero(r) non vuoto, sse n = 0 viene stampato il nodo e n=k, altrimenti n=n-1 e resta minore di k, quindi valgono PRE_RIC1 e PRE_RIC2; 
                 supponiamo allora che valgano POST_RIC1 e POST_RIC2, allora viene restituito n che è uguale al numero dei nodi da saltare => vale POST.

*/

/* DIMOSTRAZIONE DI CORRETTEZZA stampaASInf:

CASO BASE: albero(r) vuoto, restitusce n = k-1 cioè due nodi da saltare => vale POST.
PASSO INDUTTIVO: Vale PRE, se albero(r) non vuoto, allora n è sempre uguale e vale PRE_RIC1, viene esaminato l'albero
                 sinistro e incrementato n secondo l'ordine infisso, quando si giunge ad una foglia sinistra; quando n=0
                 viene stampato il nodo e riportata n=k e poi decrementata; dopo essere passati dalla radice si esamina
                 l'albero destro e si restituisce n = n nodi da saltare, cioè POST_RIC2 => vale POST.

*/
