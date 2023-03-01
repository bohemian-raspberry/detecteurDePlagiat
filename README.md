

Projet Programmation en C

ABENSOUR Liam – CREMOUX Mathéo

#VAMOS A PLAGIAT


1. Motivation
detecteurDePlagiat
Le but de ce projet programmation C est de détecter le plagiat entre deux fichiers contenant du code source C. Pour cela, une chaîne de traitement est appliquée, jusqu’à la production finale d’un rapport de similarité entre les deux fichiers.  Ce projet est inspiré de l’article http://hal.archives-ouvertes.fr/hal-01066127 .

2. Notice d’utilisation

-Placez dans le même sous-répertoire le main.c ainsi que deux fichiers en C (fichier1.c fichier2.c) .
-Ouvrez votre terminal 
-Compilez : gcc -g main.c -o ‘nom de l’exécutable’
- Exécuter : ./’nom de l’exécutable’  fichier1.c   fichier2.c
-Observez les résultats : vous aurez dans le même sous-répertoire deux fichiers .pgm filtrage.pgm vous permettra d’observer les similarités après le post filtrage et dice.pgm est une  matrice brut des similarités entre les deux fichiers.
.
3. Nous contacter
matheo.cremoux@dauphine.eu
