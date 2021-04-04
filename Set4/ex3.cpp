#include <iostream>
using namespace std;

void leggi(int*X, int nelem) {
    for(int i=0; i < nelem; i++) {
        cin >> X[i];
    }
}

void stampa(bool (*B)[5],int righe) {
    for(int i=0; i<righe; i++) {
        for(int j=0;j<5; j++ ) {
	        cout<<B[i][j]<<' ';
        }
        cout<<endl;
    }
}

void calcB(int (*A)[6][5],bool (*B)[5]) {
    int found = 0;
    for (int i=0; i<6; i++) { // rows
        for (int j=0; j<5; j++) { // columns
            for (int h=0; h<5*3; h++) { // h-slices
                for (int v=0; v<6*3; v++) { // v-slices
                    if (A[h/5][i][h%5] == A[v/6][v%6][j]) {
                        found++;
                        break;
                    }
                }
            }
            if (found == 5*3) { 
                B[i][j] = 1;
            } else {
                B[i][j] = 0;
            }
            found = 0;
        }
    }
}

int main() {
    int A[3][6][5];
    bool B[6][5];
    leggi(**A,90);
    calcB(A,B);
    stampa(B,6);
}