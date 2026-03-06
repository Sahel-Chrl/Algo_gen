#include "Paysage.h"


class Individu {
    public:
        Individu();
        vector<Cercle> cerclesIndiv;
        vector<Carre> carresIndiv;
        void affiche(Individu individu, Paysage paysage);
        const Image& getScreenshot() const { return screenshot; } 
        float score(Individu individu, int pas);//ici on a la fonction score qu'on pourra utiliser dans le main mais j'aimerais stoquer le score dans l'individu, pour ça il faut que je mette float score = score(Individu individu, int pas) ? ça marche pas
    private:
        Image screenshot;
};