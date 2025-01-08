#ifndef GUI_H
#define GUI_H

#include "types.h"
#include "jeu.h"
#include "partie.h"
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <time.h>


/* Initialisation et libération des sprites */
void InitialiserSprites(int *spriteBleu, int *spriteOrange, int *spriteCroixOrange, int *spriteCroixBleue);
void LibererSprites(int spriteBleu, int spriteOrange, int spriteCroixOrange, int spriteCroixBleue);

/* Fonctions pour la gestion des boutons */
void AfficherBouton(Bouton bouton);
int ZoneClic(Bouton bouton, int x, int y);

/* Fonctions pour la gestion de la grille */
void DessinerGrilleAvecPions(int tailleGrille, Pion *pions, int nbPions, int *casesCondamnees,
                             int *couleursCroix, int joueurActuel, int spriteBleu,
                             int spriteOrange, int spriteCroixOrange, int spriteCroixBleue);

/* Fonctions pour l'affichage des textes */
void AfficherTexteTailleGrille();
void AfficherTexteModeDeJeu();

#endif /* GUI_H */
