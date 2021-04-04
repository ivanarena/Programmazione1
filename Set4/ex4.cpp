#include<iostream>
using namespace std;

void leggi(int* X, int& nelem) {
    cin >>nelem;
    for(int i=0; i < nelem; i++) {
        cin >> X[i];
    }
    for (int j=nelem; j < 3*6*5; j++) { // fills array with -1 for future reference
        X[j] = -1;
    }
}

void stampaB(bool * X, int & nelem) {
    if (nelem < 30) { // completes boolean matrix
        for (int i=1; i <= nelem; i++) {
            if (i % 5 == 0) {
                cout << X[i-1] << endl;
            } else {
                cout << X[i-1] << " ";
            }
        }
        cout << endl;
    } else { 
        for (int i=1; i <= 30; i++) {
            if (i % 5 == 0) {
                cout << X[i-1] << endl;
            } else {
                cout << X[i-1] << " ";
            }
        }
        cout << endl;
    }
}

// calculates number of layers
int calcS(int nelem) {
    if (nelem <= 30) {
        return 1;
    } else if (nelem > 30 && nelem <= 60) {
        return 2; 
    } else {
        return 3;
    }
}

// calculates number of rows in the first layer
int calcH(int nelem) {
    if (nelem <= 30 && nelem % 5 == 0) {
        return nelem / 5;
    } else if (nelem <= 30 && nelem % 5 != 0) {
        return nelem / 5 + 1;
    } else if (nelem > 30) {
        return 6;
    } 
}

// calculates number of columns in the first layer
int calcV(int nelem) {
    if (nelem < 5) {
        return nelem % 5;
    } else {
        return 5; 
    }
}

// calculates number of elements in H-slice
int calcHelem(int nelem) {
    if (nelem <= 5) {
        return nelem;
    } else {
        return 6*calcS(nelem);
    }
}

// calculates number of elements in V-slice
int calcVelem(int nelem) {
    if (nelem % 5 == 0) {
        return nelem / 5;
    } else {
        return nelem / 5 + 1; 
    }
}

void calcB(int (*A)[6][5], int& nelem,bool (*B)[5]) {
    int found = 0; // init counter
    int numS = calcS(nelem); // stores number of layers
    int rows = calcH(nelem); 
    int cols = calcV(nelem);  
    int nHelem = calcHelem(nelem);
    int nVelem = calcVelem(nelem);
    int tempnVelem = nVelem; // allows to reset number of elements in V-slice
    for (int i=0; i<rows; i++) { // rows
        for (int j=0; j<cols; j++) { // columns
            for (int h=0; h<nHelem; h++) { // h-slices
                if (A[h/5][i][h%5] == -1) { // decrements number of elements in H-slice
                    nHelem--;
                    continue;
                }
                for (int v=0; v<tempnVelem; v++) { // v-slices
                    if (A[h/5][i][h%5] == A[v/6][v%6][j]) {
                        found++;
                        break;
                    }
                    if (A[v/6][v%6][j] == -1) { // decrements number of elements in V-slice
                        tempnVelem--;
                        break;
                    }
                }
            }
            if (found == nHelem) { 
                B[i][j] = 1;
            } else {
                B[i][j] = 0;
            }
            found = 0;
        }
        tempnVelem = nVelem; // resets number of elements in H-slice
    }
    nelem += ((nelem/5 + 1)*5) - nelem;
}

int main() {
    int A[3][6][5], nelem;
    bool B[6][5];
    leggi(**A,nelem);
    calcB(A,nelem,B);
    stampaB(*B,nelem); 
}

      
