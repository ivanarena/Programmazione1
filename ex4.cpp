#include <iostream>
#include <string>
using namespace std;

int main()
{
    char C[10];
    string c;
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
        c = C[i];
        if (open == closed && c == ")") {
            ok = false;
            break;
        }
        if (c == "(") {
            open++;
        } else if (c == ")") {
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
