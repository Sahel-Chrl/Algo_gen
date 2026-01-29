#include <iostream>
#include <random>
#include <vector>
#include <array>
#include <utility>
#include <cmath>
// #include <SFML/Graphics.hpp>  // Nécessaire pour RenderWindow
using namespace std;

/*
notre objectif et de prendre des points au hasard dans R2
et de trouver la parab pour laquelle la distance moyenne (verticale) des
points a la courbe est la plus faible
Ma popuulation d'individus va etre composé de 100 individus () qui s'amelioreront petit a petit
*/

float hasard()
{
	return (float)rand();
} // fonction nombre aleatoire pour mes parab

float hasard1()
{ // float aleatoire -100 100.
	float x;
	x = (float)rand() / RAND_MAX;
	return x;
}

float hasard1Neg()
{ // float aleatoire -100 100.
	float x;
	x = 2 * hasard1() - 1;
	return x;
}

float hasard100Neg()
{ // float aleatoire -100 100.
	float x = hasard1();
	x = 200 * x - 100;
	return x;
}

float racine(float x)
{
	return sqrt(x);
}

typedef vector<pair<float, float>> points; 
typedef array<float, 3> parab;


//fonction qui crée les couples de points
points couple(
	int n)
{
	points result;
	result.reserve(n); // on a cree "l'emplacement" pour nos vecteur qu'on va ensuite generer

	// maintenant le generateur
	for (int i = 0; i < n; i++)
	{
		float x = hasard100Neg();
		float y = hasard100Neg();
		result.emplace_back(x, y); // on range le couple cree
	}
	return result;
}

// on va creer ici notre popuulation de parabs
vector<parab> create_parab(int n)
{
	vector<parab> result;
	result.reserve(n);

	for (int i = 0; i < n; i++)
	{
		float x = hasard100Neg();
		float y = hasard100Neg();
		float z = hasard100Neg();
		result.push_back({x, y, z});
	}
	return result;
}

// fonction qui calcule la valeur en x
float valeur(float x, parab p)
{
	float y;
	y = p[0] * x * x + p[1] * x + p[2];
	return y;
} 


//fonction distance verticale
float distance(float abcisse, float ordonnee, parab parab)
{
	float y, d;
	y = valeur(abcisse, parab);
	d = abs(y - ordonnee);
	return d;
} 

//fonction distance moyenne
float distancemoy(parab c, points p)
{
	float d;
	int n = p.size();
	d = 0;
	for (auto point : p)
	{
		d = d + distance(point.first, point.second, c);
	}
	d = d / n;
	return d;
}

