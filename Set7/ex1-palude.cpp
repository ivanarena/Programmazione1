#include<iostream>
using namespace std;

void leggi_ric(bool* A, int size) {
    if (size != 0) {
        cin >> A[0];
        leggi_ric(A+1, size-1);
    }
}

void print_path_ric(int * B, int index, int size) { 
    if (size != 0) {
        cout << "(" << index << "," << B[0] << ")" << " ";
        print_path_ric(B+1, index+1, size-1);
    }

}

void buildPath(bool (*A)[8], int row, int column, int* B) {
    if (row == 8) {
        return;
    }
    if (A[row][column] == 1) {
        B[row] = column;
        buildPath(A, row+1, 0, B);
    } else {
        buildPath(A, row, column+1, B);
    }
}

bool findPath(bool (*A)[8], int row, int column) { // trova un cammino
    if (row == 7) {
        return true;
    }
    if (column == 0) { // controllo giù e giù-dx
        if (A[row+1][column] == 1) {
            findPath(A, row+1, column);
        } else if (A[row+1][column+1] == 1) {
            findPath(A, row+1, column+1);
        } else {
            return false; // cammino non trovato
        }
    } else if (column == 7) { // controllo giù e giù-sx
        if (A[row+1][column-1] == 1) {
            findPath(A, row+1, column-1);
        } else if (A[row+1][column] == 1) {
            findPath(A, row+1, column);
        } else {
            return false; // cammino non trovato
        }
    } else {
        if (A[row+1][column-1] == 1) {
            findPath(A, row+1, column-1);
        } else if (A[row+1][column] == 1) {
            findPath(A, row+1, column);
        } else if (A[row+1][column+1] == 1) {
            findPath(A, row+1, column+1);
        } else {
            return false; // cammino non trovato
        }
    }
}

bool findOne(bool (*A)[8], int row, int column) {
    if (column == 8) {
        return false; // colonna finita == 1 non trovato
    }
    if (row == 8) {
        return true; // righe finite == cammino trovato?
    }
    if (A[row][column] == 1) { // cerca l'1
        if (findPath(A, row, column)) {
            return true; // cammino trovato
        } else {
            A[row][column] = 0;
            findOne(A, row, column+1);
        }
    } else {
        findOne(A, row, column+1);
    }
}

int main() {
    bool Palude[8][8];
    leggi_ric(*Palude, 64);

    bool stop = false;
    int Path[8] = {};

    stop = findOne(Palude, 0, 0);

    if (stop) {
        buildPath(Palude, 0, 0, Path);
        print_path_ric(Path, 0, 8);
    } else {
        cout << "nessun cammino" << endl;
    }
}

