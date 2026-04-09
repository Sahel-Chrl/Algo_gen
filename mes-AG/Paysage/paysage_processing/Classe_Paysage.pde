color random_col()
{
  return color(
    (int)random(255),
    (int)random(255),
    (int)random(255));
}

import javax.swing.JOptionPane;
float randomCoord() {
  return random(800);
}


class Cercle {
  float x; //coordonnées du centre
  float y;
  float rayon;
  Cercle() {
    x = randomCoord();
    y = randomCoord();
    rayon = random(50);
  }
  void drawShape(color c) {
    fill(c);
    noStroke();
    ellipse(x, y, rayon*2, rayon*2);
  }
};

class Carre {
  float x;
  float y;
  float cote;
  float rotation;
  Carre() {
    x = randomCoord();
    y = randomCoord();
    cote = random(100);
    rotation = random(0,3.14);
  }
  void drawShape(color c) {
    fill(c);
    noStroke();

    pushMatrix();
    translate(x, y);
    rotate(rotation);
    rectMode(CENTER);
    rect(0, 0, cote, cote);
    popMatrix();
  }
};

class Paysage {
  Cercle[] cercles;
  Carre[] carres;
  int step=5;
  Paysage(int nbCircles, int nbSquares){
  cercles = new Cercle[nbCircles];
  carres = new Carre[nbSquares];
  
  for ( int i=0; i<nbCircles; i++) cercles[i] = new Cercle();
  for ( int j=0; j<nbSquares; j++) carres[j] = new Carre();
  }
};
