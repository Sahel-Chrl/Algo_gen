import javax.swing.JOptionPane;
class CoordColor
{
  int r;
  int g;
  int b;

  CoordColor(color c) {
    r = int(red(c));
    g = int(green(c));
    b = int(blue(c));
  }
};



class Individu {
  int nbChromosomes;
  boolean clignote = true;

  Cercle[] cerclesIndiv;
  Carre[] carresIndiv;

  PImage screenshot;

  Individu(int nbChrom) {
    nbChromosomes = nbChrom;

    int nbCarres = int((float)random(1) * nbChromosomes);
    int nbCercles = nbChromosomes - nbCarres;

    carresIndiv = new Carre[nbCarres];
    cerclesIndiv = new Cercle[nbCercles];

    for (int i = 0; i < nbCarres; i++) {
      carresIndiv[i] = new Carre();
    }

    for (int j = 0; j < nbCercles; j++) {
      cerclesIndiv[j] = new Cercle();
    }
  }

  void affiche(Paysage paysage) {

    background(0);

    color rouge = color(255, 0, 0, 150);
    color bleu  = color(0, 0, 255, 130);

    for (int i = 0; i < paysage.cercles.length; i++) {
      paysage.cercles[i].drawShape(rouge);
    }

    for (int i = 0; i < paysage.carres.length; i++) {
      paysage.carres[i].drawShape(rouge);
    }

    for (int i = 0; i < cerclesIndiv.length; i++) {
      cerclesIndiv[i].drawShape(bleu);
    }

    for (int i = 0; i < carresIndiv.length; i++) {
      carresIndiv[i].drawShape(bleu);
    }

    screenshot = get();
  }

  float score(int pas) {
    int mauvais = 0;
    int bien = 0;

    screenshot.loadPixels();

    for (int i = 0; i < screenshot.width; i += pas) {
      for (int j = 0; j < screenshot.height; j += pas) {
        color pixel = screenshot.pixels[j * screenshot.width + i];
        CoordColor col = new CoordColor(pixel);

        if (col.r != 0 && col.b != 0) {
          bien++;
        } /*else if (col.r != 0 || col.b != 0) {
          mauvais++;
        }*/
        else if ( col.r !=0 && col.b ==0) mauvais++;
        else if ( col.r ==0 && col.b!=0) mauvais++;
      }
    }

    return bien - mauvais;
  }

  Individu descendant() {
    Individu bebe = new Individu(0);
    bebe.nbChromosomes = nbChromosomes;

    float mutation = 3;
    int grosseMutation = int(random(25));

    bebe.cerclesIndiv = new Cercle[cerclesIndiv.length];
    bebe.carresIndiv = new Carre[carresIndiv.length];

    for (int i = 0; i < cerclesIndiv.length; i++) {
      if (grosseMutation==int(random(10))) {
        int grosseMutation2=grosseMutation*10;
        Cercle cercle = new Cercle();
        cercle.x = cerclesIndiv[i].x + random(-grosseMutation2, grosseMutation2);
        cercle.y = cerclesIndiv[i].y + random(-grosseMutation2, grosseMutation2);
        cercle.rayon = cerclesIndiv[i].rayon + random(-(grosseMutation2 / 4), grosseMutation2/4);
        bebe.cerclesIndiv[i] = cercle;
        if ( cercle.x > 800 || cercle.y > 800 || cercle.x<0 || cercle.y<0 ) {
          cercle.x = random(800);
          cercle.y = random(800);
        }
      } else {
        Cercle cercle = new Cercle();
        cercle.x = cerclesIndiv[i].x + random(-mutation, mutation);
        cercle.y = cerclesIndiv[i].y + random(-mutation, mutation);
        cercle.rayon = cerclesIndiv[i].rayon + random(-(mutation / 4), mutation/4);
        bebe.cerclesIndiv[i] = cercle;
      }
    }

    for (int j = 0; j < carresIndiv.length; j++) {
      if (grosseMutation==int(random(10))) {
        int grosseMutation3=grosseMutation*10;
        Carre carre = new Carre();
        carre.x = carresIndiv[j].x + random(-grosseMutation3, grosseMutation3);
        carre.y = carresIndiv[j].y + random(-grosseMutation3, grosseMutation3);
        carre.cote = carresIndiv[j].cote + random(-grosseMutation3, grosseMutation3);
        carre.rotation = carresIndiv[j].rotation + random(-(PI / 15), PI/15);
        bebe.carresIndiv[j] = carre;
        if ( carre.x > 800 || carre.y > 800 || carre.x<0 || carre.y<0 ) {
          carre.x = random(800);
          carre.y = random(800);
        }
      } else {
        Carre carre = new Carre();
        carre.x = carresIndiv[j].x + random(-mutation, mutation);
        carre.y = carresIndiv[j].y + random(-mutation, mutation);
        carre.cote = carresIndiv[j].cote + random(-mutation, mutation);
        carre.rotation = carresIndiv[j].rotation + random(-(PI / 50), PI/50);
        bebe.carresIndiv[j] = carre;
      }
    }

    return bebe;
  }
}
