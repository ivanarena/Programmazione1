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


void stampa_l(nodo *r)
{
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


void buildBST(nodo*&r,int x)
{
    // cout << "inserisco "<<x<<endl;
    if(!r) {r=new nodo(x);return;}
    if(r->info>= x)
        buildBST(r->left,x);
    else
        buildBST(r->right,x);
}

// PRE = (albero(r) ben formato, x1<=y<=x2)
void calcIntMin(nodo* r, int & x1, int & x2, int y) {
    if (!r) {
        return;
    } else {
        if (r->info == y) { 
            x1 = y;
            x2 = y;
        } else {
            if (r->info < y && r->info > x1) { // minore 
                x1 = r->info;
            } else if (r->info > y && r->info < x2) { // maggiore
                x2 = r->info;
            }
            calcIntMin(r->left, x1, x2, y);
            calcIntMin(r->right, x1, x2, y);
        }
    }
}
// POST = ([x1,x2] è il più piccolo intervallo che racchiude y)

// PRE = (albero(r) ben formato, x1<=y<=x2)
void calcIntMinBST(nodo* r, int & x1, int & x2, int y) {
    bool end1 = false;
    bool end2 = false;
    nodo* t = r;
    while (!end1) { // cerchiamo x1 // R = (x1<=y<=x2)
        if (!r) {
            end1 = true;
        } else if (r->info == y) {
            x1 = y;
            x2 = y;
            end1 = true;
        } else {
            if (r->info < y) { // cerchiamo x1
                if (r->info > x1) { // se è maggiore sostituiamo
                    x1 = r->info;
                }
                r = r->right; // cerco un x1 maggiore quindi vado a destra
            } else if (r->info > y) { // cerchiamo x1
                r = r->left; // cerco un r minore di y quindi vado a sinistra
            }
        }
    }

    while (!end2) { // cerchiamo x2 // R = (x1<=y<=x2)
        if (!t) {
            end2 = true;
        } else if (t->info == y) {
            x1 = y;
            x2 = y;
            end2 = true;
        } else {
            if (t->info < y) { // cerchiamo x2
                t = t->right; // cerco un r maggiore di y quindi vado a destra
            } else if (t->info > y) {
                if (t->info < x2) {
                    x2 = t->info;
                }
                t = t->left; // cerco un x2 minore quindi vado a sinistra
            }
        }
    }
}
// POST = ([x1,x2] è il più piccolo intervallo che racchiude y)

int main()
{
    int dim;
    cin >>dim;
    nodo*r=0;
    int*A=new int[dim];
    for(int i=0; i<dim;i++) {
	    cin >> A[i];
	    r=buildTree(A,0,dim);
    }
    nodo*r1=0;    
    for (int i=0; i<dim; i++)
        buildBST(r1,A[i]);
    
    stampa_l(r);
    cout<<endl; 
    stampa_l(r1);
       
    bool basta=false;
    int l1,l2,y;
    while(!basta) {
	    cin >> l1 >> l2 >> y;
	    int z1=l1, z2=l2;
	    if(y==-1)
	        basta=true;
	    else {
	        calcIntMin(r,l1,l2,y);
	        cout <<"l1="<<l1<<" l2="<<l2<<endl;

	        calcIntMinBST(r1,z1,z2,y);
	        cout <<"l1="<<z1<<" l2="<<z2<<endl;
	    }
    }
}

/*
y = 6
m1 = 2
m2 = 10

12(3(2(_,_),7(5(4(_,_),_),_)),15(_,_))
            
            12
        3          15
    2       7
          5
         4   

x1 = 5
x2 = 7

7
12 15 3
7 5 4 2
2 10 6


*/