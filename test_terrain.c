#include "generation_terrains.h"
#include "terrain.h"
#include <stdio.h>

int main(int argc, char **argv) {
  FILE *f;
  Terrain t;
  int x, y;
  erreur_terrain e;

  if (argc < 2) {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }

  f = fopen(argv[1], "r");
  int allOK;
  char nom_fich[100];
  allOK = 0;
  while (allOK == 0) {
    e = lire_terrain(f, &t, &x, &y);
    switch (e) {
      case OK:
        afficher_terrain(&t);
        allOK = 1;
        break; 
      case ERREUR_FICHIER:
        printf("Erreur lors de la lecture du terrain : ERREUR_FICHIER, veuillez entrer un nouveau nom de fichier\n");
        scanf("%s",nom_fich);
        f = fopen(nom_fich, "r");
        break;
      case ERREUR_LECTURE_LARGEUR:
        printf("Erreur lors de la lecture de la largeur : ERREUR_LECTURE_LARGEUR \n");
        allOK = 2;
        break;
      case ERREUR_LECTURE_HAUTEUR:
        printf("Erreur lors de la lecture de la hauteur : ERREUR_LECTURE_HAUTEUR \n");
        allOK = 2;
        break;
      case ERREUR_LARGEUR_INCORRECTE:
        printf("Erreur largeur incorrecte : ERREUR_LARGEUR_INCORRECTE \n");
        allOK = 2;
        break;
      case ERREUR_HAUTEUR_INCORRECTE:
        printf("Erreur hauteur incorrecte : ERREUR_HAUTEUR_INCORRECTE \n");
        allOK = 2;
        break;
      case ERREUR_CARACTERE_INCORRECT:
        printf("Erreur caractère(s) incorrect(s) : ERREUR_CARACTERE_INCORRECT \n");
        allOK = 2;
        break;
      case ERREUR_LIGNE_TROP_LONGUE:
        printf("Erreur ligne(s) trop longue(s) : ERREUR_LIGNE_TROP_LONGUE \n");
        allOK = 2;
        break;
      case ERREUR_LIGNE_TROP_COURTE:
        printf("Erreur ligne(s) trop courte(s) : ERREUR_LIGNE_TROP_COURTE \n");
        allOK = 2;
        break;
      case ERREUR_LIGNES_MANQUANTES:
        printf("Erreur ligne(s) manquante(s) : ERREUR_LIGNES_MANQUANTES \n");
        allOK = 2;
        break;
      case ERREUR_POSITION_ROBOT_MANQUANTE:
        printf("Erreur position du robot manquante : ERREUR_POSITION_ROBOT_MANQUANTE \n");
        allOK = 2;
        break;
    }
  }
  if (allOK == 1) {
    printf("Position initiale du robot : (%d, %d)\n", x, y);
    int myRes = existe_chemin_vers_sortie(&t);
    printf(">>%d\n",myRes);
  } else {
	  printf("Aborting...\n");
  }

  fclose(f);
}
