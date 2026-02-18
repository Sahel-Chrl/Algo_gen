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
        centre carreCenter(int nbCarres);
        vector<double> createCote(int nbCarres);
        void afficheCerlces(const centre& centres,const vector<double>& rayons, int nbCercles);
        void afficheCarres(const centre& centres, const vector<double>&cote, int nbCarres);

};