#include "Individu.h"

Individu::Individu(int nbChromosomes)
{
    int nbCarres, nbCercles;
nbCarres = (int)(randfloat() *nbChromosomes);
nbCercles = nbChromosomes-nbCarres;
for(int i=0;i<nbCarres; i++){
    carresIndiv.push_back(Carre());
}
for(int j=0;j<nbCercles; j++){
    cerclesIndiv.push_back(Cercle());
}
}


void Individu::affiche(Individu individu, Paysage paysage)
{
    RenderWindow window(VideoMode(Vector2u(600, 600)), "Cercles avec SFML");
    window.setFramerateLimit(60);

    Texture texture(Vector2u{600, 600});

    bool disp=true;
    while (window.isOpen()) {
        while (auto ev = window.pollEvent()) {
            if (ev->is<Event::Closed>())
              window.close();
        }

        Color red(255,0,0,120);
        Color blue(0,0,255,120);
        window.clear(Color::Black);
        for (auto& cercle : paysage.cercles){
            if(disp) cercle.print();
              window.draw(cercle.draw(red));
        }
         if (disp) cout<<"--"<<endl;
        for (auto& carre : paysage.carres){
            if(disp) carre.print();
            window.draw(carre.draw(red));
        }
        for (auto& cercle : cerclesIndiv){
            if(disp) cercle.print();
              window.draw(cercle.draw(blue));
        }
         if (disp) cout<<"--"<<endl;
        for (auto& carre : carresIndiv){
            if(disp) carre.print();
            window.draw(carre.draw(blue));
        }

        if (disp) cout<<endl;
        disp=false;
        window.display();

        texture.update(window);   // copie le contenu de la fenêtre
        screenshot = texture.copyToImage();   // on remplit screenshot
    }
}


float Individu::score(Individu individu, int pas)
{
    int score,mauvais=0,bien=0;
    const Image& img = individu.getScreenshot();
    Vector2u size = img.getSize();

    unsigned int largeur  = size.x; //unsigner pour pas negatif
    unsigned int hauteur = size.y;
    for (int i=0; i<largeur; i=i+pas){
        for(int j=0; j<hauteur; j=j+pas){
            Color c = screenshot.getPixel(Vector2u(i,j));

            if (c != Color::Magenta) // intersections violettes donc on teste comme ça.
                bien = bien+1;
            else if (c != Color::Red)
                mauvais = mauvais+1;
            else if (c != Color::Blue)
                mauvais = mauvais+1;
            else;
        }
    }
    score=bien/mauvais;
    return score;
}
