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
et de trouver la parabole pour laquelle la distance moyenne (verticale) des
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

// on va creer ici notre popuulation de paraboles
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

float valeur(float x, parab p)
{
	float y;
	y = p[0] * x * x + p[1] * x + p[2];
	return y;
} // fonction qui calcule la valeur en x

float distance(float z, float t, parab p)
{
	float y, d;
	y = valeur(z, p);
	d = abs(y - t);
	return d;
} // on calcule ici la distance verticale du point z,t a la courbe

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
} // on a calculer la distance moyenne

vector<float> score2proba(vector<float> scores)
{ // fonction qui prends les scores des paraboles et les transforme en probas
	vector<float> probas;
	float somme = 0;
	for (auto score : scores)
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

parab descendant(parab mere, float variance)
{
	parab enfant;
	for (int i = 0; i < mere.size(); i++)
	{
		enfant[i] = mere[i] + variance * hasard1Neg();
	}
	return enfant;
}

float minVec(vector<float> vec){
	float min=vec[0];
	for (int i=0; i<vec.size(); i++){
		if (vec[i]<min){
			min=vec[i];
		}
	}
	return min;
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
	cout << "Combien de paraboles ?" << endl;
	cin >> m;

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
		/*cout << "Voici quelques points pris" <<endl;
		for (const auto& [x, y] : points){
		cout<< "("<<x<<","<<y<<")"<<endl<<endl;*/
		cout << "Beaucoup de points donc je ne les affiches pas." << endl
			 << endl;
	}

	// appel d'une liste de popu pour la parabole
	auto popu = create_parab(m);
	vector<float> scores;
	for (auto parabole : popu)
	{
		scores.push_back(distancemoy(parabole, points));
	}
	vector<float> probas = score2proba(scores);

	// afficher les popu
	int i = 0;
	for (auto parabole : popu)
	{
		cout << "Triplet: (" << parabole[0] << "," << parabole[1] << "," << parabole[2] << ")" << endl;
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
	for (int i = 0; i < generations; i++)
	{
		vector<parab> newPop;
		vector<float> scores;
		for (auto parabole : popu)
		{
			scores.push_back(distancemoy(parabole, points));
		}
		vector<float> probas = score2proba(scores);
		vector<float> cumul = probas2cumul(probas);
		for(int j=0; j<popu.size(); j++){
				int indiv=echantillon(cumul);
				float variance=10;
				if(scores[indiv]/100<10){variance=scores[indiv]/100;}
				parab enfant=descendant(popu[indiv],variance);
				newPop.push_back(enfant);
		}
		popu=newPop;
		cout<<minVec(scores)<<endl;
		
	}
	return 0;
}
