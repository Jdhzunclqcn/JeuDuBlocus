#include "jeu.h"
#include "gui.h"
#include "partie.h"
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <time.h>


/* Fonction pour détecter la case cliquée */
int DetecterCaseCliquee(int tailleGrille, int *x_case, int *y_case, int x, int y) {
    int taille_case = 500 / tailleGrille;
    if (x >= 20 && x <= 520 && y >= 20 && y <= 520) {
        *x_case = (x - 20) / taille_case;
        *y_case = (y - 20) / taille_case;
        return 1; /* Clic dans une case valide */
    }
    return 0;
}

/* Fonction pour vérifier si une case est adjacente */
int EstAdjacente(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1;
}


/* Fonction pour vérifier si une case est libre */
int EstLibre(int x, int y, Pion *pions, int nbPions) {
    int i;
    for (i = 0; i < nbPions; i++) {
        if (pions[i].x == x && pions[i].y == y) return 0;
    }
    return 1;
}

/* Fonction pour vérifier si une case est occupée par un pion */
int EstOccupee(int x, int y, Pion *pions, int nbPions) {
    int i;
    for (i = 0; i < nbPions; i++) {
        if (pions[i].x == x && pions[i].y == y) return 1;
    }
    return 0;
}

/* Fonction pour vérifier si un joueur peut se déplacer */
int PeutSeDeplacer(int x, int y, int tailleGrille, Pion *pions, int nbPions, int *casesCondamnees) {
    int dx,dy,nx,ny;
    for ( dx = -1; dx <= 1; dx++) {
        for (dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            nx = x + dx;
            ny = y + dy;
            if (nx >= 0 && nx < tailleGrille && ny >= 0 && ny < tailleGrille &&
                !EstOccupee(nx, ny, pions, nbPions) && !casesCondamnees[ny * tailleGrille + nx]) {
                return 1;
            }
        }
    }
    return 0;
}

