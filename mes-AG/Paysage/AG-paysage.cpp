#include "Population.h"

int main()
{
    srand(time(NULL));
    Paysage paysage;
    int pas,nbIndividus,nbChromosomes;

    cout << "Quel pas entre les pixels pour la comparaison d'image ?"<<endl;
    cin >> pas;
    cout << "combien d'individus dans une population ?"<<endl;
    cin >> nbIndividus;
    cout <<"combien de chromosomes(cercles/carres) par individus ?"<<endl;
    cin >> nbChromosomes;

    vector<Individu*> individus;
    for (int i= 0; i<nbIndividus; i++){
        Individu *individu=new Individu(nbChromosomes);
        individus.push_back(individu);
        if(i==0) individu->clignote=false;
        individu->affiche(paysage);
        cout << "score : " << individu->score(pas)<<endl;
    }
    Population pop(individus,pas);
    pop.nextGeneration();
    


    return 0;
}


