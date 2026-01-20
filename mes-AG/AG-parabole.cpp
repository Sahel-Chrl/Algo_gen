#include <iostream>
#include <random>
#include <vector>
#include <utility>
#include <cmath>
using namespace std;

/* 
notre objectif et de prendre des points au hasard dans R2 
et de trouver la parabole pour laquelle la distance moyenne des 
points a la courbe est la plus faible
*/


float hasard() {
    return (float)rand();
} // fonction nombre aleatoire pour mes coefs

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
        double x = hasard();
        double y = hasard();
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
    float y,x,d,l;
    x=hasard();
    y = valeur(x);
    d= racine((x-z)*(x-z)+(y-t)*(y-t));
    l=d;
    for (int i=1; i<=1000; i++){
        if (d>=l){
            x=hasard();
            d=racine((x-z)*(x-z)+(y-t)*(y-t));
        }
        else {
            l=d;
        }
    }// bof j'aproxime la distance min mais il me manque un truc la
    return d;
}



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
    

   float d; //on va calculer la distance moyenne
   d=0;
   for (const auto& [z, t] : points){
    d=d+distance(z,t);
   }
   d=d/n;
   cout << "Voici la distance moyenne entre les points et la courbe :  " << d <<endl;

    return 0;
}