// fonction qui prends les scores des parabs et les transforme en probas
vector<float> score2proba(vector<float> scores)
{ 
	vector<float> probas;
	float somme = 0;
	for (auto score : scores) //plus le score est grand moins il aura de chance d'être pris (on veut la distance min)
	{
		float inverse = 1 / score;
		probas.push_back(inverse);
		somme += inverse;
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

//on fait juste la somme des probas pour les 
vector<float> probas2cumul(vector<float> probas)
{
	vector<float> cumul;
	cumul.push_back(0);
	for (int i = 0; i < probas.size(); i++)
	{
		cumul.push_back(probas[i] + cumul[i]);
	}
	return cumul;
}

//fonction qui prend au hasard un nombre entre 0 et 1 et revoie la position de ce nombre dans cumul (renvoi quel individu c'est)
int echantillon(vector<float> cumul)
{
	float r = hasard1();
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


//fonction qui crée un descendant en fonction d'un parent choisi, c'est surement ici qu'on peut encore ameliorer le code
parab descendant(parab mere, float variance) 
{
	parab enfant;
	for (int i = 0; i < mere.size(); i++)
	{
		enfant[i] = mere[i] + variance; //enfant + mutation
	}
	return enfant;
} // je pourrais changer cette fonction pour moins changer le x carre que la constante ? 

//fonction qui prend les scores d'une population et donne la distance minimale parmis ces scores 
float minVec(vector<float> scores){
	float min=scores[0];
	for (int i=0; i<scores.size(); i++){
		if (scores[i]<min){
			min=scores[i];
		}
	}
	return min;
}


//fonction qui va calculer le score moyen pour ensuie avoir une meilleur estimation de la variance
float scoreMoyen (vector<float> scores){
    float moy;
    moy = 0;
    for (int i=0; i<scores.size(); i++){
        moy = moy + scores[i];
    }
    moy=moy/scores.size();
    return moy;
}

//fonction qui passe de la moyenne a la variance la "mieux"
//si un individu a un meilleur score que la moyenne on lui octroie une petite variance, et inversement
float moy2variance (float moy, vector<float> scores, int numero) {
    float variance;
    float pourcent=moy/100; //on calcule 1 pourcent de la moyenne pour avoir une variance approprié au score moyen des individus
    variance = (scores[numero]/moy) *pourcent; // je pondere la variance a la distance au score moyen
    variance = variance * hasard1Neg();
    return variance;
}


int affiche()
{
	/*sf::RenderWindow window(sf::VideoMode(800, 600), "Graph of f(x)");

	// Créer un tableau de points
	sf::VertexArray points(sf::LinesStrip);

	// Remplir les points avec les valeurs de la fonction
	for (float x = -400; x < 400; x++) {
		float y = f(x * 0.01) * 100;  // Transformation pour adapter à la fenêtre
		points.append(sf::Vertex(sf::Vector2f(x + 400, 300 - y), sf::Color::Red));  // Déplacement des points
	}

	// Boucle principale
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		window.draw(points);  // Dessiner la courbe
		window.display();
	}

	return 0;*/

	// truc de chatgpt mais ça sert a rien de juste le copier donc j'attends de bien comprendre
	return 0;
}

int main()
{
	srand(time(NULL));
	int n, m;
	cout << "Combien de point voulez vous ?" << endl;
	cin >> n;
	

	// appel d'une liste de couple
	auto points = couple(n);
	if (n < 5)
	{
		cout << "Voici les points pris" << endl;
		for (const auto point : points)
		{
			cout << "(" << point.first << "," << point.second << ")" << endl
				 << endl;
		}
	}
	else
	{
		cout << "Beaucoup de points donc je ne les affiches pas." << endl
			 << endl;
	}

	cout << "Combien de paraboles ?" << endl;
	cin >> m;

	// appel d'une liste de paraboles pour la population
	auto popu = create_parab(m);

	
	vector<float> scores;
	for (auto parab : popu)
	{
		scores.push_back(distancemoy(parab, points));
	}
	vector<float> probas = score2proba(scores);

	// afficher les popu
	int i = 0;
	for (auto parab : popu)
	{
		cout << "Triplet: (" << parab[0] << "," << parab[1] << "," << parab[2] << ")" << endl;
		cout << "Distance moyenne : " << scores[i] << endl;
		cout << "proba de reproduction :" << probas[i] << endl
			 << endl;
		i++;
	}

	// on va tester l'echantillonage
	/*int nb_echant;
		cout<<"combien d'echantillons ?"<<endl;
		cin >> nb_echant;
		vector<float> cumul;
		cumul=probas2cumul(probas);
		for (int i=0; i<nb_echant; i++){
			cout << echantillon(cumul) <<" ";
		}
		cout<<endl;
		return 0;*/

	int generations;
	cout << "combien de generations veux tu ?" << endl;
	cin >> generations;
    cout << endl <<endl;


	//boucle principale du programme qui utilise les fonctions pour ameliorer la population
	for (int i = 0; i < generations; i++)
	{
		vector<parab> newPop;
		vector<float> scores;
		for (auto parab : popu) // on remplit notre tableau de score pour une population
		{
			scores.push_back(distancemoy(parab, points));
		}
		vector<float> probas = score2proba(scores);
		vector<float> cumul = probas2cumul(probas); //on a transforme nos scores en probas et nos probas en cumul
        float moyenne = scoreMoyen(scores);
		for(int j=0; j<popu.size(); j++){ //on cree une nouvelle population du même nombre d'individu que la precedente
				int indiv=echantillon(cumul);
				float variance;
                variance = moy2variance(moyenne, scores, j);
				parab enfant=descendant(popu[indiv],variance);
				newPop.push_back(enfant);
		}
		popu=newPop;
		cout<<minVec(scores)<<endl;
		
	}
	return 0;
}

//plus on diminue la variance, plus la population s'ameliore lentement mais le passage d'une bonne generation a une mauvaise se fait rare.
//en prenant peu de points 1 seul par exemple, on se rends encore plus compte de l'efficacité du programme