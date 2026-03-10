#include "Paysage.h"
#include "Individu.h"

class Population {
    public:
        vector<int> scores;
        int pas;
        vector<Individu*> individus;
        float scoreMoyen();
        int minScore();
        vector<int> scoreNegToPos();
        vector<float> score2probas(); // je pourrais/voudrais mettre un tableau d'individu et stoquer le score de l'indiv dans individu et pas la fct score seulement (comme ça je le calcule la bas et j'ai moins de trucs dans le main)
        vector<float> probas2cumul(vector<float> probas);
        int numIndiv(vector<float> cumul);
        Population(vector<Individu*>,int pas);
        void nextGeneration();
};