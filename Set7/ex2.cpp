#include<iostream>
using namespace std;

void leggi_ric(int* A, int size) {
    if (size != 0) {
        cin >> A[0];
        leggi_ric(A+1, size-1);
    }
}

bool matchFound(int* A, int* B, int LB) {
    if (LB == 0) {
        return true;
    }
    if (A[0] == B[0]) {
        matchFound(A+1,B+1,LB-1);
    } else {
        return false;
    }
}

int searchMatch(int* A, int LA, int* B, int LB, int count) {
    if (LA == LB-1) {
        return -1;
    }
    if (A[0] == B[0]) {
        if (matchFound(A+1,B+1,LB-1)) {
            return count;
        } else {
            searchMatch(A+1,LA-1,B,LB,count+1);
        }
    } else {
        searchMatch(A+1,LA-1,B,LB,count+1);
    }
}

int main() {
    int T[50], P[10], LT, LP;
    cin >> LT >> LP;
    leggi_ric(T,LT);
    leggi_ric(P,LP);
    cout << "inizio match=" << searchMatch(T,LT,P,LP,0) << endl;  
}   

/* 

7 3
0 1 3 0 1 2 3
0 1 2

*/