/* Fonction principale du jeu */
void Jouer(int spriteBleu, int spriteOrange, int spriteCroixOrange, int spriteCroixBleue) {
    Bouton boutonsTailleGrille[] = {
        {80, 70, 100, 70, "3x3", 0},
        {300, 70, 100, 70, "4x4", 0},
        {550, 70, 100, 70, "5x5", 0},
        {80, 180, 100, 70, "6x6", 0},
        {300, 180, 100, 70, "7x7", 0},
        {550, 180, 100, 70, "8x8", 0},
        {300, 280, 100, 70, "9x9", 0}
    };
    Bouton boutonJ1 = {100, 460, 150, 70, "1 Joueur", 0};
    Bouton boutonJ2 = {400, 460, 150, 70, "2 Joueurs", 0};
    Bouton boutonJouer = {270, 570, 150, 70, "JOUER", 0};
    Bouton boutonTerminer = {280, 450, 125, 70, "Terminer", 0};
    Bouton boutonNouvellePartie = {260, 350, 170, 70, "Nouvelle Partie", 0};

    int tailleGrille = 0, nbJoueurs = 0;
    int boutonJouerVisible = 0, grilleAffichee = 0, joueurActuel = 0, phaseDeplacement = 0, phasePlacement = 1;
    int redessiner = 1; /* Indicateur pour savoir si on doit redessiner l'écran */

    Pion pions[2] = {{-1, -1, 0}, {-1, -1, 1}}; 
    int casesCondamnees[100] = {0};
    int couleursCroix[100] = {0}; /* Tableau pour stocker la couleur des croix */
    int x,y,i,j;
    int x_case, y_case;
    int continuer = 1;

    srand(time(NULL)); /* Initialiser le générateur de nombres aléatoires */

    /* Ne pas effacer l'écran trop souvent */
    EffacerEcran(CouleurParComposante(255, 255, 255));

    while (continuer) {
        if (SourisCliquee()) {
            SourisPosition();
            x = _X, y = _Y;

            if (!grilleAffichee) {
                for (i = 0; i < 7; i++) {
                    if (ZoneClic(boutonsTailleGrille[i], x, y)) {
                        /* Réinitialiser les autres boutons de sélection de la taille de la grille */
                        for (j = 0; j < 7; j++) {
                            boutonsTailleGrille[j].estClique = 0;
                        }
                        tailleGrille = i + 3;
                        boutonsTailleGrille[i].estClique = 1;
                        redessiner = 1; /* Forcer le redessin de l'écran */
                    }
                }
                if (ZoneClic(boutonJ1, x, y)) {
                    nbJoueurs = 1;
                    boutonJ1.estClique = 1;
                    boutonJ2.estClique = 0;
                    redessiner = 1; 
                } else if (ZoneClic(boutonJ2, x, y)) {
                    nbJoueurs = 2;
                    boutonJ2.estClique = 1;
                    boutonJ1.estClique = 0;
                    redessiner = 1; 
                }
                if (tailleGrille && nbJoueurs && !boutonJouerVisible) {
                    boutonJouerVisible = 1;
                    redessiner = 1; 
                }
                if (boutonJouerVisible && ZoneClic(boutonJouer, x, y)) {
                    grilleAffichee = 1;
                    redessiner = 1; 
                }
            } else {
                
                if (DetecterCaseCliquee(tailleGrille, &x_case, &y_case, x, y)) {
                    if (phasePlacement) {
                        if (EstLibre(x_case, y_case, pions, 2)) {
                            pions[joueurActuel].x = x_case;
                            pions[joueurActuel].y = y_case;
                            joueurActuel = 1 - joueurActuel;
                            if (pions[0].x != -1 && pions[1].x != -1) {
                                phasePlacement = 0; 
                            }
                            redessiner = 1; /* Force a redessiner la grille */
                        }
                    } else if (!phaseDeplacement) {
                        if (EstAdjacente(pions[joueurActuel].x, pions[joueurActuel].y, x_case, y_case) &&
                            !EstOccupee(x_case, y_case, pions, 2) && !casesCondamnees[y_case * tailleGrille + x_case]) {
                            pions[joueurActuel].x = x_case;
                            pions[joueurActuel].y = y_case;
                            phaseDeplacement = 1;
                            redessiner = 1; 
                        }
                    } else if (EstLibre(x_case, y_case, pions, 2) && !casesCondamnees[y_case * tailleGrille + x_case]) {
                        casesCondamnees[y_case * tailleGrille + x_case] = 1;
                        couleursCroix[y_case * tailleGrille + x_case] = joueurActuel; /* Mettre à jour la couleur de la croix */
                        joueurActuel = 1 - joueurActuel;
                        phaseDeplacement = 0;
                        redessiner = 1; /* Forcer le redessin de la grille */

                        /* Vérifie si le joueur actuel peut encore se déplacer */
                        if (!PeutSeDeplacer(pions[joueurActuel].x, pions[joueurActuel].y, tailleGrille, pions, 2, casesCondamnees)) {
                            AfficherGagnant(1 - joueurActuel, boutonTerminer, boutonNouvellePartie,
                                             &tailleGrille, &nbJoueurs, &boutonJouerVisible, &grilleAffichee, &joueurActuel,
                                             &phaseDeplacement, &phasePlacement, pions, casesCondamnees, couleursCroix, &redessiner); /* Afficher le gagnant */
                        }

                        /* Simule le deuxième joueur si c'est une partie à un seul joueur */
                        if (nbJoueurs == 1 && joueurActuel == 1) {
                            SimulerDeuxiemeJoueur(tailleGrille, pions, casesCondamnees, couleursCroix, joueurActuel);
                            joueurActuel = 0; /* Retourner au joueur humain */
                            redessiner = 1; /* Forcer le redessin de la grille */

                            /* Vérifier si le joueur actuel peut encore se déplacer après le mouvement simulé */
                            if (!PeutSeDeplacer(pions[joueurActuel].x, pions[joueurActuel].y, tailleGrille, pions, 2, casesCondamnees)) {
                                AfficherGagnant(1 - joueurActuel, boutonTerminer, boutonNouvellePartie,
                                                 &tailleGrille, &nbJoueurs, &boutonJouerVisible, &grilleAffichee, &joueurActuel,
                                                 &phaseDeplacement, &phasePlacement, pions, casesCondamnees, couleursCroix, &redessiner); /* Afficher le gagnant */
                            }
                        }
                    }
                }
            }
        }
        if (redessiner) {
            if (!grilleAffichee) {
                EffacerEcran(CouleurParComposante(255, 255, 255));
                AfficherTexteTailleGrille(); /* Afficher le texte "Taille de la grille" */
                for ( i = 0; i < 7; i++) {
                    AfficherBouton(boutonsTailleGrille[i]);
                }
                AfficherTexteModeDeJeu(); /* Afficher le texte "Mode de jeu" */
                AfficherBouton(boutonJ1);
                AfficherBouton(boutonJ2);
                if (boutonJouerVisible) AfficherBouton(boutonJouer);
            } else {
                EffacerEcran(CouleurParComposante(255, 255, 255)); /* Effacer l'écran avant de redessiner la grille */
                DessinerGrilleAvecPions(tailleGrille, pions, 2, casesCondamnees, couleursCroix, joueurActuel,
                                        spriteBleu, spriteOrange, spriteCroixOrange, spriteCroixBleue);
            }
            redessiner = 0; /* Réinitialiser l'indicateur de redessin */
        }
    }
}


