## 🇫🇷 french Presentation
# Algo-gen 💻🧬
Ce projet vise à explorer les liens entre la biologie évolutive et les algorithmes génétiques (AG, inspirés du principe d’évolution par sélection naturelle). Pour cela, je programme de tels algorithmes, pour essayer ensuite de relier les dynamiques simulées à des principes évolutifs connus. Cette approche me permet d’aborder la biologie évolutive sous un angle théorique, pour mieux en saisir les fondements, et peut-être identifier des questions de recherche pertinentes.  
  
Nous pouvons par exemple observer plus en détail mon premier AG : « AG-polynomes », codé [ici](mes-AG/Polynomes/AG-polynomes.pde)  en Processing et [ici](mes-AG/Polynomes/AG-polynomes.cpp) en C++. 
 Son objectif est simple : optimiser des polynômes pour les rapprocher de points fixes imposés, comme une « population de polynômes » s'adapterait à son environnement.  
  
En voici une explication :  
•	Nous commençons par placer des points aléatoirement dans une fenêtre du plan ; ces points représentent l'environnement auquel les polynômes devront s’adapter.  
•	Nous créons ensuite des polynômes (de degré fixé par l’utilisateur) dont les coefficients sont tirés au hasard dans un intervalle restreint. Les polynômes représent des individus, et leur nombre (choisi par l’utilisateur) correspond à la taille de la population.
•	Pour calculer la fitness (ou valeur sélective) des polynômes, nous sommons simplement les distances verticales de ces polynômes aux points.  
•	À partir d'une population et du score des individus, nous générons une nouvelle génération, en simulant un principe évolutif essentiel : les plus adaptés tendent à avoir une descendance plus nombreuse ; c’est l’analogue de la sélection naturelle.  
•	Pour ce faire, nous tirons la nouvelle génération en assignant aux parents des probabilités correspondant à leur fitness. Ainsi, nous laissons aussi une certaine place au hasard. Plus la population est petite, plus la distribution de la génération n+1 pourra s’éloigner de l’attendu : c’est l’analogue de la dérive génétique.  
•	Lors de la création d'un descendant, nous ajoutons des modifications aléatoires des coefficients du polynôme : c’est l’analogue de la mutation.  
•	Nous répétons le processus et observons, à travers les générations, le rapprochement des polynômes vers les points.  
  
Notons que ce problème d’optimisation a déjà résolu par ailleurs, mais notre objectif ici n'est pas de trouver le meilleur polynôme ; il s’agit plutôt de mieux appréhender un schéma évolutif darwinien.  
  
À partir de cet algorithme pourtant simple, on peut observer des mécanismes biologiques déjà complexes, notamment autour de la « shifting balance theory » : la population de polynômes peut rester bloquée autour d’un maximum local, car pour s’en échapper, il faudrait passer par des scores bien moins bons. De même, en biologie évolutive, on parle souvent du « paysage de fitness » composé de collines (des maxima locaux) et de vallées (correspondant à des génotypes de moindre fitness). De façon très intéressante, la dérive, en ajoutant des fluctuations aléatoires des fréquences des génotypes, peut permettre le passage vers un meilleur maximum local, c’est-à-dire une meilleure exploration évolutive du paysage. Ce phénomène est contrôlé par la taille de la population : plus elle est grande, plus elle trouvera un maximum local rapidement, mais moins elle pourra s’en éloigner pour en trouver un meilleur.  
  
→ Si vous souhaitez tester mes AG, je vous conseille d'utiliser Processing, simple à installer et plus interactif.  
→ Pour plus de détails sur les AG : [detail_AG](comprendre_creer_un_AG/comprendre-genetic-AG.txt).  
→ Un AG un petit peu plus élaboré, pour un problème plus difficile (adapter des formes à un paysage 2d) : [Paysage](mes-AG/Paysage/paysage_processing/paysage.pde)  




## 🇬🇧 English Presentation  
# Algo-gen 💻🧬  
  
This project aims to explore the links between evolutionary biology and genetic algorithms (GAs, inspired by the principle of evolution through natural selection). To do this, I program such algorithms and then try to relate the simulated dynamics to known evolutionary principles. This approach allows me to study evolutionary biology from a theoretical perspective, in order to better understand its foundations and perhaps identify relevant research questions.  
  
For example, we can take a closer look at my first GA: “GA-polynomials,” coded here in Processing and here in C++. Its objective is simple: to optimize polynomials so that they fit a set of fixed points, much like a “population of polynomials” adapting to its environment.  

Here is an explanation:  
• We begin by placing points randomly in a window of the plane; these points represent the environment to which the polynomials must adapt.  
• We then create polynomials (with a degree chosen by the user) whose coefficients are randomly selected within a restricted interval. The polynomials represent individuals, and their number (also chosen by the user) corresponds to the population size.  
• To calculate the fitness (or selective value) of the polynomials, we simply sum the vertical distances between these polynomials and the points.  
• From a population and the individuals’ scores, we generate a new generation by simulating an essential evolutionary principle: the fittest individuals tend to have more offspring; this is the analogue of natural selection.  
• To do this, we sample the new generation by assigning parents probabilities proportional to their fitness. In this way, we also leave some room for chance. The smaller the population, the more the distribution of generation n+1 may deviate from what is expected: this is the analogue of genetic drift.  
• When creating an offspring, we add random modifications to the polynomial coefficients: this is the analogue of mutation.  
• We repeat the process and observe, across generations, how the polynomials move closer to the points.  
  
It should be noted that this optimization problem has already been solved elsewhere, but our objective here is not to find the best polynomial; rather, it is to better understand a Darwinian evolutionary framework.  
  
From this simple algorithm, it is already possible to observe complex biological mechanisms, particularly those related to the “shifting balance theory”: the population of polynomials can remain trapped around a local maximum, because escaping it would require passing through much lower scores. Similarly, in evolutionary biology, people often speak of a “fitness landscape” made up of hills (local maxima) and valleys (corresponding to genotypes with lower fitness). Very interestingly, drift, by introducing random fluctuations in genotype frequencies, can allow the population to move toward a better local maximum, that is, toward a better evolutionary exploration of the landscape. This phenomenon is controlled by population size: the larger the population, the faster it will find a local maximum, but the less likely it will be to move away from it in search of a better one.  
  
→ If you would like to test my GAs, I recommend using Processing, which is easy to install and more interactive.   
→ For more details on GAs: [details_AG](comprendre_creer_un_AG/comprendre-genetic-AG.txt)   
→ A slightly more elaborate GA for a more difficult problem (adapting shapes to a 2D landscape): [Landscape](mes-AG/Paysage/paysage_processing/paysage.pde)  
