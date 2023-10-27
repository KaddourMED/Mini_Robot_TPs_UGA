#ifndef _OBSERVATEUR_H_
#define _OBSERVATEUR_H_

/* #include "robot.h"
#include "terrain.h" */

typedef enum{
    AVANCER,
    GAUCHE,
    DROIT,
    PAS_MESURE,
    MESURE_DEVANT,
    MESURE_DERRIERE,
    MESURE_DEVANT_DROIT,
    MESURE_DEVANT_GAUCHE,
    MESURE_DERRIERE_DROIT,
    MESURE_DERRIERE_GAUCHE,
    MESURE_DROIT,
    MESURE_GAUCHE,

} Alphabet;

typedef enum{
    ETAT_INITIAL,
    ETAT_MESURE,
    ETAT_ERREUR
} Etats;

typedef enum{
    ACCEPTER,
    REFUSER,
}Resultat;

typedef struct Observateur{
    Etats etat;
    //alphabet alpha;
}Observateur;

void init_observateur(Observateur *obs);

Etats recuperer_etat_obs(Observateur obs);

Etats transition(Etats etat, Alphabet al);

Resultat decision_observateur(Etats etat);

#endif