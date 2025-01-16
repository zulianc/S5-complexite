Instructions :  
   
1 - Compléter le code d'avl.cpp pour avoir une implémentation
d'un arbre de type AVL.  
  
2 - Faire des tests d'insertion, de suppression et de recherche (penser à faire une fonction d’affichage).
Faire en sorte d’avoir toutes les possibilités dans vos tests.  
  
3 – Considérer le fichier "avl_bench.cpp". Il génère des ensembles de benchmarking avec des tailles d’arbre différentes :
de 2^5 éléments dans l’arbre à 2^25 éléments. Pour chaque taille, il donne 3 fichiers :
Values, Search et Delete, contenant respectivement les valeurs à insérer dans l’arbre,
les valeurs à rechercher, et celles à supprimer. Ajouter dans ce fichier (avl.cpp) les codes nécessaire pour lire
les fichiers de benchmark et effectuer les opérations correspondantes.  
  
4 – Ajouter du code pour chronométrer les opérations. Réaliser des courbes comparatives
des temps d’exécutions des différentes opération en fonction de la taille de l’arbre.
Retrouvons-nous bien les complexité logarithmiques promises ?  


Pour build : `xmake`  
Pour run : `xmake run`  