#include "Paysage.h"


Color Paysage::random_col()
{
	return Color(
		static_cast<int>((int)((double)rand()/RAND_MAX * 255)),
		static_cast<int>((int)((double)rand()/RAND_MAX * 255)),
		static_cast<int>((int)((double)rand()/RAND_MAX * 255)));
}


centre Paysage::circleCenter(int nbCercles)
{
centre result;
for (int i=0; i<nbCercles; i++){
    double x = (double)rand()/RAND_MAX*200-100;
    double y = (double)rand()/RAND_MAX*200-100;
    result.push_back({x,y});
}
return result;
}


centre Paysage::squareCenter(int nbCarres)
{
centre result;
for (int i=0; i<nbCarres; i++){
    double x = (double)rand()/RAND_MAX*200-100;
    double y = (double)rand()/RAND_MAX*200-100;
    result.push_back({x,y});
}
return result;
}


centre Paysage::triCenter(int nbTri)
{
centre result;
for (int i=0; i<nbTri; i++){
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


vector<double> Paysage::createCote(int nbCarres)
{
vector<double> result;
for (int j=0; j<nbCarres; j++){
    result.push_back((double)rand()/RAND_MAX*5);
}
return result;
}


vector<double> Paysage::createCoteTri(int nbTri)
{
vector<double> result;
for (int j=0; j<nbTri; j++){
    result.push_back((double)rand()/RAND_MAX*5);
}
return result;
}


void Paysage::affiche(const centre& centresCircles,const vector<double>& rayons,int nbCercles,const centre& centresSquares, const vector<double>&coteSquares, int nbCarres, const centre& centreTri, const vector<double>&coteTri, int nbTri)
{
	Color col=random_col();
    RenderWindow window(VideoMode(Vector2u(600, 600)), "Cercles avec SFML");
    window.setFramerateLimit(60);

    vector<CircleShape> circles;

    for (int k = 0; k < nbCercles; k++) {

        CircleShape circle(rayons[k]*10);
        circle.setFillColor(col);
        //circle.setFillColor(random_col());
        circle.setOrigin(Vector2f((float)rayons[k], (float)rayons[k]));

        float px = static_cast<float>((centresCircles[k].first  + 100.0) * 3.0);
        float py = static_cast<float>((centresCircles[k].second + 100.0) * 3.0);
        circle.setPosition(Vector2f(px, py));

        circles.push_back(circle);
    }

    vector<RectangleShape> squares;

    for (int j = 0; j < nbCarres; j++) {

        RectangleShape square(Vector2f(coteSquares[j]*11, coteSquares[j]*11));
        square.setFillColor(col);
        square.setPosition(Vector2f((centresSquares[j].first+100)*3, (centresSquares[j].second+100)*3));
        float degSquares = ((float)(rand()) / (float)(RAND_MAX)) * 90;
        square.setRotation(degrees(degSquares));
        squares.push_back(square);
    }


	vector<ConvexShape> triangles;	

	for (int i = 0; i < nbTri; i++) {
		
		ConvexShape tri;
		float deg = ((float)(rand()) / RAND_MAX * 120);
		float h = coteTri[i] * sqrt(3) *10;
		tri.setFillColor(col);

		tri.setPointCount(3);
		tri.setPoint(0, Vector2f(0, 0));
		tri.setPoint(1, Vector2f(coteTri[i]*20, 0));
		tri.setPoint(2, Vector2f(coteTri[i]*10, h));
		
		tri.setOrigin(Vector2f(coteTri[i]*15, h ));

		float posx = ((float)centreTri[i].first+100)*3;
		float posy = ((float)centreTri[i].second+100)*3;
		tri.setPosition(Vector2f(posx, posy));
		tri.setRotation(degrees(deg));

		triangles.push_back(tri);
		
	}


    while (window.isOpen()) {
        while (auto ev = window.pollEvent()) {
            if (ev->is<Event::Closed>())
              window.close();
        }

        window.clear(Color::Black);
        for (const auto& circle : circles)
            window.draw(circle);
        for (const auto& square : squares)
            window.draw(square);
		for (const auto& tri : triangles )
			window.draw(tri);
        window.display();
    }
}