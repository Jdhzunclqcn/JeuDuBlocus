#ifndef TYPES_H
#define TYPES_H

/* Définition des structures */
typedef struct {
    int x, y;     /* Position du pion en coordonnées de la grille */
    int couleur;  /* 0 pour rouge, 1 pour bleu */
} Pion;

typedef struct {
    int x, y;
    int largeur, hauteur;
    char texte[30];
    int estClique; /* Indique si le bouton a été cliqué */
} Bouton;

#endif /* TYPES_H */