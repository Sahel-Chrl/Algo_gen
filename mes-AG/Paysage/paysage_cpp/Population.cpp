#include "Population.h"



void Population::nextGeneration(){

	vector<Individu*> descendence;
    int nbIndiv=individus.size();
	float moyenne=scoreMoyen();
	int min=minScore();
	vector<int> scoresPop= scoreNegToPos();
	vector<float> proba= score2probas();
	vector<float> cumul= probas2cumul(proba);
	for (int i=0; i<individus.size(); i++){
		int num = numIndiv(cumul);
		Individu* descendenti = individus[i]->descendant();
		descendence.push_back(descendenti);
	}
	for (int j=0; j<individus.size();j++){
		delete individus[j];
		individus[j]=descendence[j];
	}
}

Population::Population(vector<Individu*> indivs, int p){
	pas=p;
	for (int i=0; i<indivs.size(); i++){
		individus.push_back(indivs[i]);
		scores.push_back(indivs[i]->score(pas));
	}

}


float Population::scoreMoyen()
{   int total=0;
    for (auto score : scores){
        total+=score;
    }
    total=total/scores.size();
    return total;
}


int Population::minScore()
{
	float min = scores[0];
	for (int i = 0; i < scores.size(); i++)
	{
		if (scores[i] < min)
		{
			min = scores[i];
		}
	}
	return min;
}


vector<int> Population::scoreNegToPos()
{
	int min= minScore();
	if (min<0){
		for (int i=0; i<scores.size(); i++){
			scores[i]-=min;
		}
	}
	return scores;
}



vector<float> Population::score2probas()
{
	vector<float> probas;
	float somme = 0;
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


vector<float> Population::probas2cumul(vector<float> probas)
{
	vector<float> cumul;
	cumul.push_back(0);
	for (int i = 0; i < probas.size(); i++)
	{
		cumul.push_back(probas[i] + cumul[i]);
	}
	return cumul;
}

// fonction qui prend au hasard un nombre entre 0 et 1 et revoie la position de ce nombre dans cumul (renvoi quel individu c'est)
int Population::numIndiv(vector<float> cumul)
{
	float r = rand()/RAND_MAX;
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

