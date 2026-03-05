#include "Paysage.h"


class Individu {
    public:
        vector<Cercle> cerclesIndiv;
        vector<Carre> carresIndiv;
        Individu(int);
        void affiche(Individu individu, Paysage paysage);
        const Image& getScreenshot() const { return screenshot; } // lecture
        float score(Individu individu, int pas);
        Individu mutation();
    private:
        Image screenshot;
};