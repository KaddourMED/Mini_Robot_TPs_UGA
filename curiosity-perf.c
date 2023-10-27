#include "environnement.h"
#include "interprete.h"
#include "programme.h"
#include "generation_terrains.h"

#include <stdio.h>
#include <stdlib.h>

void gestion_erreur_terrain(erreur_terrain e) {
  switch (e) {
  case OK:
    break;
  case ERREUR_FICHIER:
    printf("Erreur lecture du terrain : erreur d'ouverture du fichier\n");
    exit(1);
  case ERREUR_LECTURE_LARGEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la largeur\n");
    exit(1);
  case ERREUR_LECTURE_HAUTEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la hauteur\n");
    exit(1);
  case ERREUR_LARGEUR_INCORRECTE:
    printf("Erreur lecture du terrain : largeur incorrecte\n");
    exit(1);
  case ERREUR_HAUTEUR_INCORRECTE:
    printf("Erreur lecture du terrain : hauteur incorrecte\n");
    exit(1);
  case ERREUR_CARACTERE_INCORRECT:
    printf("Erreur lecture du terrain : caractère incorrect\n");
    exit(1);
  case ERREUR_LIGNE_TROP_LONGUE:
    printf("Erreur lecture du terrain : ligne trop longue\n");
    exit(1);
  case ERREUR_LIGNE_TROP_COURTE:
    printf("Erreur lecture du terrain : ligne trop courte\n");
    exit(1);
  case ERREUR_LIGNES_MANQUANTES:
    printf("Erreur lecture du terrain : lignes manquantes\n");
    exit(1);
  case ERREUR_POSITION_ROBOT_MANQUANTE:
    printf(
        "Erreur lecture du terrain : position initiale du robot manquante\n");
    exit(1);
  }
}

void affichage_position_programme(erreur_programme e) {
  int i;
  printf("Ligne %d, colonne %d :\n", e.num_ligne, e.num_colonne);
  printf("%s\n", e.ligne);
  /* Impression de e.num_colonne-1 espaces */
  for (i = 1; i < e.num_colonne; i++) {
    printf(" ");
  }
  /* Impression d'un curseur de position */
  printf("^\n");
}

void gestion_erreur_programme(erreur_programme e) {
  switch (e.type_err) {
  case OK_PROGRAMME:
    break;
  case ERREUR_FICHIER_PROGRAMME:
    printf("Erreur lecture du programme : erreur d'ouverture du fichier\n");
    exit(2);
  case ERREUR_BLOC_NON_FERME:
    printf("Erreur lecture du programme : bloc non fermé\n");
    exit(2);
  case ERREUR_FERMETURE_BLOC_EXCEDENTAIRE:
    printf("Erreur lecture du programme : fermeture de bloc excédentaire\n");
    affichage_position_programme(e);
    exit(2);
  case ERREUR_COMMANDE_INCORRECTE:
    printf("Erreur lecture du programme : commande incorrecte\n");
    affichage_position_programme(e);
    exit(2);
  }
}

int main(int argc, char **argv) {
  Environnement envt;
  Programme prog;
  erreur_terrain errt;
  erreur_programme errp;
  etat_inter etat;
  resultat_inter res;
  FILE *f_p;
  FILE *f_r;
  FILE *f_tr;
  Terrain T;

  int nb_obs = 0, nb_sortis = 0 , nb_bloques = 0;
  float pas_moyen = 0;

  if (argc < 9) {
      printf("Usage: %s <fichier_programme> <N> <L> <H> <d> <graine> <nb_step_max> <fichier_res>\n", argv[0]);
      return 1;
  }
  

  f_p = fopen(argv[1], "r");
  f_r = fopen(argv[8], "w");

  int pas, n, l, h, graine, nb_step_max;
  float d;

  n = strtol(argv[2], NULL, 10);
  l = strtol(argv[3], NULL, 10);
  h = strtol(argv[4], NULL, 10);
  d = strtof(argv[5], NULL);
  graine = strtol(argv[6], NULL, 10);
  nb_step_max = strtol(argv[7], NULL, 10);
  fprintf(f_r, "%d\n", n);

  // Initialisation de la fonction random
  srand(graine);
  

  /* Ecrire les résultats */
  for(int i = 0; i < n; i++){
    pas = 0;
    generation_aleatoire(&T, l, h, d);
    while(existe_chemin_vers_sortie(&T) != 1){
      generation_aleatoire(&T, l, h, d); }
    f_tr = fopen("terrain_11x9.txt", "w");
    fprintf(f_tr, "%d\n%d\n", l, h);
    ecrire_terrain(f_tr, &T, l/2, h/2);
    fclose(f_tr);


    /* Initialisation de l'environnement : lecture du terrain,
    initialisation de la position du robot */
    
    errt = initialise_environnement(&envt, "terrain_11x9.txt");
    gestion_erreur_terrain(errt);

    /* Lecture du programme */
    errp = lire_programme(&prog, argv[1]);
    gestion_erreur_programme(errp);

    /* Initialisation de l'état */
    init_etat(&etat);
    do {
        res = exec_pas(&prog, &envt, &etat);
        /* Affichage du terrain et du robot */
        afficher_envt(&envt);
        pas++;
    } while (res == OK_ROBOT && pas < nb_step_max);
    printf("Nombre de pas = %d\n\n", pas);
    switch (res) {
        case OK_ROBOT:
        case ARRET_ROBOT:
            fprintf(f_r, "-1\n");
            nb_bloques++;
            break;
        case SORTIE_ROBOT:
            fprintf(f_r, "terrain = %d, pas_executes = %d\n", i + 1, pas);
            nb_sortis++;
            pas_moyen = pas_moyen + pas;
            break;
        case PLOUF_ROBOT:
            fprintf(f_r, "-2\n");
            nb_obs++;
            break;
        case CRASH_ROBOT:
            fprintf(f_r, "-3\n");
            nb_obs++;
            break;
        case ERREUR_PILE_VIDE:
            printf("ERREUR : pile vide\n");
            break;
        case ERREUR_ADRESSAGE:
            printf("ERREUR : erreur d'adressage\n");
            break;
        case ERREUR_DIVISION_PAR_ZERO:
            printf("ERREUR : division par 0\n");
            break;
        }
      if (i != n-1)
        printf("Terrain suivant :\n");
  }
  printf("Bilan :\n");
  printf("Nombre terrains où robot est sorti : %d\n", nb_sortis);
  printf("Nombre terrains où robot est bloqué : %d\n", nb_bloques);
  printf("Nombre terrains où robot a touché un obstacle : %d\n", nb_obs);
  if (nb_sortis != 0) {
    printf("Nombre de pas moyen lorsque robot est sorti : %.2f\n", (pas_moyen/ nb_sortis)); }
  else {
    printf("Le robot n'est jamais sorti\n");
  }
}
