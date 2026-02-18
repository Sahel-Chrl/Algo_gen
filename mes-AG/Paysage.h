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
using centreCercles= vector<pair<double,double>>;



class Paysage {  
    int nbCercles;  
    public : 
        Color random_col();
        centreCercles createCenter(int nbCercles);
        vector<double> createRayons(int nbCercles);
        void afficheCerlces(const centreCercles& centres,const vector<double>& rayons, int nbCercles);

};