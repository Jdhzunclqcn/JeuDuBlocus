#ifndef PARTIE_H
#define PARTIE_H

#include "types.h"
#include "jeu.h"
#include "gui.h"
#include <graph.h>

void SimulerDeuxiemeJoueur(int tailleGrille, Pion *pions, int *casesCondamnees, int *couleursCroix, int joueurActuel);
void AfficherGagnant(int couleurGagnant, Bouton boutonTerminer, Bouton boutonNouvellePartie,
                      int *tailleGrille, int *nbJoueurs, int *boutonJouerVisible, int *grilleAffichee, int *joueurActuel,
                      int *phaseDeplacement, int *phasePlacement, Pion *pions, int *casesCondamnees, int *couleursCroix, int *redessiner);
void ReinitialiserPartie(int *tailleGrille, int *nbJoueurs, int *boutonJouerVisible, int *grilleAffichee, int *joueurActuel,
                         int *phaseDeplacement, int *phasePlacement, Pion *pions, int *casesCondamnees, int *couleursCroix);

#endif /* PARTIE_H */
