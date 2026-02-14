#include <iostream>
#include <random>
#include <vector>
#include <array>
#include <utility>
#include <cmath>
#include <algorithm>
#include <SFML/Graphics.hpp>  // Nécessaire pour RenderWindow
using namespace sf;
using namespace std;

/*
notre objectif et de prendre des points au hasard dans R2
et de trouver la parab pour laquelle la distance moyenne (verticale) des
points a la courbe est la plus faible
Ma popuulation d'individus va etre composé de 100 individus () qui s'amelioreront petit a petit
*/

double hasard()
{
	return (double)rand();
} // fonction nombre aleatoire pour mes parab

double hasard1()
{ // double aleatoire -100 100.
	double x;
	x = (double)rand() / RAND_MAX;
	return x;
}

double hasard1Neg()
{ // double aleatoire -100 100.
	double x;
	x = 2 * hasard1() - 1;
	return x;
}

double hasard100Neg()
{ // double aleatoire -100 100.
	double x = hasard1();
	x = 200 * x - 100;
	return x;
}

double racine(double x)
{
	return sqrt(x);
}

typedef vector<pair<double, double>> points; 
typedef vector<double> parab;


//fonction qui crée les couples de points
points couple(
	int n)
{
	points result;
	result.reserve(n); // on a cree "l'emplacement" pour nos vecteur qu'on va ensuite generer

	// maintenant le generateur
	for (int i = 0; i < n; i++)
	{
		double x = hasard100Neg();
		double y = hasard100Neg();
		result.emplace_back(x, y); // on range le couple cree
	}
	return result;
}

// on va creer ici notre popuulation de parabs
vector<parab> create_parab(int n, int degre)
{
	vector<parab> result;

	for (int i = 0; i < n; i++)//je parcours les courbes
	{
        parab par;

		for (int j=0; j<degre; j++){
			double x;
			x=hasard100Neg();
			for ( int k=j+1; k<degre ; k++){
				x=x/100;
			}
			par.push_back(x);
		}
		result.push_back(par);
	}
	return result;
}

// fonction qui calcule la valeur en x
double valeur(double x, const parab& p)
{
	double y=0;
	//y = p[0] * x * x + p[1] * x + p[2];
    for (int i=0; i<p.size(); i++ ){
        y=y*x+p[i];
    }
	return y;
} 


//fonction distance verticale
double distance(double abcisse, double ordonnee, const parab &parab)
{
	double y, d;
	y = valeur(abcisse, parab);
	d = abs(y - ordonnee);
	return d;
} 

