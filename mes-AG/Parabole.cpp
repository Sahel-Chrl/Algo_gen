#include "Parabole.h"


Parabole::Parabole(int degre, const vector<double> &grandeurs)
{
	for (int j = 0; j < degre; j++)
	{
		double x;
		x = (((double)rand()/RAND_MAX)*2-1 )* grandeurs[j];
		coefs.push_back(x);
	}
	couleur = random_col();
}

Parabole::Parabole(vector<double> &coefficients, Color col)
{
	for (auto c : coefficients)
		coefs.push_back(c);
	couleur = col;
}