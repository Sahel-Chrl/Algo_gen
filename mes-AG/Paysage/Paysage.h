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

//cree une fenere 100 sur 100 qui affiche un paysage 
using centre= vector<pair<double,double>>;


class Paysage { 
    int nbCercles;  
    public : 
        Color random_col();
        centre circleCenter(int nbCercles);
        vector<double> createRayons(int nbCercles);
        centre squareCenter(int nbCarres);
        vector<double> createCote(int nbCarres);
        centre triCenter (int nbTri);
        vector<double> createCoteTri(int nbTri);

        void affiche(const centre& centresCircles,const vector<double>& rayons, int nbCercles,
            const centre& centreSquares, const vector<double>&coteSquares, int nbCarres,
            const centre& centreTri, const vector<double>&coteTri, int nbTri);
};