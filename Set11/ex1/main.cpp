#include<iostream>
#include "BST.h"
using namespace std;
using namespace BST;

int main() {
    //prepara un albero iniziale non triviale
    nodo* r=new nodo(15, new nodo(7), new nodo(19));
    r->left->right=new nodo (9, new nodo(8));
    r->right->right=new nodo(25, new nodo(22));
    
    bool stop=false;
    while(!stop) {
        int a, x;
        cin >> a;
        switch (a) {
        case 0:
            stop = true;
            break;
        case 1:
            stampa_l(r);
            break;
        case 2:
            cin >> x;
            insert(r, x);
            stampa_l(r);
            break;
        case 3:
            cin >> x;
            if (search(r, x)) cout << "valore " << x << " presente" << endl;
            else cout << "valore " << x << " non presente" << endl;
            break;
        case 4:
            cin >> x;
            if (x == 1) {
                cout << max(r)->info << endl;
            } else if (x == 2) {
                cout << min(r)->info << endl;
            }
            break;
        case 5:
            cout << altezza(r) << endl;
            break;
        case 6:
            cout << altMin(r) << endl;
            break;
        default:
            break;
        }
    }
}