#include "Paysage.h"


Color Paysage::random_col()
{
	return Color(
		static_cast<int>((int)((double)rand()/RAND_MAX * 255)),
		static_cast<int>((int)((double)rand()/RAND_MAX * 255)),
		static_cast<int>((int)((double)rand()/RAND_MAX * 255)));
}


centreCercles Paysage::createCenter(int nbCercles)
{
centreCercles result;
for (int i=0; i<nbCercles; i++){
    double x = (double)rand()/RAND_MAX*200-100;
    double y = (double)rand()/RAND_MAX*200-100;
    result.push_back({x,y});
}
return result;
}


vector<double> Paysage::createRayons(int nbCercles)
{
vector<double> result;
for (int j=0; j<nbCercles; j++){
    result.push_back((double)rand()/RAND_MAX*5);
}
return result;
}


void Paysage::afficheCerlces(const centreCercles& centres,const vector<double>& rayons,int nbCercles)
{
    RenderWindow window(VideoMode(Vector2u(600, 600)), "Cercles avec SFML");
    window.setFramerateLimit(60);

    vector<CircleShape> circles;

    for (int k = 0; k < nbCercles; k++) {

        CircleShape circle(rayons[k]*10);
        //circle.setFillColor(Color::Red);
        circle.setFillColor(random_col());
        circle.setOrigin(Vector2f((float)rayons[k], (float)rayons[k]));

        float px = static_cast<float>((centres[k].first  + 100.0) * 3.0);
        float py = static_cast<float>((centres[k].second + 100.0) * 3.0);
        circle.setPosition(Vector2f(px, py));

        circles.push_back(circle);
    }

    while (window.isOpen()) {
        while (auto ev = window.pollEvent()) {
            if (ev->is<Event::Closed>())
              window.close();
        }

        window.clear(Color::Black);
        for (const auto& circle : circles)
            window.draw(circle);
        window.display();
    }
}