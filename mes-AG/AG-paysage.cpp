#include "Paysage.h"

int main()
{
    Paysage p;

    int nbCercles;
    cout << "combien de cercles dans ton paysage ?"<<endl;
    cin >>nbCercles;

    auto centres = p.circleCenter(nbCercles);
    auto rayons = p.createRayons(nbCercles);

    p.afficheCerlces(centres,rayons,nbCercles);
    return 0;
}

