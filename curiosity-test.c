#include "environnement.h"
#include "interprete.h"
#include "programme.h"
#include "observateur.h"

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

  char terrain[100];
  char programme[100];
  char nom_fich[100];
  char e;
  int pas = 0, pas_lu;
  FILE *f;

  if (argc < 2) {
    printf("Usage: %s <fichier>\n", argv[0]);
    return 1;
  }

  f = fopen(argv[1], "r");
  while (f == NULL) {
    printf("Erreur lors de la lecture du terrain, veuillez entrer un nouveau nom de fichier\n");
    scanf("%s",nom_fich);
    f = fopen(nom_fich, "r");
  }

  /* Initialisation de l'environnement : lecture du terrain,
     initialisation de la position du robot */
  fscanf(f, "%s", terrain);
  errt = initialise_environnement(&envt, terrain);
  gestion_erreur_terrain(errt);

  /* Lecture du programme */
  fscanf(f, "%s", programme);
  errp = lire_programme(&prog, programme);
  gestion_erreur_programme(errp);

  /* Lecture des pas à exécuter */
  fscanf(f, "%d", &pas_lu);

  /* Lecture du caractère e */
  fscanf(f, "\n");  /* Lecture du caractère de retour (new line) */
  fscanf(f, "%c", &e);

  /* Initialisation de l'état */
  init_etat(&etat);
  do {
    res = exec_pas(&prog, &envt, &etat);
    /* Affichage du terrain et du robot */
    afficher_envt(&envt);
    pas++;
  } while (res == OK_ROBOT && pas < pas_lu);

  if (pas != pas_lu) {
    printf("Le pas n'est pas correct (pas attendu : %d, pas lu : %d)\n", pas_lu, pas);
    return 1;
  }

  if (e == 'N' || e == 'F') {
    int x1, x2;
    int y1, y2;
    fscanf(f, "%d %d", &x1, &y1);
    position(&(envt.r), &x2, &y2);

    char o1, o3;
    Orientation o2;
    fscanf(f, "\n");
    fscanf(f, "%c", &o1);
    o2 = orient(&(envt.r));

    switch (o2) {
      case Nord :
        o3 = 'N';
        break;
      case Ouest :
        o3 = 'O';
        break;
      case Est :
        o3 = 'E';
        break;
      case Sud :
        o3 = 'S';
        break;
    }    

    if ((x1==x2) && (y1==y2) && (o1==o3)) {
      printf("OK\n");
    }
    else {
      if (x1!=x2) {
        printf("Abscisse incorrecte\n");
      }
      if (y1!=y2) {
        printf("Ordonnée incorrecte\n");
      }
      if (o1!=o3) {
        printf("Orientation incorrecte\n");
      }
    }
  }

  /* Affichage du résultat */
  switch (res) {
  case OK_ROBOT:
    if (e == 'N') {
      printf("Cohérent : Robot sur une case libre, programme non terminé (ne devrait pas "
           "arriver)\n");
    }
    else {
      if (e == 'F') printf("Erreur : Le programme devrait être terminé (état actuel : Robot sur une case libre, programme non terminé)\n");
      if (e == 'S') printf("Erreur : Robot devrait être sorti du terrain (état actuel : Robot sur une case libre, programme non terminé)\n");
      if (e == 'O') printf("Erreur : Robot devrait rencontrer un rocher (état actuel : Robot sur une case libre, programme non terminé)\n");
      if (e == 'P') printf("Erreur : Robot devrait être dans l'eau (état actuel : Robot sur une case libre, programme non terminé)\n");    
    }
    break;
  case SORTIE_ROBOT:
    if (e == 'S') {
      printf("Cohérent : Robot est sorti du terrain\n");
    }
    else {
      if (e == 'F') printf("Erreur : Le programme devrait être terminé (état actuel : Robot est sorti du terrain)\n");
      if (e == 'N') printf("Erreur : Robot devrait être sur une case libre (état actuel : Robot est sorti du terrain)\n");
      if (e == 'O') printf("Erreur : Robot devrait rencontrer un rocher (état actuel : Robot est sorti du terrain)\n");
      if (e == 'P') printf("Erreur : Robot devrait être dans l'eau (état actuel : Robot est sorti du terrain)\n");    
    }
    break;
  case ARRET_ROBOT:
    if (e == 'F') {
      printf("Cohérent : Robot sur une case libre, programme terminé\n");
    }
    else {
      if (e == 'N') printf("Erreur : Le programme ne devrait pas être terminé (état actuel : Robot sur une case libre, programme terminé)\n");
      if (e == 'S') printf("Erreur : Robot devrait être sorti du terrain (état actuel : Robot sur une case libre, programme non terminé)\n");
      if (e == 'O') printf("Erreur : Robot devrait rencontrer un rocher (état actuel : Robot sur une case libre, programme non terminé)\n");
      if (e == 'P') printf("Erreur : Robot devrait être dans l'eau (état actuel : Robot sur une case libre, programme non terminé)\n");    
    }
    break;
  case PLOUF_ROBOT:
    if (e == 'P') {
      printf("Cohérent : Robot est tombé dans l'eau\n");
    }
    else {
      if (e == 'F') printf("Erreur : Le programme devrait être terminé (état actuel : Robot est tombé dans l'eau)\n");
      if (e == 'S') printf("Erreur : Robot devrait être sorti du terrain (état actuel : Robot est tombé dans l'eau)\n");
      if (e == 'O') printf("Erreur : Robot devrait rencontrer un rocher (état actuel : Robot est tombé dans l'eau)\n");
      if (e == 'N') printf("Erreur : Robot devrait être sur une case libre (état actuel : Robot est tombé dans l'eau)\n");    
    }
    break;
  case CRASH_ROBOT:
    if (e == 'O') {
      printf("Cohérent : Robot a rencontré un rocher\n");
    }
    else {
      if (e == 'F') printf("Erreur : Le programme devrait être terminé (état actuel : Robot a rencontré un rocher)\n");
      if (e == 'S') printf("Erreur : Robot devrait être sorti du terrain (état actuel : Robot a rencontré un rocher)\n");
      if (e == 'P') printf("Erreur : Robot devrait être dans l'eau (état actuel : Robot a rencontré un rocher)\n");
      if (e == 'N') printf("Erreur : Robot devrait être sur une case libre (état actuel : Robot a rencontré un rocher)\n");    
    }
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
}
