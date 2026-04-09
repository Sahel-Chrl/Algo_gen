import javax.swing.JOptionPane;
class Population {
  int[] scores;
  int pas;
  Individu[] individus;

  Population(Individu[] indivs, int p) {
    pas = p;
    individus = new Individu[indivs.length];
    scores = new int[indivs.length];

    for (int i = 0; i < indivs.length; i++) {
      if (indivs[i]== null) {
        println("individu " + i + " est null");
      } else if ( indivs[i].screenshot == null) println("screenshot " + i + " null");
      else {
        individus[i] = indivs[i];
        scores[i] = int(indivs[i].score(pas));
      }
    }
  }

  int minScore() {
    int minVal = scores[0];
    for (int i = 0; i < scores.length; i++) {
      if (scores[i] < minVal) {
        minVal = scores[i];
      }
    }
    return minVal;
  }


  int[] scoresNegToPos() {
    int minVal = minScore();

    int[] scoresPos = new int[scores.length];
    for (int i = 0; i < scores.length; i++) {
      scoresPos[i] = scores[i];
    }

    if (minVal < 0) {
      for (int i = 0; i < scoresPos.length; i++) {
        scoresPos[i] -= minVal;
      }
    }

    return scoresPos;
  }

  float bestScore() {
    int[] scoresPos = scoresNegToPos();
    int best = scoresPos[0];
    for ( int i=0; i < scoresPos.length; i++) {
      if ( best < scoresPos[i] ) best=scoresPos[i];
    }
    return best;
  }

  int WhosBest() {
    int num=0;
    int[] scoresPos = scoresNegToPos();
    for ( int i=0; i< scoresPos.length; i++) {
      if ( scoresPos[num]<scoresPos[i] ) num=i;
    }
    return num;
  }


  float scoreMoyen() {
    int total = 0;
    int[] scoresPos = scoresNegToPos();
    for (int i = 0; i < scoresPos.length; i++) {
      total += scoresPos[i];
    }
    return float(total) / scoresPos.length;
  }

  /*float badestScore() {
   int[] scoresPos = scoresNegToPos();
   int bad = scoresPos[0];
   for ( int i=0; i < scoresPos.length; i++) {
   if ( bad>scoresPos[i]) bad=scoresPos[i];
   }
   return bad;
   }*/


  float[] score2probas() {
    int[] scoresPos = scoresNegToPos();
    float[] probas = new float[scoresPos.length];
    float somme = 0;

    for (int i = 0; i < scoresPos.length; i++) {
      probas[i] = scoresPos[i];
      somme += probas[i];
    }

    if (somme == 0) {
      println("attention somme nulle");
      return probas;
    }

    for (int i = 0; i < probas.length; i++) {
      probas[i] = probas[i] / somme;
    }

    return probas;
  }

  float[] probas2cumul(float[] probas) {
    float[] cumul = new float[probas.length + 1];
    cumul[0] = 0;

    for (int i = 0; i < probas.length; i++) {
      cumul[i + 1] = probas[i] + cumul[i];
    }

    return cumul;
  }

  int numIndiv(float[] cumul) {
    float r = random(1);
    int debut = 0;
    int fin = cumul.length - 1;

    while (fin - debut > 1) {
      int milieu = (fin + debut) / 2;
      if (cumul[milieu] > r) {
        fin = milieu;
      } else {
        debut = milieu;
      }
    }

    return debut;
  }

  void nextGeneration(Paysage paysage) {
    Individu[] descendance = new Individu[individus.length];

    //float moyenne = scoreMoyen();
    //int minVal = minScore();
    //int[] scoresPop = scoresNegToPos();
    float[] proba = score2probas();
    float[] cumul = probas2cumul(proba);

    for (int i = 0; i < individus.length; i++) {
      int num = numIndiv(cumul);
      descendance[i] = individus[num].descendant();
    }

    for (int j = 0; j < individus.length; j++) {
      individus[j] = descendance[j];
      individus[j].affiche(paysage);
      scores[j] = int(individus[j].score(pas));
    }
  }
}
