#include "Population.h"

/*Population::Population(){
    vector<Individu> population;
    int nbIndiv;
    cout <<"combien d'individus veux tu ?"<<endl;
    cin >> nbIndiv;
    for (int i=0; i<nbIndiv; i++){
        //population.push_back(individu)//probleme je veux faire ma population d'individu ici comment faire ?
    }

}*/

float Population::scoreMoyen(vector<double> scores)
{   int total=0;
    for (auto score : scores){
        total+=score;
    }
    total=total/scores.size();
    return total;
}


double Population::minScore(vector<double> scores)
{
	double min = scores[0];
	for (int i = 0; i < scores.size(); i++)
	{
		if (scores[i] < min)
		{
			min = scores[i];
		}
	}
	return min;
}


vector<double> Population::score2probas(vector<double>scores)
{
	vector<double> probas;
	double somme = 0;
	for (auto score : scores) // plus le score est grand moins il aura de chance d'être pris (on veut la distance min)
	{
		probas.push_back(score);
		somme += score;
	}
	if (somme == 0)
	{
		cout << "attention somme nulle" << endl;
		return probas;
	}


	// on normalise notre tableaux de probas pour que la somme fasse 1
	for (int i = 0; i < probas.size(); i++)
	{
		probas[i] = probas[i] / somme;
	}
	return probas;
}


vector<double> Population::probas2cumul(vector<double> probas)
{
	vector<double> cumul;
	cumul.push_back(0);
	for (int i = 0; i < probas.size(); i++)
	{
		cumul.push_back(probas[i] + cumul[i]);
	}
	return cumul;
}

// fonction qui prend au hasard un nombre entre 0 et 1 et revoie la position de ce nombre dans cumul (renvoi quel individu c'est)
int Population::numIndiv(vector<double> cumul)
{
	double r = rand()/RAND_MAX;
	int debut = 0, fin = cumul.size() - 1;
	while (fin - debut > 1)
	{
		int milieu = (fin + debut) / 2;
		if (cumul[milieu] > r)
		{
			fin = milieu;
		}
		else
		{
			debut = milieu;
		}
	}
	return debut;
}



Individu Population::descendent(Individu individu){
    int mutationCoordonnee, mutationRayon, mutationCote;
    for (int i=0; i<individu.cerclesIndiv.size(); i++){
        Cercle cercle = individu.cerclesIndiv[i];
        cercle.x+=mutationCoordonnee;
        cercle.y+=mutationCoordonnee;
        cercle.rayon+=mutationRayon;
    }
    for (int j=0; j<individu.carresIndiv.size(); j++){
        Carre carre = individu.carresIndiv[j];
    }
}