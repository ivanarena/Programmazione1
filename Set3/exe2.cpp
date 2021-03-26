#include <iostream>
using namespace std;

int leggi(int*X, int dimX)
{
    int k,i=0;
    bool ok=false;
    while(!ok)
    {
        cout<<"dai intero k, 0 < k <"<<dimX<<endl;
        cin >> k;
        if(0<k && k<dimX)
    	    ok=true;
    }
    
    while(i<k)
    {
        cin >>X[i];
        i=i+1;
    }
    return k;
}

void stampa(int*X, int lim)
{
    int i=0;
    while(i < lim)
    {
        cout<<X[i]<<' ';
        i=i+1;
    }
    cout<<endl;
}

int K(int*X, int dim) { 
    for (int i=0; i<dim; i++) { 
        for (int j=i+1; j<dim; j++) {
            if (X[j]==X[i]) {
                for (int k=j; k<dim; k++) {
                    X[k] = X[k+1];
                }
                dim--;
                i--;
            }
        }
    }
    return dim;
}

int main()
{
    int A[30];
    int elemA = leggi(A,30);
    int nNew = K(A,elemA);
    stampa(A,nNew);
}