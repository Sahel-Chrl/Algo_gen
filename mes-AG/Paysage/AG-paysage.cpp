#include "Paysage.h"
#include "Individu.h"

int main()
{
    srand(time(NULL));
    Paysage paysage;
    int nbChromosomes,pas;


    cout <<"combien de chromosomes par individus ?"<<endl;
    cin >> nbChromosomes;
    Individu individu(nbChromosomes);
    cout << "Quel pas entre les pixels pour la comparaison d'image ?"<<endl;
    cin >> pas;

    individu.affiche(individu, paysage); //affiche capture l'image et la stocke dans individu
    individu.score(individu,pas);
    return 0;
}

