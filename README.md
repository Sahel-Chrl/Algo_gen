## 🇫🇷 french Présentation
# Algo-gen 💻🧬
Dans ce projet, je cherche à mettre en évidence le lien étroit entre les algorithmes génétiques et la biologie évolutive. 
Pour cela, je crée des AG (codes qui utilisent le principe évolutif afin de résoudre divers problèmes d'approximation), puis j'étudie les mécanismes de l'algorithme en essayant de les relier à des principes évolutifs connus. 
Je pense que cette approche de l'évolution peut amener une autre façon, peut-être plus terre à terre, d'aborder des questions fondamentales de la biologie. 
  
Pour vous donner un exemple simple, nous pouvons observer plus en détail mon premier AG (en Processing, resp en C++) : [AG-polynomes](mes-AG/Polynomes/Polynomes.pde) // [AG-polynomes](mes-AG/Polynomes/AG-polynomes.cpp)   
L'objectif de cet AG est plutôt simple : se rapprocher de points avec des polynômes. En voici une explication grossière :
- Nous plaçons des points aléatoirement répartis dans une fenêtre de l'ordinateur. 
- Nous créons un certain nombre de polynômes de degré fixe qui représenteront des individus dans une population. 
- Nous calculons la distance verticale de ces polynômes aux points, créant ainsi le score des polynômes (l'objectif étant de se rapprocher des points). 
- À partir d'une population et du score des individus, nous donnons naissance à une nouvelle, en copiant un principe évolutif simple : les plus forts feront plus d'enfants. 
- Lors de la création d'un enfant, nous ajoutons des mutations en modifiant « aléatoirement » les coefficients du polynôme.
- Nous répétons le processus et observons alors le rapprochement des polynômes vers les points. 
  
Cet AG consiste donc à chercher le meilleur polynôme d'un degré fixé pour approcher des points. Ce problème est bien sûr entièrement résolu mathématiquement, mais notre objectif ici n'est pas de trouver le meilleur polynôme, mais bien de modéliser un schéma évolutif.

À partir de cet algorithme pourtant simple, on peut observer des mécanismes biologiques déjà compliqués, notamment autour de la **shifting balance theory** : 
Les maximums locaux dans lesquels peut se bloquer une population (un meilleur score local dans lequel on reste bloqué car, pour en échapper, il faut passer par des scores bien moins bons) : en biologie évolutive, on parle souvent de vallée adaptative ; notre population est sur un pic adaptatif local. Pour atteindre un pic plus élevé, elle doit parfois passer par une zone de fitness plus faible et descendre dans une vallée afin de remonter. 
Plus une population est petite, plus la **dérive génétique** est fréquente, et donc le passage d'une vallée adaptative est plus simple du fait des effets stochastiques plus forts dans les petites populations. 
La vitesse d'évolution d'une population en fonction de sa taille : on pourrait parler de **rythme évolutif** ou de vitesse d'adaptation ; plus la population est grande, plus elle trouvera un maximum local rapidement, mais il aura tendance à être moins bon que celui d'une population plus petite. 

→ Si vous souhaitez tester mes AG, je vous conseille d'utiliser Processing, simple à installer et plus interactif.  
→ Pour mieux comprendre ce qu'est un AG : [comprendre_creer_un_AG](comprendre_creer_un_AG/comprendre-genetic-AG.txt)  



## 🇬🇧 Presentation
# Algo-gen 💻🧬
In this project, I aim to highlight the close connection between genetic algorithms and evolutionary biology.  
To do this, I create GAs (programs that use evolutionary principles to solve various approximation problems), then I study the mechanisms of the algorithm while trying to relate them to known evolutionary principles.  
I believe that this approach to evolution can offer another way, perhaps a more concrete one, to address fundamental questions in biology.  
  
To give you a simple example, we can take a closer look at my first GA (in Processing, then in C++): [AG-polynomes](mes-AG/Polynomes/Polynomes.pde) // [AG-polynomes](mes-AG/Polynomes/AG-polynomes.cpp). 
The goal of this GA is fairly simple: to get as close as possible to points using polynomials. Here is a rough explanation:
- We place points randomly distributed within a window on the computer screen.  
- We create a certain number of fixed-degree polynomials that will represent individuals in a population.
- We calculate the vertical distance between these polynomials and the points, thus creating the score of each polynomial (the goal being to get as close as possible to the points).
- From one population and the scores of its individuals, we produce a new one by copying a simple evolutionary principle: the fittest individuals will have more offspring.
- When creating an offspring, we add mutations by “randomly” modifying the coefficients of the polynomial.
- We repeat the process and then observe the polynomials moving closer and closer to the points.

This GA therefore consists of searching for the best polynomial of a fixed degree to approximate a set of points. Of course, this problem has already been fully solved mathematically, but our goal here is not to find the best polynomial. Rather, it is to model an evolutionary process.

From this algorithm, simple as it may seem, we can already observe complex biological mechanisms, particularly in relation to **shifting balance theory**:
Local maxima in which a population can become trapped (a local best score in which it remains stuck because escaping it would require going through much worse scores): in evolutionary biology, this is often described as an adaptive valley; our population is sitting on a local adaptive peak. To reach a higher peak, it may sometimes have to pass through a region of lower fitness and descend into a valley before climbing back up.
The smaller a population is, the more frequent **genetic drift** becomes, and therefore crossing an adaptive valley becomes easier because stochastic effects are stronger in small populations.
As for the speed of evolution of a population as a function of its size, one could speak of an **evolutionary rate** or speed of adaptation: the larger the population, the faster it will find a local maximum, but that maximum will tend to be less optimal than the one a smaller population might eventually reach.

→ If you would like to test my GAs, I recommend using Processing, which is easy to install and more interactive.  
→ To better understand what a GA is: [comprendre_creer_un_AG](comprendre_creer_un_AG/comprendre-genetic-AG.txt)
