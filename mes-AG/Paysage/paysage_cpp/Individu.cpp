#include "Individu.h"

Individu::Individu(int nbChrom)
{
    nbChromosomes=nbChrom;
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


void Individu::affiche(Paysage paysage)
{
    cout<<"affichage paysage individiu"<<endl;
    RenderWindow window(VideoMode(Vector2u(600, 600)), "Cercles avec SFML");
    window.setFramerateLimit(60);

    Texture texture(Vector2u{600, 600});

    bool firstLoop=true;
    while (window.isOpen()) {
        while (auto ev = window.pollEvent()) {
            if (ev->is<Event::Closed>())
              window.close();
        }

        Color red(255,0,0,150);
        Color blue(0,0,255,130);
        window.clear(Color::Black);
        for (auto& cercle : paysage.cercles){
            //if(firstLoop) cercle.print();
              window.draw(cercle.draw(red));
        }
         if (firstLoop) cout<<"--"<<endl;
        for (auto& carre : paysage.carres){
            //if(firstLoop) carre.print();
            window.draw(carre.draw(red));
        }
        for (auto& cercle : cerclesIndiv){
            //if(firstLoop) cercle.print();
              window.draw(cercle.draw(blue));
        }
         if (firstLoop) cout<<"--"<<endl;
        for (auto& carre : carresIndiv){
            //if(firstLoop) carre.print();
            window.draw(carre.draw(blue));
        }

        // if (firstLoop) cout<<endl;
        firstLoop=false;
        //window.display();

        texture.update(window);   // copie le contenu de la fenêtre
        screenshot = texture.copyToImage();   // on remplit screenshot
        if(clignote) {
            //sleep(0.1);
            break;
        }
        else window.display();
    }
    cout<<"fin affichage"<<endl;
}


float Individu::score(int pas)
{
    int score,mauvais=0,bien=0;
    Vector2u size = screenshot.getSize();

    unsigned int largeur  = size.x; //unsigner pour pas negatif
    unsigned int hauteur = size.y;
    for (int i=0; i<largeur; i=i+pas){
        for(int j=0; j<hauteur; j=j+pas){
            Color pixel = screenshot.getPixel(Vector2u(i,j));
            Color col(pixel);

            if (col.r!=0 && col.b!=0 ) // intersections violettes donc on teste comme ça.
                bien++;
                else if ((col.r!=0) || (col.b != 0))
                mauvais++;
        }
    }
    score=bien-mauvais;
    return score;
}

coordColor::coordColor(uint32_t c)
{
        r=(uint8_t)((c >> 16) & 0xFF);
        g=(uint8_t)((c >> 8) & 0xFF);
        b=(uint8_t)(c & 0xFF);
}

Individu * Individu::descendant(){
    Individu* bebe=new Individu(nbChromosomes);
    float amplitude=4;
    for (int i=0; i<cerclesIndiv.size(); i++){
        Cercle cercle;
        cercle.x= cerclesIndiv[i].x + rand()/RAND_MAX*amplitude;
        cercle.y= cerclesIndiv[i].y + rand()/RAND_MAX*amplitude;
        cercle.rayon= cerclesIndiv[i].rayon + rand()/RAND_MAX*amplitude/2;
        bebe->cerclesIndiv.push_back(cercle);
    }
    for (int j=0; j<carresIndiv.size(); j++){
        Carre carre;
		carre.x = carresIndiv[j].x + rand()/RAND_MAX*amplitude;
		carre.y = carresIndiv[j].y + rand()/RAND_MAX*amplitude;
		carre.cote = carresIndiv[j].cote + rand()/RAND_MAX*amplitude;
		carre.rotation = carresIndiv[j].rotation + rand()/RAND_MAX*3.14/10;
        bebe->carresIndiv.push_back(carre);
    }
	return bebe;
}
