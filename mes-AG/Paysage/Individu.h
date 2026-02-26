#include "Paysage.h"


class Individu {
    public:
    vector<Cercle> cercles;
    vector<Carre> carres;
    Individu(int);
    float score(Paysage &paysage);
    Individu mutation();
};