#include <iostream>
using namespace std;

// read 20 integers and print the sum of the positives and the sum of the negatives
int main()
{
    int i = 0;
    int pos = 0, neg = 0;
    int num[20];
    
    while (i < 20) {
        cout << "Enter an integer: ";
        cin >> num[i];
        if (num[i] >= 0) {
            ++pos;
        } else {
            ++neg;
        }
        ++i;
    }

    cout << pos << " " << neg << endl;
    return 0;
}