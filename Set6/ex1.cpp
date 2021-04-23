#include<iostream>
using namespace std;

void leggi(bool*B, int nelem) {
    for (int i=0; i<nelem; i++) {
        cin >> B[i];
    }
}

void print_path(int*X, int righe) {
    for(int i=0; i<righe; i++) {
        cout << '(' << i << ',' << X[i] << ')' << ' ';
    }
    cout << endl;
}

// PRE = Riceve Palude
bool mod(bool (*A)[8]) {
    for (int i = 1; i < 8; i++) { // R1 = (1<=i<=8) && A[1..i-1][0..7] controllato
        for (int j = 0; j < 8; j++) { // R2 = (0<=j<=8) && A[i][j] == 0 sse senza cammini
            if (A[i][j] == 1) {
                if (j == 0) { // se primo elem controllo solo due sopra
                    if (!(A[i-1][j] == 1 || A[i-1][j+1] == 1)) {
                        A[i][j] = 0;
                    }
                } else if (j == 7) { // se ultimo elem controllo solo due sopra
                    if (!(A[i-1][j-1] == 1 || A[i-1][j] == 1)) {
                        A[i][j] = 0;
                    }
                } else { // controllo i tre sopra
                    if (!(A[i-1][j-1] == 1 || A[i-1][j] == 1 || A[i-1][j+1] == 1)) {
                        A[i][j] = 0;
                    }
                }
            }
        }
    }
    // POST = Palude è modificata come da consegna

    int count = 0;
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            if (A[i][j] == 1) {
                count++;
            }
        }
        if (count == 0) {
            return true; // manda true a stop sse trova una riga di zeri
        }
    }
    return false; // manda false a stop sse non trova nessuna riga di zeri
    // POST = restituisce vero sse trova una riga di zeri, falso altrimenti
}
// POST = Modifica Palude come da consegna e restituisce a stop vero sse trova una riga di zeri, falso altrimenti

// PRE = Riceve Palude, la lunghezza del cammino ed un array vuoto
void build_path(bool (*A)[8], int size, int (*I)) {
    int lastIndex;
    for (int i=0; i<size; i++) {
        if (A[7][i] == 1) {
            lastIndex = i; // salva l'indice dell'ultimo elemento del cammino
        }
    }
    I[7] = lastIndex; 
    for (int i=6; i>=0; i--) {
        if (lastIndex == 0) {
            if (A[i][lastIndex] == 1) {
                I[i] = lastIndex;
            } else if (A[i][lastIndex+1] == 1) {
                lastIndex = lastIndex + 1;
                I[i] = lastIndex;
            }
        } else if (lastIndex == 7) {
            if (A[i][lastIndex] == 1) {
                I[i] = lastIndex;
            } else if (A[i][lastIndex-1] == 1) {
                lastIndex = lastIndex - 1;
                I[i] = lastIndex;
            }
        } else {
            if (A[i][lastIndex] == 1) {
                I[i] = lastIndex;
            } else if (A[i][lastIndex+1] == 1) {
                lastIndex = lastIndex + 1;
                I[i] = lastIndex;
            } else if (A[i][lastIndex-1] == 1) {
                lastIndex = lastIndex - 1;
                I[i] = lastIndex;
            }
        }
    }
}
// POST = Costruisce un array con gli indici del cammino di Palude 

int main() {
    bool Palude[8][8];
    leggi(*Palude,64);
    bool stop = false;

    stop = mod(Palude); // stop = true sse non c'è cammino
    
    if (!stop) {
        int Path[8];
        build_path(Palude,8,Path);  
        print_path(Path,8);
    }
    else {
        cout << "nessun cammino" << endl;
    }
}

/*

DIMOSTRAZIONE DI CORRETTEZZA SU mod

(1) mod riceve Palude, i=1 && non ho controllato nulla => vale R
(2) i=k && ho controllato A[1..k-1][0..7] => i=k+1 && ho controllato A[1..k][0..7]
(3) i=8 && ho controllato A[1..7][0..7] e modificato tutto => vale POST
    
*/
