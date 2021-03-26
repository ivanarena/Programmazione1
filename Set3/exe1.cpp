#include <iostream>
using namespace std;

void leggi(int*X, int k) {
    int i=0;
    while(i<k)
    {
        cin >>X[i];
        i=i+1;
    }
}

void stampaMat(bool (*X)[8], int righe) {
    for(int i=0; i < righe; i++)
    {
        for(int j=0; j<7; j++)
	    cout<<X[i][j]<<' ';
        cout << endl;
    }
  
}

void calcB(int(*A)[8], bool(*B)[8]) {
    int found = 0;
    for (int i=0; i<7; i++) { // R=(0<=i<7)
        for (int j=0; j<8; j++) { // R=(0<=j<8) && B[i][j] == 0 V 1
            for (int k=0; k<8; k++) { // R=(0<=k<8) 
                for (int m=0; m<7; m++) { // R=(0<=m<7) && (0<=found<=8)
                    if (A[i][k] == A[m][j]) {
                        found++;
                        break;
                    }
                } 
            }
            if (found == 8) { 
                B[i][j] = 1;
            } else {
                B[i][j] = 0;
            }
            found = 0;
        }
    }
}

int main() {
    int A[7][8];
    bool B[7][8]; // initializes B
  
    leggi(*A,56); // lo leggiamo come se avesse 1 dimensione
  
    calcB(A,B);
 
    stampaMat(B,7);
}