#include <iostream>
#include <random>
#include <vector>
#include <array>
#include <utility>
#include <cmath>
#include <algorithm>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
#pragma once // pour ne pas changer cercle carre...

//cree une fenere 100 sur 100 qui affiche un paysage 

Color random_col();
float randfloat();

class Cercle {
    public :
    float x; //coordonnées du centre
    float y;
    float rayon;
    Cercle();
    CircleShape draw(Color color);
    void print();
};

class Carre {
    public :
    float x;
    float y;
    float cote;
    float rotation;
    Carre();
    RectangleShape draw(Color color);
    void print();
};

class Paysage {  
    public : 
        vector<Cercle> cercles;
        vector<Carre> carres;
        vector<vector<bool>> tableau;
        int step=5;
        Paysage();
};