//fonction distance moyenne
double distancemoy(const parab& c, points p)
{
	double d;
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
vector<double> score2proba(vector<double> scores)
{ 
	vector<double> probas;
	double somme = 0;
	for (auto score : scores) //plus le score est grand moins il aura de chance d'être pris (on veut la distance min)
	{
		double inverse = 1 / score;
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
vector<double> probas2cumul(vector<double> probas)
{
	vector<double> cumul;
	cumul.push_back(0);
	for (int i = 0; i < probas.size(); i++)
	{
		cumul.push_back(probas[i] + cumul[i]);
	}
	return cumul;
}

//fonction qui prend au hasard un nombre entre 0 et 1 et revoie la position de ce nombre dans cumul (renvoi quel individu c'est)
int echantillon(vector<double> cumul)
{
	double r = hasard1();
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
parab descendant(const parab& mere, double variance) 
{
	parab enfant;
	for (int i = 0; i < mere.size(); i++)
	{	double hasard=hasard1Neg();
		enfant.push_back(mere[i] + variance * hasard * mere[i]); //enfant + mutation
		
	}
	return enfant;
} // je pourrais changer cette fonction pour moins changer le x carre que la constante ? 

//fonction qui prend les scores d'une population et donne la distance minimale parmis ces scores 
double minVec(vector<double> scores){
    if(scores.size()==0){
        cout<<"scores vide, erreur"<<endl;
        return 0.;
    }
	double min=scores[0];
	for (int i=0; i<scores.size(); i++){
		if (scores[i]<min){
			min=scores[i];
		}
	}
	return min;
}


//fonction qui va calculer le score moyen pour ensuie avoir une meilleur estimation de la variance
double scoreMoyen (vector<double> scores){
    double moy;
    moy = 0;
    for (int i=0; i<scores.size(); i++){
        moy = moy + scores[i];
    }
    moy=moy/scores.size();
    return moy;
}



void affiche(const vector<parab> &popu, points& pts){

// Fenêtre SFML 3 : VideoMode prend un Vector2u
    RenderWindow window(
        VideoMode(Vector2u(600, 600)),
        "Courbe avec SFML 3"
    );
    window.setFramerateLimit(60);


   const size_t pointCount = 200;
   vector<VertexArray> curves;
   for(auto par : popu){
   VertexArray curve(PrimitiveType::LineStrip, pointCount);

    for (size_t i = 0; i < pointCount; ++i)
    {
        float x = (float)i-100;
        float y = valeur(x,par);

        curve[i].position = { (x+100)*3, (y+100)*3 };
        curve[i].color = Color::Green;
    }
	curves.push_back(curve);
}
//points
const float radius = 3.f;
vector<CircleShape> dots;
for (auto point : pts)
{
    CircleShape dot(radius);
    dot.setFillColor(Color::Red);
    dot.setOrigin({radius, radius});
    dot.setPosition({((float)point.first+100)*3, ((float)point.second+100)*3});
    dots.push_back(dot);
}

    VertexArray axes(PrimitiveType::Lines, 4);

// Axe X
axes[0].position = {0.f, 300.f};
axes[1].position = {600.f, 300.f};

// Axe Y
axes[2].position = {300.f, 0.f};
axes[3].position = {300.f, 600.f};

for (int i = 0; i < 4; ++i)
    axes[i].color = Color(150, 150, 150);


 while (window.isOpen())
    {
        // SFML 3 : pollEvent() -> std::optional<Event>
        while (auto ev = window.pollEvent())
        {
            // SFML 3 : event est une variante (std::variant-like)
            if (ev->is<Event::Closed>())
                window.close();
        }

window.clear(Color::Black);
window.draw(axes);
for (const auto& p : dots)
    window.draw(p);
for( auto curve : curves ) window.draw(curve);
window.display();
}
}

int main()
{

	int nb_checkpoint=10;
	srand(time(NULL));
	int n, m;
	cout << "Combien de point voulez vous ?" << endl;
	cin >> n;
cout<<"combien de coefs veux tu pour les polynomes ?"<<endl;
int deg;
cin >>deg;
    //int deg=(int)(n/2);
	//if(deg==0) deg=1;
    //cout<<"le degre des polynomes est : "<<deg-1<<endl;
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
	auto popu = create_parab(m,deg);
	if (m<11&deg>1){
		int i=1;
		cout <<"voici un exemple du premier et deuxième coefficient de quelques paraboles:"<<endl;
		for (auto parab : popu){
			cout << " - parabole "<<i<< ": coef 1 = "<<parab[deg-1]<<endl<<"coef 2 = "<<parab[deg-2]<<endl;
			i++;
		}
	}
	

	
	vector<double> scores;
	for (auto parab : popu)
	{
		scores.push_back(distancemoy(parab, points));
	}
	vector<double> probas = score2proba(scores);


	int generations;
	cout << "combien de generations veux tu ?" << endl;
	cin >> generations;
    cout << endl <<endl;

	affiche(popu, points);
	//boucle principale du programme qui utilise les fonctions pour ameliorer la population
	int distance_Checkpoint=(int)(generations/nb_checkpoint);
	for (int i = 0; i < generations; i++)
	{
		vector<parab> newPop;
		vector<double> scores;
		for (auto parab : popu) // on remplit notre tableau de score pour une population
		{
			scores.push_back(distancemoy(parab, points));
		}
		vector<double> probas = score2proba(scores);
		vector<double> cumul = probas2cumul(probas); //on a transforme nos scores en probas et nos probas en cumul
		for(int j=0; j<popu.size(); j++){ //on cree une nouvelle population du même nombre d'individu que la precedente
				int indiv=echantillon(cumul);
				double variance=.1;
                if(indiv>=popu.size()) cout<<"erreur: indiv "<<indiv<<" dans popu "<<popu.size()<<endl;
				parab enfant=descendant(popu[indiv],variance);
				newPop.push_back(enfant);
		}
		popu=newPop;
		if (i%distance_Checkpoint==0){
		cout<<minVec(scores)<<" "<<scoreMoyen(scores)<<endl;
		}
		
	}
	affiche(popu, points);
	return 0;
}

//plus on diminue la variance, plus la population s'ameliore lentement mais le passage d'une bonne generation a une mauvaise se fait rare.
//en prenant peu de points 1 seul par exemple, on se rends encore plus compte de l'efficacité du programme