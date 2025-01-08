#include "partie.h"
#include "jeu.h"
#include "gui.h"
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <time.h>

/* Fonction pour simuler le deuxième joueur */
void SimulerDeuxiemeJoueur(int tailleGrille, Pion *pions, int *casesCondamnees, int *couleursCroix, int joueurActuel) {
    int x_case, y_case;
    /*int taille_case = 500 / tailleGrille;*/
    int dx,dy,nx,ny;

    /* Trouver une case adjacente libre pour déplacer le pion */
    int mouvementValide = 0;
    for (dx = -1; dx <= 1; dx++) {
        for ( dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            nx = pions[joueurActuel].x + dx;
            ny = pions[joueurActuel].y + dy;
            if (nx >= 0 && nx < tailleGrille && ny >= 0 && ny < tailleGrille &&
                !EstOccupee(nx, ny, pions, 2) && !casesCondamnees[ny * tailleGrille + nx]) {
                pions[joueurActuel].x = nx;
                pions[joueurActuel].y = ny;
                mouvementValide = 1;
                break; /* Sortir de la boucle si un mouvement valide est trouvé */
            }
        }
        if (mouvementValide) break;
    }

    /* Trouver une case libre pour placer une croix */
    do {
        x_case = rand() % tailleGrille;
        y_case = rand() % tailleGrille;
    } while (!EstLibre(x_case, y_case, pions, 2) || casesCondamnees[y_case * tailleGrille + x_case]);

    casesCondamnees[y_case * tailleGrille + x_case] = 1;
    couleursCroix[y_case * tailleGrille + x_case] = joueurActuel; /* Mettre à jour la couleur de la croix */
}

/* Fonction pour afficher le texte du gagnant */
void AfficherGagnant(int couleurGagnant, Bouton boutonTerminer, Bouton boutonNouvellePartie,
                      int *tailleGrille, int *nbJoueurs, int *boutonJouerVisible, int *grilleAffichee, int *joueurActuel,
                      int *phaseDeplacement, int *phasePlacement, Pion *pions, int *casesCondamnees, int *couleursCroix, int *redessiner) {
    int terminer = 0;
    int x,y;
    EffacerEcran(CouleurParComposante(255, 255, 255));
    ChoisirCouleurDessin(CouleurParComposante(0, 0, 0)); /* Noir pour le texte */
    if (couleurGagnant == 0) {
        EcrireTexte(170, 270, "Le joueur orange a gagne !", 2);
    } else {
        EcrireTexte(170, 270, "Le joueur bleu a gagne !", 2);
    }

    /* Afficher les boutons */
    AfficherBouton(boutonTerminer);
    AfficherBouton(boutonNouvellePartie);

    /* Attendre un clic de souris */
    
    while (!terminer) {
        if (SourisCliquee()) {
            SourisPosition();
            x = _X, y = _Y;

            if (ZoneClic(boutonTerminer, x, y)) {
                FermerGraphique();
                exit(0); /* Terminer le programme */
            }
            if (ZoneClic(boutonNouvellePartie, x, y)) {
                /* Réinitialiser le jeu */
                ReinitialiserPartie(tailleGrille, nbJoueurs, boutonJouerVisible, grilleAffichee, joueurActuel,
                                    phaseDeplacement, phasePlacement, pions, casesCondamnees, couleursCroix);
                *redessiner = 1; /* Forcer le redessin de l'écran */
                terminer = 1; /* Sortir de la boucle */
            }
        }
    }
}

/* Fonction pour réinitialiser la partie */
void ReinitialiserPartie(int *tailleGrille, int *nbJoueurs, int *boutonJouerVisible, int *grilleAffichee, int *joueurActuel,
                         int *phaseDeplacement, int *phasePlacement, Pion *pions, int *casesCondamnees, int *couleursCroix) {
    int i;
    *tailleGrille = 0;
    *nbJoueurs = 0;
    *boutonJouerVisible = 0;
    *grilleAffichee = 0;
    *joueurActuel = 0;
    *phaseDeplacement = 0;
    *phasePlacement = 1;
    pions[0].x = -1;
    pions[0].y = -1;
    pions[0].couleur = 0;
    pions[1].x = -1;
    pions[1].y = -1;
    pions[1].couleur = 1;

    for (i = 0; i < 100; i++) {
        casesCondamnees[i] = 0;
        couleursCroix[i] = 0;
    }
}