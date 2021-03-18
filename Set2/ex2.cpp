#include<iostream>
using namespace std;

int leggi(int *X, int dim);

void stampa(int *X, int dim);

int main()
{
    int A[30];
    int n = leggi(A, 30);
    int x = A[0];
    int i = 1, j = 1;
    int temp; // n da sottrarre all'indice di A
  
    // PRE = (0 < n <= 30) && (A[0..n-1] contiene solo 2 valori distinti)
    
    while (i < n-j) {  // R = (1 <= i < n-j) && (A[0..i-1] == x)
        if (A[i] != x) {
            while (A[n-j] != x) {
                j++;
                if (i == n-j) {
                    break;
                }

            }
            temp = A[n-j];
            A[n-j] = A[i];
            A[i] = temp;
        }
        i++;
    }
     
    stampa(A, n);

    return 0;
}

int leggi(int *X, int dim) {
    int n, i = 0;
    do {
        cin >> n; // n = dimensione nuovo array
    } while (n < 1 || n > dim);

    while (i < n) {
        cin >> X[i];
        i++;
    }

    return n;
}

void stampa(int *X, int dim) {
    int i = 0;
    while (i < dim) {
        cout << X[i] << " ";
        i++;
    }
    cout << endl;
}

// POST = (A[0..n-1-j] == x) && (A[n-j..n-1] != x)