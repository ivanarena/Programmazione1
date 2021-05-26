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

int height(nodo* root) {
	if(!root) {
		return 0;
	}
	return 1 + max(height(root->left), height(root->right));
}

void stampa_l(nodo *r) {
    if(r) {
        cout<<r->info<<'(';
        stampa_l(r->left);
        cout<<',';
        stampa_l(r->right);
        cout<<')';
    } else
        cout<< '_';
}

void sc(int*C) {
    cout<<*C<<' ';    
    if(*C!=-1)
    sc(C+1);
}

// PRE = (albero(r) è ben formato e non vuoto, k>=0 e y valore qualsiasi, C ha almeno tanti elementi quanta è l'altezza di albero(r))
bool cerca_cam(nodo* r, int k, int y, int* C) {
    // base cases 
    if (!r->left && !r->right) { // if r leaf
        if ((k == 0 && r->info != y) || (k == 1 && r->info == y)) { // y found k times or found k-1 times and current node->info == y
            *C = -1; // sets array end
            return true;
        } else {
            return false;
        }
    } 

    if (r->info == y) {
        if (cerca_cam(r->left, k-1, y, C+1)) {
            *C = 0;
            return true;
        } else if (cerca_cam(r->right, k-1, y, C+1)) {
            *C = 1;
            return true;
        } else {
            return false;
        }
    } else { 
        if (cerca_cam(r->left, k, y, C+1)) {
            *C = 0;
            return true;
        } else if (cerca_cam(r->right, k, y, C+1)) {
            *C = 1;
            return true;
        } else {
            return false;
        }
    }
    // reminder to insert -1 at the end of arr C, calculating maybe height with given function
}
/* POST= (restituisce true sse in albero(r) esiste un cammino da r ad una foglia con esattamente k
nodi con campo info=y e false altrimenti) &&(in caso restituisca true, C contiene una sequenza
(anche vuota) di 0/1 seguita da -1 e che individua il cammino più a sinistra in albero(r) con
esattamente k nodi con campo info=y). */

int main() {
    int dim;
    cin >> dim;
    int* a = new int[dim];
    for (int i=0; i<dim; i++)
        cin >> a[i];
      
    nodo* root = NULL;
    root = buildTree(a, 0, dim);
    stampa_l(root);
    cout << endl;
    int h = height(root);
    int* C = new int[h];
   
    int k, val;  
    cin >> val >> k;    
    
    bool b = cerca_cam(root,k,val,C);
    cout << endl;
    if(b) {
        cout << "trovato  cammino= ";
        sc(C);
        cout << endl;
    } else
        cout <<" nessun cammino con "<< k <<" valori= "<< val << endl;
  
}

/*

DIMOSTRAZIONE DI CORRETTEZZA:

CASO BASE: albero(r) contiene solo la radice (che è anche una foglia) e o k è 0 oppure k è 1 e la radice ha campo info uguale a y,
           in entrambi casi la PRE è rispettata e viene restituito true e |C|=1 => vale POST.
CASO RICORSIVO: Vale PRE, assumiamo vero il passo ricorsivo, allora se siamo nel caso base avremo true sse il cammino è stato trovato o false altrimenti,
                se non siamo nel caso base, la funzione effettuerà un'altra chiamata ricorsiva, fin quando non arriverà al caso base, dove vale POST,
                come già dimostrato sopra. 

*/
