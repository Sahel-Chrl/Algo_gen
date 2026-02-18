#include "Paysage.h"

int main()
{
    srand(time(NULL));
    Paysage p;

    int nbCircles, nbSquares, nbTri;
    cout << "combien de cercles dans ton paysage ?"<<endl;
    cin >>nbCircles;
    cout << "combien de Carrés dans ton paysage ?"<<endl;
    cin >>nbSquares;
    cout <<"combien de triangles dans ton paysage ?"<<endl;
    cin >>nbTri;

    auto centresCircles = p.circleCenter(nbCircles);
    auto rayons = p.createRayons(nbCircles);
    auto centresSquares = p.squareCenter(nbSquares);
    auto coteSquares = p.createCote(nbSquares);
    auto centresTri = p.triCenter(nbTri);
    auto coteTri = p.createCoteTri(nbTri);

    p.affiche(centresCircles, rayons, nbCircles,
        centresSquares, coteSquares, nbSquares,
        centresTri, coteTri, nbTri);
    return 0;
}

