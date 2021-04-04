#include<iostream>
using namespace std;

void leggi(int* X, int & nelem) {
    bool ok=false;
    while(!ok) {
        cin >> nelem;
        if(nelem>0 && nelem <=49)
        ok=true;
    }
    
    for(int i=0; i < nelem; i++) {
        cin >> X[i];
    }
}

// PRE = Riceve un puntatore agli elementi di una matrice e nelem
void stampa(bool * X, int & nelem) {
    for (int i=1; i <= nelem; i++) {
        if (i % 7 == 0) {
            cout << X[i-1] << endl;
        } else {
            cout << X[i-1] << " ";
        }
    }
    cout << endl;
}
// POST = Stampa una matrice booleana

// PRE = Riceve nelem
int numrows(int nelem) {
    if (nelem % 7 == 0) {
        return nelem / 7;
    } else {
        return nelem / 7 + 1;
    }
}
// POST = Restituisce numero righe riempite

// PRE = Riceve nelem
int numcolumns(int nelem) {
    if (nelem % 7 == 0 || nelem > 7) {
        return 7;
    } else {
        return nelem % 7;
    }
}
// POST = Restituisce numero colonne riempite

// PRE = Riceve due matrici - di cui una vuota - e nelem
void calcB(int (*X)[7], int & nelem, bool (*Y)[7]) {
    int even = nelem % 7;
    int found = 0;
    int nrows = numrows(nelem);
    int ncols = numcolumns(nelem);
    int lastncols = ncols;
    for (int row = 0; row < nrows; row++) {
        for (int col = 0; col < ncols; col++) {
            for (int relem = 0; relem < lastncols; relem++) {
                if (even != 0 && row == nrows-1) {
                    lastncols = even;
                }
                for (int celem = 0; celem < nrows; celem++) {
                    if (X[row][relem] == X[celem][col]) {
                        found++;
                        break;
                    }
                }
            }
            if (found == lastncols) {
                Y[row][col] = 1;
            } else {
                Y[row][col] = 0;
            }
            found = 0;
        }
        
    }
    nelem += ((nelem/7 + 1)*7) - nelem; // updates nelem to fill B matrix
}
// POST = Riempie B[i][j] di valori booleani se la riga i è contenuta nella colonna j 

int main() {
    int A[7][7], nelem;
    bool B[7][7]  = {0}, finitoR=false;
    leggi(*A,nelem);
    calcB(A,nelem,B);
    stampa(*B,nelem);
}
