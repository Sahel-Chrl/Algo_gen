#include <iostream>
#include <random>
#include <vector>
#include <utility>
using namespace std;


float hasard() {
    return (float)rand();
} // fonction nombre aleatoire pour mes coefs


vector<std::pair<double, double>> couple(
    int n
){
    vector<std::pair<double, double>> result;
    result.reserve(n); //on a cree "l'emplacement" pour nos vecteur qu'on va ensuite generer

    //maintenant le generateur
    for (int i=0; i<n; i++){
        double x = hasard();
        double y = hasard();
        result.emplace_back(x, y); //on range le couple cree
    }
    return result;
}


struct coefs {
    float a,b,c;
} // je cree mes trois coefs pour la parabole

coefs parabole() {
    return{1f,2f,3f};
}



int main(){
    int n;
    cout << "Combien de point voulez vous ?"<<endl;
    cin>> n; 

    //appel d'une liste de couple
    auto points = couple(n);
    for (const auto& [x, y] : points){
        cout<< "("<<x<<","<<y<<")"<<endl<<endl;
    }

    return 0;
}
