import javax.swing.JOptionPane;


int cinInt(String message) {
  String s = JOptionPane.showInputDialog(message);
  return int(s);
}

Paysage paysage;
Population pop;
Individu[] individus;

int pas;
int nbIndividus;
int nbChromosomes;
int nbGenerations;
int numGeneration=0;




void setup() {
  size(800, 800);
  frameRate(120);
  background(0);

  pas = cinInt("Quel pas entre les pixels ?");
  nbIndividus = cinInt("Combien d'individus dans une population ?");
  nbChromosomes = cinInt("Combien de chromosomes (cercles/carres) par individu ?");
  nbGenerations = cinInt("combien de generations veux tu ?");


  paysage = new Paysage(15, 15);
  individus = new Individu[nbIndividus];



  for ( int i=0; i<nbIndividus; i++) {
    Individu individu = new Individu(nbChromosomes);
    individus[i] = individu;
    individu.affiche(paysage);
  }
  pop = new Population(individus, pas);

}



void draw() {
  if ( numGeneration<nbGenerations ) {
    println("POPULATION :" + numGeneration );
    println("   -Score moyen population " + pop.scoreMoyen());
    println("   -Meilleur score " + pop.bestScore());
    individus[pop.WhosBest()].affiche(paysage); // affiche meilleur individu
    //delay(1);
    numGeneration++;
    pop.nextGeneration(paysage);
  }
  else noLoop();
}
