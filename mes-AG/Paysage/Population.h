#include "Paysage.h"
#include "Individu.h"

class Population {
    public:
        //vector<Individu> population; //je voudrais utiliser ça plutot que mettre des choses dans le main ? ( sauf si c'est dans population juste apres)
        //Population();
        float scoreMoyen(vector<double>);
        double minScore(vector<double> scores);
        vector<double> score2probas(vector<double> scores); // je pourrais/voudrais mettre un tableau d'individu et stoquer le score de l'indiv dans individu et pas la fct score seulement (comme ça je le calcule la bas et j'ai moins de trucs dans le main)
        vector<double> probas2cumul(vector<double> probas);
        int numIndiv(vector<double> cumul);
        Individu descendent(Individu individu);
};