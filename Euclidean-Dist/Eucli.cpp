//C++ program for Euclidean Distance and Hamming Distance

#include <bits/stdc++.h>
using namespace std;

float DistEucli(int x1, int y1, int x2, int y2) {
    return sqrt(((x2 - x1)*(x2 - x1))+ ((y2 - y1)*(y2 - y1)));
}

int DistHamm(int n1, int n2) {
    int x = n1 ^ n2;
    int setBits = 0;

    while (x > 0) {
        setBits += x & 1;
        x >>= 1;
    }

    return setBits;
}

int main() {

    //Euclidean Distance
    cout << endl <<"Enter two integers for Euclidean Distance : " << endl ;
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << endl << "Euclidean Distance between (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ") is " << DistEucli(x1, y1, x2, y2) << endl;

    //Hamming Distance
    cout << "Enter two integers for Hamming Distance : " << endl ;
    int n1, n2;
    cin >> n1 >> n2;
    cout << endl << "Hamming Distance between " << n1 << " and " << n2 << " is " << DistHamm(n1, n2) << endl;

    return 0;
}
