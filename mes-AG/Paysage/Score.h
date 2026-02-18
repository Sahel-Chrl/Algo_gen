
#include "Paysage.h"



using centre = vector<pair<double,double>>;
struct chromosome {
    double rayon;
    centre c;
};
using individu = vector<chromosome>;
using population = vector<individu>;

class Score {
    int nbChromosomes;
    individu createIndiv(int nbChromosomes);
    float scoreIndividu(individu indiv, Paysage pays);
};