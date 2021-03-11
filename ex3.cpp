#include<iostream>
using namespace std;

int main()
{
    int A[8], i=0, j=7;
    bool ok;
    while(i<8)
    {
        cin >> A[i];
        i++;  
    }
    i=0;
    while (j>=0) {
        if (A[j] == A[i]) {
            ok = true;
        } else {
            ok = false;
            break;
        }
        j--;
        i++;

    }

    if(ok)
        cout << "e’ un palindromo" << endl;
    else
        cout << "non e’ un palindromo" << endl;

    return 0;
}