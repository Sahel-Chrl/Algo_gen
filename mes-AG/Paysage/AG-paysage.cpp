#include "Population.h"

int main()
{
    srand(time(NULL));
    Paysage paysage;
    int pas;
    Individu individu;
    cout << "Quel pas entre les pixels pour la comparaison d'image ?"<<endl;
    cin >> pas;
    Population popultation;

    individu.affiche(individu, paysage); //affiche capture l'image et la stocke dans individu
    return 0;
}


