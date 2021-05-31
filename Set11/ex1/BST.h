#ifndef BST_H
#define BST_H
namespace BST
{
struct nodo{
    int info;
    nodo* left,*right;
    nodo(int a=0, nodo*b=0, nodo*c=0) 
    {info=a; left=b; right=c;}
};
    
void stampa_l(nodo*);
nodo* insert(nodo*, int);
bool search (nodo*, int);
nodo* max(nodo*);
nodo* min(nodo*);
int altezza(nodo*);
int altMin(nodo*);
};

#endif