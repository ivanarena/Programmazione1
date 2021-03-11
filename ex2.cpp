#include <iostream>
using namespace std;

int main()
{
    int num[20];
    int i = 0, ones = 0, twos = 0, threes = 0, fours = 0, fives = 0;

    while (i<20) {
        cout << "Enter an integer: ";
        cin >> num[i];
        switch (num[i])
        {
        case 1:
            ones++;
            break;
        case 2:
            twos++;
            break;
        case 3:
            threes++;
            break;
        case 4:
            fours++;
            break;
        case 5:
            fives++;
            break;
        default:
            break;
        }
        ++i;
    }

    cout << "_________________" << endl;
    cout << "Ones: " << ones << endl;
    cout << "Twos: " << twos << endl;
    cout << "Threes: " << threes << endl;
    cout << "Fours: " << fours << endl;
    cout << "Fives: " << fives << endl;

    return 0;
}