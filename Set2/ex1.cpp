#include <iostream>
using namespace std;

int leggi(int *X, int dim);

void stampa(int *X, int dim);

int main() {
  int A[30], y, i = 0, j;
  int n = leggi(A, 30);
  
  cin >> y; // inserisci valore da eliminare

  while (i < n) { // R = (0 <= i < n) && (A[0..i-1] != y)
    if (A[i] == y) {
      j = i;
      n--;

      while (j < n) { // shifta il resto degli elementi
        A[j] = A[j+1];
        j++;
      }

    } else {
      i++;
    }
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

// POST = (A[0..n-1] != y)
