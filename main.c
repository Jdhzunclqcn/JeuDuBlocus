#include "gui.h"
#include "jeu.h"
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>



int main() {
    
    int spriteBleu, spriteOrange, spriteCroixOrange, spriteCroixBleue;

    if (InitialiserGraphique() == 0) {
        printf("Erreur d'initialisation graphique.\n");
        return 1;
    }
    CreerFenetre(270, 50, TAILLE_FENETRE, TAILLE_FENETRE);

    InitialiserSprites(&spriteBleu, &spriteOrange, &spriteCroixOrange, &spriteCroixBleue);

    Jouer(spriteBleu, spriteOrange, spriteCroixOrange, spriteCroixBleue);

    LibererSprites(spriteBleu, spriteOrange, spriteCroixOrange, spriteCroixBleue); /* Libérer les sprites avant de fermer le programme */
    FermerGraphique();
    return 0;
}