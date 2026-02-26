#include "Individu.h"

Individu::Individu(int nbChromosomes)
{
    int nbCarres, nbCercles;
nbCarres = (int)(randfloat() *nbChromosomes);
nbCercles = nbChromosomes-nbCarres;
for(int i=0;i<nbCarres; i++){
    carres.push_back(Carre());
}
for(int j=0;j<nbCercles; j++){
    cercles.push_back(Cercle());
}
}

float Individu::score(Paysage &paysage)
{
    
}
