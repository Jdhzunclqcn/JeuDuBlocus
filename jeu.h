#ifndef JEU_H
#define JEU_H

#include "types.h"
#include "gui.h"
#include "partie.h"
#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <time.h>

#define TAILLE_FENETRE 700

/* Déclarations des fonctions */

/* Détecte si un clic a été fait dans une case et retourne ses coordonnées */
int DetecterCaseCliquee(int tailleGrille, int *x_case, int *y_case, int x, int y);

/* Vérifie si une case est adjacente à une autre */
int EstAdjacente(int x1, int y1, int x2, int y2);

/* Vérifie si une case est libre (aucun pion ou obstacle) */
int EstLibre(int x, int y, Pion *pions, int nbPions);

/* Vérifie si une case est occupée par un pion */
int EstOccupee(int x, int y, Pion *pions, int nbPions);

/* Vérifie si un joueur peut se déplacer depuis sa position */
int PeutSeDeplacer(int x, int y, int tailleGrille, Pion *pions, int nbPions, int *casesCondamnees);

/* Fonction principale du jeu */
void Jouer(int spriteBleu, int spriteOrange, int spriteCroixOrange, int spriteCroixBleue);

#endif /* JEU_H */
