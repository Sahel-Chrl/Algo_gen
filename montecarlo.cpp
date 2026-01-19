#include <iostream>
using namespace std;
#include <random>

// exemple methode de montecarlo; approximation de pi


float hasard () {
    return (float)rand()/RAND_MAX;
} //fonction alea entre 0,1

int main () {
    cout<< "Bonjour!!" <<endl;
    float x,y;
    int n,m;
    cout << "Donne un entier" << endl;
    cin >> n;
    m=0;
    for (int i=1 ; i<=n ; i++ ) {
        x=hasard();
        y=hasard(); // appel de la fct
        if (x*x+y*y<=1) {
            m++;
            //ajout d'un point dans le cercle
        }
    }
    cout << 4.*m/n << endl; // calcul de pi
    return 0;
}