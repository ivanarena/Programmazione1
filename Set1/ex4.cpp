#include <iostream>
using namespace std;

int main()
{
    char C[10];
    bool ok = true;
    int i=0; 
    int open = 0, closed = 0;
    while(i<10)
    {
        cin >> C[i];
        i=i+1;
    }
    i = 0;
    while (i<10)
    {
        if (open == closed && C[i] == ')') {
            ok = false;
            break;
        }
        if (C[i] == '(') {
            open++;
        } else if (C[i] == ')') {
            closed++;
        }
        i++;
    }

    if (open == closed && ok) {
        cout << "bilanciato" << endl;
    } else {
        cout << "non bilanciato" << endl;
    }

    return 0;
}
