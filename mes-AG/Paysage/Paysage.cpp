#include "Paysage.h"


Color random_col()
{
	return Color(
		static_cast<int>((int)((double)rand()/RAND_MAX * 255)),
		static_cast<int>((int)((double)rand()/RAND_MAX * 255)),
		static_cast<int>((int)((double)rand()/RAND_MAX * 255)));
}

float randfloat(){
     return (static_cast<float>(rand()) / RAND_MAX) ;
}

float random_coord(){
    return (static_cast<float>(rand()) / RAND_MAX) * 600;
}

Cercle::Cercle(){
    x = random_coord();  // Random value between -300 and 300
    y = random_coord();  // Random value between -300 and 300
    rayon = randfloat()*65;     // Random value between 0 and 75
}

CircleShape Cercle::draw(Color color)
{
        CircleShape circle(rayon);
        circle.setFillColor(color);
        circle.setOrigin(Vector2f(rayon, rayon));
        circle.setPosition(Vector2f(x, y));
return circle;
}

void Cercle::print()
{
    cout<< x <<" "<<y<<" "<<rayon<<endl;
}

Carre::Carre(){
    x=random_coord();
    y=random_coord();
    cote=randfloat()*65;
}
void Carre::print()
{
    cout<< x <<" "<<y<<" "<<cote<<endl;
}

RectangleShape Carre::draw(Color color)
{
        RectangleShape square(Vector2f(cote, cote));
        square.setFillColor(color);
        square.setPosition(Vector2f(x, y));
        square.setRotation(radians(rotation));
        return square;
}

Paysage::Paysage()
{
    int nbCircles, nbSquares, nbTri, nbChromosomes;
    cout << "combien de cercles dans ton paysage ?"<<endl;
    cin >>nbCircles;
    cout << "combien de Carrés dans ton paysage ?"<<endl;
    cin >>nbSquares;
    for (int i=0; i<nbCircles; i++){
        cercles.push_back(Cercle());
    }
    for (int j=0; j<nbSquares; j++){
        carres.push_back(Carre());
    }
    for (int i=0 ; i<600; i=i+step){
        vector<bool> ligne;
        for (int j=0; j<600 ; j=j+step){
            ligne.push_back(false);
        }
        tableau.push_back(ligne);
    }
    //remploir le tableau de true fals paysage en lisznt les pixels
}
