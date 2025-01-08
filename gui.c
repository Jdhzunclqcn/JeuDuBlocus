#include "gui.h"
#include "jeu.h"
#include "partie.h"
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <time.h>

/* Fonction pour initialiser les sprites */
void InitialiserSprites(int *spriteBleu, int *spriteOrange, int *spriteCroixOrange, int *spriteCroixBleue) {
    *spriteBleu = ChargerSprite("Pionb_50x50.png"); /* Charger le sprite pour le pion bleu */
    *spriteOrange = ChargerSprite("Pionc_50x50.png"); /* Charger le sprite pour le pion orange */
    *spriteCroixOrange = ChargerSprite("croixo4x4.png"); /* Charger le sprite pour les croix orange */
    *spriteCroixBleue = ChargerSprite("croixb4x4.png"); /* Charger le sprite pour les croix bleues */
    if (*spriteBleu == -1 || *spriteOrange == -1 || *spriteCroixOrange == -1 || *spriteCroixBleue == -1) {
        printf("Erreur de chargement des sprites. Assurez-vous que les fichiers existent et sont accessibles.\n");
        FermerGraphique();
        exit(1);
    }
}

/* Fonction pour libérer les sprites */
void LibererSprites(int spriteBleu, int spriteOrange, int spriteCroixOrange, int spriteCroixBleue) {
    LibererSprite(spriteBleu); /* Libérer le sprite bleu */
    LibererSprite(spriteOrange); /* Libérer le sprite orange */
    LibererSprite(spriteCroixOrange); /* Libérer le sprite croix orange */
    LibererSprite(spriteCroixBleue); /* Libérer le sprite croix bleue */
}

/* Fonction pour afficher un bouton */
void AfficherBouton(Bouton bouton) {
    if (bouton.estClique) {
        ChoisirCouleurDessin(CouleurParComposante(173, 216, 230)); /* Bleu clair */
        RemplirRectangle(bouton.x, bouton.y, bouton.largeur, bouton.hauteur);
    }
    ChoisirCouleurDessin(CouleurParComposante(0, 0, 0)); /* Noir pour le contour et le texte */
    DessinerRectangle(bouton.x, bouton.y, bouton.largeur, bouton.hauteur);
    EcrireTexte(bouton.x + 20, bouton.y + 40, bouton.texte, 1);
}

/* Fonction pour vérifier si un clic touche le bouton */
int ZoneClic(Bouton bouton, int x, int y) {
    return (x >= bouton.x && x <= bouton.x + bouton.largeur &&
            y >= bouton.y && y <= bouton.y + bouton.hauteur);
}

/* Fonction pour dessiner la grille et ses pions */
void DessinerGrilleAvecPions(int tailleGrille, Pion *pions, int nbPions, int *casesCondamnees, int *couleursCroix, int joueurActuel,
                              int spriteBleu, int spriteOrange, int spriteCroixOrange, int spriteCroixBleue) {
    int taille_case = 500 / tailleGrille;
    int i,px,py,cx,cy;

    /* Dessiner la grille */
    DessinerRectangle(20, 20, 500, 500);
    for (i = 1; i < tailleGrille; i++) {
        DessinerSegment(20, 20 + i * taille_case, 520, 20 + i * taille_case); /* Lignes horizontales */
        DessinerSegment(20 + i * taille_case, 20, 20 + i * taille_case, 520); /* Lignes verticales */
    }

    /* Dessiner les pions */
    for (i = 0; i < nbPions; i++) {
        px = 20 + pions[i].x * taille_case + taille_case / 2;
        py = 20 + pions[i].y * taille_case + taille_case / 2;

        if (pions[i].couleur == 0) {
            AfficherSprite(spriteOrange, px - 25, py - 25); /* Afficher le sprite pour le pion orange */
        } else {
            AfficherSprite(spriteBleu, px - 25, py - 25); /* Afficher le sprite pour le pion bleu */
        }
    }

    /* Marquer les cases condamnées */
    for ( i = 0; i < tailleGrille * tailleGrille; i++) {
        if (casesCondamnees[i]) {
            cx = i % tailleGrille;
            cy = i / tailleGrille;
            px = 20 + cx * taille_case + taille_case / 2;
            py = 20 + cy * taille_case + taille_case / 2;

            if (couleursCroix[i] == 0) {
                AfficherSprite(spriteCroixOrange, px - 20, py - 20); /* Afficher le sprite pour la croix orange */
            } else {
                AfficherSprite(spriteCroixBleue, px - 20, py - 20); /* Afficher le sprite pour la croix bleue */
            }
        }
    }
}

/* Fonction pour afficher le texte "Taille de la grille" */
void AfficherTexteTailleGrille() {
    ChoisirCouleurDessin(CouleurParComposante(0, 0, 0)); /* Noir pour le texte */
    EcrireTexte(220, 50, "Taille de la grille", 2);
}

/* Fonction pour afficher le texte "Mode de jeu" */
void AfficherTexteModeDeJeu() {
    ChoisirCouleurDessin(CouleurParComposante(0, 0, 0)); /* Noir pour le texte */
    EcrireTexte(245, 420, "Mode de jeu", 2);
}