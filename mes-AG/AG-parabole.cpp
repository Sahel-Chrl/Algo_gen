#include <iostream>
#include <random>
#include <vector>
#include <array>
#include <utility>
#include <cmath>
//#include <SFML/Graphics.hpp>  // Nécessaire pour RenderWindow
using namespace std;


/* 
notre objectif et de prendre des points au hasard dans R2 
et de trouver la parabole pour laquelle la distance moyenne (verticale) des 
points a la courbe est la plus faible
Ma population d'individus va etre composé de 100 individus () qui s'amelioreront petit a petit
*/


float hasard() {
    return (float)rand();
} // fonction nombre aleatoire pour mes coefs

float hasard100() { //float aleatoire -100 100.
    float x;
    x= (float)rand()/RAND_MAX;
    x=200*x-100; 
    return x;
}

float racine(float x) {
    return sqrt(x);
}


typedef vector<pair<double, double>> points;


points couple(
    int n
){
    points result;
    result.reserve(n); //on a cree "l'emplacement" pour nos vecteur qu'on va ensuite generer

    //maintenant le generateur
    for (int i=0; i<n; i++){
        double x = hasard100();
        double y = hasard100();
        result.emplace_back(x, y); //on range le couple cree
    }
    return result;
}


//on va creer ici notre population de paraboles
vector<array<double, 3>> create_coefs(int n){
    vector<array<double, 3>> result;
    result.reserve(n);

    for (int i=0; i<n; i++){
        double x = hasard100();
        double y = hasard100();
        double z = hasard100();
        result.push_back({x, y, z});
    }
    return result;
}

typedef array<double,3> coefs;

float valeur(float x, coefs p) {
    float y;
    y = p[0]*x*x + p[1]*x + p[2];
    return y;
}// fonction qui calcule la valeur en x


double distance(float z, float t, coefs p) {
    float y,d;
    y= valeur(z,p);
    d= abs(y-t);
    return d;
} //on calcule ici la distance verticale du point z,t a la courbe


float distancemoy( coefs c, points p){
float d;
int n= p.size();
   d=0;
   for (auto point : p){
    d=d+distance(point.first,point.second,c);
   }
   d=d/n;
   return d;
}//on a calculer la distance moyenne


int affiche(){
    /*sf::RenderWindow window(sf::VideoMode(800, 600), "Graph of f(x)");

    // Créer un tableau de points
    sf::VertexArray points(sf::LinesStrip);

    // Remplir les points avec les valeurs de la fonction
    for (double x = -400; x < 400; x++) {
        double y = f(x * 0.01) * 100;  // Transformation pour adapter à la fenêtre
        points.append(sf::Vertex(sf::Vector2f(x + 400, 300 - y), sf::Color::Red));  // Déplacement des points
    }

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(points);  // Dessiner la courbe
        window.display();
    }

    return 0;*/

    //truc de chatgpt mais ça sert a rien de juste le copier donc j'attends de bien comprendre
    return 0;
}

int main(){
    int n,m;
    cout << "Combien de point voulez vous ?"<<endl;
    cin>> n; 
    cout << "Combien de paraboles ?"<<endl;
    cin >>m;

    //appel d'une liste de couple
    auto points = couple(n);
    if (n<5){
        cout<< "Voici les points pris" <<endl;
        for (const auto point : points){
        cout<< "("<<point.first<<","<<point.second<<")"<<endl<<endl;
        }
    }
    else {
        /*cout << "Voici quelques points pris" <<endl;
        for (const auto& [x, y] : points){
        cout<< "("<<x<<","<<y<<")"<<endl<<endl;*/
        cout << "Beaucoup de points donc je ne les affiches pas." << endl<<endl;
    }

    //appel d'une liste de triplets pour la parabole
    auto triplets = create_coefs(m);
    // afficher les triplets
    for ( auto parabole : triplets){ 
        cout<<"Triplet: ("<<parabole[0]<<","<<parabole[1]<<","<<parabole[2]<<")"<<endl;
        cout<<"Distance moyenne : "<< distancemoy(parabole, points)<<endl<<endl;

    }


    return 0;
}
