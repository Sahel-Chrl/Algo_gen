#include "Paysage.h"

int main()
{
    srand(time(NULL));
    Paysage p;
    int nbChromosomes;


    cout <<"combien de chromosomes par individus ?"<<endl;
    cin >> nbChromosomes;

    p.affiche();
    return 0;
}

