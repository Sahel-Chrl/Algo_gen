class Parabole
{
  float[] coefs;
  color couleur;

  public Parabole(int degre, float[] grandeurs)
  { 
    coefs = new float[degre];
    for (int j = 0; j < degre; j++)
    {
      float x;
      x = hasard1Neg() * grandeurs[degre-j-1];
      coefs[j] = x;
    }
    couleur = random_col();
  }

  Parabole( float[] coefficients, color col)
  {
    coefs = new float[coefficients.length];
    for (int i=0; i<coefficients.length; i++)
      coefs[i]=coefficients[i];
      
    couleur = col;
  }
};
