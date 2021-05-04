#include<iostream>
using namespace std;

struct stringa {
    int lung;
    char S[20];
    stringa(int a=0, char* b=0) {
        lung=a;
        for(int i=0; i<lung; i++)
            S[i]=b[i];
    }
    bool operator<=(const stringa &Z);
};

istream& operator>>(istream &stream, stringa &Z) {
    stream >> Z.lung >> Z.S;
    return stream;
}

ostream& operator<<(ostream &stream, stringa &Z) {
    stream << "la stringa e':" << endl;
    stream << Z.S << endl;
    return stream;
}

bool stringa::operator<=(const stringa & Z) {
    for (int i=0; i<lung; i++) {
        if (S[i] < Z.S[i]) {
            return true;
        } else if (S[i] > Z.S[i]) {
            return false;
        }
    }
}
 
int main() {
    stringa X, Y, Z, W;
    cin >> X >> Y >> Z >> W;
    if(X <= Y)
        cout << X;
    else
        cout << Y;
    
    if(Y <= X)
        cout << Y;
    else
        cout << X;
    
    if(X <= Z)
        cout << X;
    else
        cout << Z;
    
    if(X <= W)
        cout << X;
    else
        cout << W;
    
    if(!(Z<=W))
        cout<< Z;
    else
        cout<<W;
}





