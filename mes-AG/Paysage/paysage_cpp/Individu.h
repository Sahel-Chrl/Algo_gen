#include "Paysage.h"

struct coordColor 
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    coordColor(uint32_t c);
};



class Individu {
    public:
        int nbChromosomes;
        bool clignote=true;
        Individu(int nbChrom);
        vector<Cercle> cerclesIndiv;
        vector<Carre> carresIndiv;
        void affiche(Paysage paysage);
        const Image& getScreenshot() const { return screenshot; } 
        float score(int pas);//ici on a la fonction score qu'on pourra utiliser dans le main mais j'aimerais stoquer le score dans l'individu, pour ça il faut que je mette float score = score(Individu individu, int pas) ? ça marche pas
        Individu * descendant();
    private:
        Image screenshot;
};