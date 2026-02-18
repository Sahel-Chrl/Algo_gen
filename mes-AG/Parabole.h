#include <iostream>
#include <random>
#include <vector>
#include <array>
#include <utility>
#include <cmath>
#include <algorithm>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


Color random_col()
{
	return Color(
		static_cast<int>((int)((double)rand()/RAND_MAX) * 255),
		static_cast<int>((int)((double)rand()/RAND_MAX) * 255),
		static_cast<int>((int)((double)rand()/RAND_MAX) * 255));
}

class Parabole
{
public:
	vector<double> coefs;
	Color couleur;

	Parabole(int degre, const vector<double> &grandeurs);
    Parabole(vector<double> &coefficients, Color col);
};