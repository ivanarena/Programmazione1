#include<iostream>
#include "BST.h"
using namespace std;
using namespace BST;

// (1)
// PRE = (albero(r) ben formato)
void BST::stampa_l(nodo* r) {
    if (r) {
        std::cout << r->info << "(";
        stampa_l(r->left);
        std::cout << ",";
        stampa_l(r->right);
        std::cout << ")";
    } else {
        std::cout << "_";
    }
}
// POST = (stampa albero(r) in formato lineare)

// (2)
// PRE = (albero(r) ben formato)
nodo* BST::insert(nodo* r, int x) {
    if (!r) {
        return new nodo(x);
    } else {
        if (r->info >= x) {
            // PRE_RIC = (nodi a destra sono maggiori di x)
            r->left = insert(r->left, x);
            // POST_RIC = (sse r vuoto x viene inserito)
        } else {
            // PRE_RIC = (nodi a sinistra sono minori di x)
            r->right = insert(r->right, x);
            // POST_RIC = (sse r vuoto x viene inserito)
        }
    }
    return r;
}
// POST = (restituisce albero(r) con l'aggiunta di un nodo con campo info uguale a x in ordine)

// (3)
// PRE = (albero(r) ben formato)
bool BST::search (nodo* r, int x) {
    if (!r) {
        return false;
    } else if (r->info == x) {
        return true;
    } else {
        if (r->info > x) {
            return search(r->left, x);
        } else {
            return search(r->right, x);
        }
    }
}
// POST = (restuisce true sse trova un nodo con campo info uguale a x, false altrimenti)

// (4.1)
// PRE = (albero(r) ben formato)
nodo* BST::max(nodo* r) {
    if (!r) {
        return 0;
    } else {
        if (r->right) {
            return max(r->right);
        } else {
            return r;
        }
    }
}
// POST = (restituisce il nodo con il campo info maggiore)

// (4.2)
// PRE = (albero(r) ben formato)
nodo* BST::min(nodo* r) {
    if (!r) {
        return 0;
    } else {
        if (r->left) {
            return min(r->left);
        } else {
            return r;
        }
    }
}
// POST = (restituisce il nodo con il campo info minore)

// (5)
// PRE = (albero(r) ben formato)
int BST::altezza(nodo* r) {
    if (!r) {
        return 0;
    } else {
        int sx = altezza(r->left);
        int dx = altezza(r->right);

        if (r->left) {
            return 1 + altezza(r->left);
        } else if (r->right) {
            return 1 + altezza(r->right);
        }

        if (sx >= dx) {
            return sx;
        } else {
            return dx;
        }
    }
}
// POST = (restituisce l'altezza di albero(r))

// (6)
// PRE = (albero(r) ben formato)
int BST::altMin(nodo*r) {
    if (!r) {
        return -1;
    }
    if (!r->left && !r->right) {
        return -1;
    } else {
        int sx = altMin(r->left);
        int dx = altMin(r->right);

        if (r->left) {
            return 1 + altMin(r->left);
        } else if (r->right) {
            return 1 + altMin(r->right);
        }

        if (sx <= dx) {
            return sx;
        } else {
            return dx;
        }
    }

}
// POST = (restituisce la lunghezza minima tra i cammini che collegano la radice di albero(r) ad una sua foglia)

/* DIMOSTRAZIONE DI CORRETTEZZA (2)

CASO BASE: se albero(r) è vuoto restituisce un albero formato solo dal nodo con campo info uguale a x.
PASSO INDUTTIVO: Vale PRE, se albero(r) è non vuoto entriamo nell'else, se il nodo attuale ha campo info maggiore o uguale di x controlliamo l'albero sinistro,
                 altrimenti controlliamo quello destro => vale PRE_RIC; supponiamo vera POST_RIC, allora sse r è vuoto x viene inserito a sinistra di un nodo con
                 campo info maggiore o a destra di uno con campo info minore => vale POST.

*/