#include <stdio.h>
#include <stdlib.h>
#include "observateur.h"

void init_observateur(Observateur *obs){
    obs->etat = ETAT_INITIAL;
}

Etats recuperer_etat_obs(Observateur obs){
    return obs.etat;
}

Etats transition(Etats etat, Alphabet al){
    if(etat == ETAT_INITIAL){
        if(al == GAUCHE || al == DROIT) return ETAT_INITIAL;
        else if(al == MESURE_DEVANT) return ETAT_MESURE;
        else return ETAT_ERREUR;
    }
    if(etat == ETAT_MESURE){
        if(al == GAUCHE || al == DROIT || al == AVANCER) return ETAT_INITIAL;
        else return ETAT_MESURE;
    }
    return ETAT_ERREUR;
}

Resultat decision_observateur(Etats etat){
    if(etat == ETAT_ERREUR) return REFUSER;
    else return ACCEPTER;
}