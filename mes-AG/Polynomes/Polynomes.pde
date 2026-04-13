import javax.swing.JOptionPane;
import controlP5.*;

//il faut aussi ouvrir classe_polynomes.pde et Point.pde


ControlP5 cp5;

float hasard()
{
  return (float)random(1000);
} // fonction nombre aleatoire pour mes parab

float hasard1()
{
  return (float)random(1);
}

float hasard1Neg()
{
  return (float)random(-1, 1);
}

color random_col()
{
  return color(
    hasard1() * 255,
    hasard1() * 255,
    hasard1() * 255);
}

int lireInt(String message) {
  String s = JOptionPane.showInputDialog(message);
  return int(s);
}


float racine(float x)
{
  return sqrt(x);
}



// fonction qui crée les couples de points
Point[] couple(int n)
{
  Point[] points = new Point[n];

  for (int i = 0; i < n; i++)
  {
    float x = hasard1Neg() * 100;
    float y = hasard1Neg() * 100;
    points[i]= new Point(x, y); // on range le couple cree
  }
  return points;
}

// on va creer ici notre popuulation de parabs
Parabole[] create_parab(int n, int degre, float[] grandeurs)
{
  Parabole[] result = new Parabole[n];

  for (int i = 0; i < n; i++) // je parcours les courbes
  {
    //Parabole par = new Parabole(degre, grandeurs);
    //result.push(par);
    result[i] = new Parabole(degre, grandeurs);
  }
  return result;
}

// fonction qui calcule la valeur en x
float valeur(float x, Parabole p)
{
  float y = 0;
  // y = p[0] * x * x + p[1] * x + p[2];
  for (int i = 0; i < p.coefs.length; i++)
  {
    y = y * x + p.coefs[i];
  }
  return y;
}

// fonction distance verticale
float distance(float abcisse, float ordonnee, Parabole parab)
{
  float y, d;
  y = valeur(abcisse, parab);
  d = abs(y - ordonnee);
  return d;
}

// fonction distance moyenne
float distancemoy(Parabole c, ArrayList<Point> Point)
{
  float d;
  int n = Point.size();
  d = 0;
  for (var point : Point)
  {
    d = d + distance(point.x, point.y, c);
  }
  d = d / n;
  return d;
}

// fonction qui prends les scores des parabs et les transforme en probas
float[] score2proba(float[] scores)
{
  float[] probas = new float[scores.length];
  float somme = 0;

  for ( int i=0; i<scores.length; i++) { // plus le score est grand moins il aura de chance d'être pris (on veut la distance min)
    float inverse = 1/scores[i];
    probas[i]=inverse;
    somme+=inverse;
  }

  if (somme == 0)
  {
    println ( "attention somme nulle" );
    return probas;
  }

  if (somme==0) {
    println("attention somme nulle division par 0 dans score2probas");
  }
  // on normalise notre tableaux de probas pour que la somme fasse 1
  for (int j = 0; j < probas.length; j++)
  {
    probas[j] = probas[j] / somme;
  }

  return probas;
}

// on fait juste la somme des probas pour les
float[] probas2cumul(float[] probas)
{
  float[] cumul = new float[probas.length+1];
  cumul[0]=0;
  for (int i = 0; i < probas.length; i++)
  {
    cumul[i+1]=probas[i]+cumul[i];
  }
  return cumul;
}

// fonction qui prend au hasard un nombre entre 0 et 1 et revoie la position de ce nombre dans cumul (renvoi quel individu c'est)
int echantillon(float[] cumul)
{
  float r = hasard1();
  int debut = 0, fin = cumul.length - 1;
  while (fin - debut > 1)
  {
    int milieu = (fin + debut) / 2;
    if (cumul[milieu] > r)
    {
      fin = milieu;
    } else
    {
      debut = milieu;
    }
  }
  return debut;
}

// fonction qui crée un descendant en fonction d'un parent choisi, c'est surement ici qu'on peut encore ameliorer le code
Parabole descendant(Parabole mere, float[] grandeurs, int degre)
{
  float[] enfantCoefs = new float[degre];
  float newVar = variance;
  color newCol = mere.couleur;
  if (hasard1() < .02)
  {
    newVar = 40 * variance; // grosse mutation
    newCol = random_col();
  }

  int minimum;
  minimum = degre;
  if ( mere.coefs.length <= degre ) minimum = mere.coefs.length;

  for (int i = 0; i < minimum; i++)
  {

    float hasard = hasard1Neg();

    enfantCoefs[degre - i-1] = mere.coefs[mere.coefs.length-i-1] + newVar * hasard * grandeurs[i]; // enfant + mutation
  }

  for ( int j = minimum; j < degre; j++ ) {
    float hasard = hasard1Neg();
    enfantCoefs[degre - j - 1]=hasard*grandeurs[j];
  }

  Parabole enfant = new Parabole(enfantCoefs, newCol);
  return enfant;
} // je pourrais changer cette fonction pour moins changer le x carre que la  ante ?

// fonction qui prend les scores d'une population et donne la distance minimale parmis ces scores
float minVec(float[] scores)
{
  if (scores.length == 0)
  {
    println( "scores vide, erreur" );
    return 0.;
  }
  float min = scores[0];
  for (int i = 0; i < scores.length; i++)
  {
    if (scores[i] < min)
    {
      min = scores[i];
    }
  }
  return min;
}

