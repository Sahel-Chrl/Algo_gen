#include <iostream>
using namespace std;
#include <random>

float hasard () {
    return (float)rand()/RAND_MAX;
}

int main () {
    cout<< "Bonjour" <<endl;
    float x,y;
    int n,m;
    cout << "donne un entier" << endl;
    cin >> n;
    m=0;
    for (int i=1 ; i<=n ; i++ ) {
        x=hasard();
        y=hasard();
        if (x*x+y*y<=1) {
            m++;
            //point dans le cercle
        }
    }
    cout << 4.*m/n << endl;
    return 0;
}