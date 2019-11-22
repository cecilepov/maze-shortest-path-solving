

------------- INSTRUCTIONS DE COMPILATION/EXECUTION --------------


$ g++ -ansi -pedantic -Wall -Wextra -std=c++1y -c labyrinthe.cc

$ g++ labyrinthe.o

$ ./a




---------------------------NIVEAU 7 ------------------------------

******************************************************************

>>> ÉNONCÉ :

L'image E donnée en page 7 est la donnée en entrée du projet.
On veut résoudre le problème du labyrinthe et obtenir le chemin suivant :

1 1 1 1
      1
  1 1 1
  1
  1
  1 1 1 1


******************************************************************

>>> SOLUTION PROPOSÉE

L'image d'entrée est :

2 1 1 1 0
0 0 0 1 0
0 1 1 1 0
0 1 0 1 0
1 1 0 0 0
0 1 1 1 3


• ETAPE 1
On mémorise dans deux objets de la classe point2d :
    - les coordonnées du point de départ du labyrinthe (valeur 2 dans l'image d'entrée);
    - les coordonnées du point d'arrivée du labyrinthe (valeur 3 dans l'image d'entrée).

-----------------------

• ETAPE 2
On crée une image partielle à partir de l'image d'entrée (on ne 'garde' que les points ayant une valeur différente de 0 )

Dans cette image partielle, qui ne doit contenir que des 1, un unique 2 (départ) et un unique 3 (arrivée), on remplace :
   - le 3 (case d'arrivée) et les 1 par des 0.
   - le 2 (case d'entrée) par un 1.


On obtient alors l'image partielle présentée dans l'énoncé du niveau 6 :

1 0 0 0
      0
  0 0 0
  0   0
0 0
  0 0 0 0

-----------------------

• ETAPE 3
L'image partielle créée à l'étape 2 est l'input de l'algorithme de calcul de la carte de distance.
On peut lui "appliquer" cet algorithme grâce aux niveaux 5 et 6 du projet.
On applique donc cet algorithme à l'image partielle et on stocke le résultat dans une variable distance_map.


-----------------------

• ETAPE 4
A partir de l'image distance_map précédemment obtenue, on cherche le chemin qui permet d'aller
du point de départ au point d'arrivée (leurs positions ont été enregistrées à l'étape(1)).
En d'autres termes, quels points font partie de ce chemin ?

On obtient l'image suivante : (sont à 1 tous les points faisant partie de ce chemin).

1 1 1 1
      1
  1 1 1
  1   6
101
  1 1 1 1

> On appelera cette image img_step4

  -----------------------

• ETAPE 5

On veut faire afficher clairement ce chemin. Pour cela, il faut "supprimer" les valeurs 10 et 6 qu'il y avait sur l'image précédente.
On passe par une image2d, qui au départ vaut :

0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0

On copie la valeur img_step4 dans cette image2d si img_step4[i] = 1.
On a alors :

1 1 1 1 0
0 0 0 1 0
0 1 1 1 0
0 1 0 0 0
0 1 0 0 0
0 1 1 1 1

On appellera cette image solution_img2d.

On transforme solution_img2d en image partielle, et on obtient le résultat final suivant :

1 1 1 1
      1
  1 1 1
  1
  1
  1 1 1 1

-> Ce qui correspondait bien à la solution recherchée.
