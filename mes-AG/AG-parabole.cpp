#include <iostream>
#include <random>
#include <vector>
#include <utility>
#include <cmath>
using namespace std;

/* 
notre objectif et de prendre des points au hasard dans R2 
et de trouver la parabole pour laquelle la distance moyenne (verticale) des 
points a la courbe est la plus faible
*/


float hasard() {
    return (float)rand();
} // fonction nombre aleatoire pour mes coefs

float hasard100() {
    float x;
    x= (float)rand()/RAND_MAX;
    x=100*x;
    return x;
}

float racine(float x) {
    return sqrt(x);
}




vector<pair<double, double>> couple(
    int n
){
    vector<pair<double, double>> result;
    result.reserve(n); //on a cree "l'emplacement" pour nos vecteur qu'on va ensuite generer

    //maintenant le generateur
    for (int i=0; i<n; i++){
        double x = hasard100();
        double y = hasard100();
        result.emplace_back(x, y); //on range le couple cree
    }
    return result;
}


struct coefs {
    float a,b,c;
}; // je cree mes trois coefs pour la parabole


coefs parabole() {
    return{1.0f,2.0f,3.0f};
}

float valeur(float x) {
    coefs d = parabole();
    float y;
    y = d.a*x*x + d.b*x + d.c;
    return y;
}// fonction qui calcule la valeur en x


double distance(float z, float t) {
    float y,d;
    y= valeur(z);
    d= racine((y-t)*(y-t));
    return d;
} //on calcule ici la distance verticale du point z,t a la courbe


float distancemoy(int n){
float d;
   d=0;
   auto points = couple(n);
   for (const auto& [z, t] : points){
    d=d+distance(z,t);
   }
   d=d/n;
   return d;
}//on a calculer la distance moyenne



int main(){
    int n;
    cout << "Combien de point voulez vous ?"<<endl;
    cin>> n; 

    //appel d'une liste de couple
    auto points = couple(n);
    if (n<5){
        cout<< "Voici les points pris" <<endl;
        for (const auto& [x, y] : points){
        cout<< "("<<x<<","<<y<<")"<<endl<<endl;
        }
    }
    else {
        /*cout << "Voici quelques points pris" <<endl;
        for (const auto& [x, y] : points){
        cout<< "("<<x<<","<<y<<")"<<endl<<endl;*/
        cout << "Beaucoup de points donc je ne les affiches pas." << endl<<endl;
    }

    float d=distancemoy(n);
    cout << "Voici la distance moyenne (verticale) entre les points et la courbe :  " << d <<endl;

    return 0;
}