// fonction qui va calculer le score moyen pour ensuie avoir une meilleur estimation de la variance
float scoreMoyen(float[] scores)
{
  float moy;
  moy = 0;
  for (int i = 0; i < scores.length; i++)
  {
    moy = moy + scores[i];
  }
  moy = moy / scores.length;
  return moy;
}




int nb_checkpoint = 1000;

int nb_points, nb_individus, deg, degMax, generations;
int idGeneration = 0;
int numPopu = 0;

ArrayList<Point> points;
float[] grandeurs;
Parabole[] popu;
float variance = 0.05;

int pointCount = 200;
float radius = 3;

void setup() {
  size(800, 800);
  println("setup debut");
  randomSeed((int)millis());

  cp5 = new ControlP5(this);
  cp5.addSlider("variance")
    .setPosition(575, 90)
    .setSize(170, 20)
    .setRange(0,1 )
    .setValue(.05)
    .setDecimalPrecision(3); 


  nb_points = 1;
  Point[] pts = couple(nb_points);
  points = new ArrayList<Point>();
  for (Point p : pts) {
    points.add(p);
  }


  //deg = lireInt("combien de coefs veux-tu pour les polynomes ?");
  //if (deg < 1) deg = 1;
  deg=5;
  degMax=15;
  cp5.addSlider("deg")
    .setPosition(575, 60)
    .setSize(170, 20)
    .setRange(1, degMax)
    .setValue(deg)
    .setDecimalPrecision(0); // pas de decimales

  grandeurs = new float[degMax];
  float g = 100;
  for (int d = 0; d < degMax; d++)
  {
    grandeurs[d] = g;
    g = g / 100;
  }


  //nb_individus = lireInt("combien de polynomes voulez vous ?");
  nb_individus = 30;
  cp5.addSlider("nb_individus")
    .setPosition(575, 30)
    .setSize(170, 20)
    .setRange(1, 300)
    .setValue(nb_individus)
    .setDecimalPrecision(0); // pas de decimales

  if (nb_individus < 1) nb_individus = 1;
  // appel d'une liste de paraboles pour la population
  popu = create_parab(nb_individus, deg, grandeurs);


  float[] scores = new float[popu.length];
  for ( int i=0; i<popu.length; i++)
  {
    scores[i]= distancemoy(popu[i], points);
  }

  println("setup fin");
}


void dessinerAxes() {
  stroke(150);
  line(0, 400, 800, 400);
  line(400, 0, 400, 800);
}

int pointClique() {
  for (int i=0; i< points.size(); i++) {
    Point p = points.get(i);

    float px = ((p.x +100)*4);
    float py = ((p.y +100)*4);

    if (dist(mouseX, mouseY, px, py) <= radius*3) {
      return i;
    }
  }
  return -1;
}

void mousePressed() {
   if (cp5.isMouseOver()) {
    return;
  }
  int i = pointClique();

  if (i != -1) {
    points.remove(i);   // enlève le point cliqué
  }
  else {
    float x = mouseX / 4.0 - 100;
    float y = mouseY / 4.0 - 100;
    points.add(new Point(x, y));   // ajoute un point
  }
}


void dessinerPoints() {
  fill(255, 0, 0);
  noStroke();

  for (Point point : points) {
    float px = (point.x +100)*4;
    float py = (point.y +100)*4;
    ellipse(px, py, radius*2, radius*2);
  }
}


void dessinerCourbes() {
  noFill();

  for (Parabole par : popu) {
    stroke(par.couleur);

    beginShape();
    for (int i = 0; i < pointCount; i++) {
      float x = i - 100;
      float y = valeur(x, par);

      float px = (x + 100.5) * 4;
      float py = (y + 100) * 4;

      vertex(px, py);
    }
    endShape();
  }
}


void draw() {
  background(0);
  text("nb_individus = " + nb_individus, 575, 30);
  text("nombre de coefs = " + deg, 575, 60);
  text( points.size() + " points", 575, 130);
  if ( keyPressed && key=='p') {
  points.clear();
  }
  text ( "variance " + variance , 575,90);
  
  dessinerAxes();
  dessinerPoints();


  int distance_Checkpoint = 100;



  Parabole[] newPop = new Parabole[nb_individus];
  float[] scores = new float[popu.length];

  for (int i = 0; i < popu.length; i++) {
    scores[i] = distancemoy(popu[i], points);
  }

  float[] probas = score2proba(scores);
  float[] cumul = probas2cumul(probas);

  for (int j = 0; j < newPop.length; j++) {
    int indiv = echantillon(cumul);

    if (indiv >= popu.length) {
      println("erreur: indiv " + indiv + " dans popu " + popu.length);
      indiv = popu.length - 1;
    }

    Parabole enfant = descendant(popu[indiv], grandeurs, deg);
    newPop[j] = enfant;
  }

  popu = newPop;

  if (idGeneration % distance_Checkpoint == 0) {
    println("Population numero " + numPopu + " : ");
    numPopu=numPopu+distance_Checkpoint;
    println(" meilleur score = " + minVec(scores) + "  " + "score moyen = " +scoreMoyen(scores));
    println("degre choisi " + (deg-1) );
  }

  idGeneration++;

  dessinerCourbes();
}




// plus on diminue la variance, plus la population s'ameliore lentement mais le passage d'une bonne generation a une mauvaise se fait rare.
// en prenant peu de points 1 seul par exemple, on se rends encore plus compte de l'efficacité du programme
