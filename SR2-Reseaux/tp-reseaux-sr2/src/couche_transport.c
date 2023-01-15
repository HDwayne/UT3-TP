#include <stdio.h>
#include "couche_transport.h"
#include "services_reseau.h"
#include "application.h"

/* ************************************************************************** */
/* *************** Fonctions utilitaires couche transport ******************* */
/* ************************************************************************** */

// RAJOUTER VOS FONCTIONS DANS CE FICHIER...





/* ===================== Fenêtre d'anticipation ============================= */

/*--------------------------------------*/
/* Fonction d'inclusion dans la fenetre */
/*--------------------------------------*/
int dans_fenetre(unsigned int inf, unsigned int pointeur, int taille) {

    unsigned int sup = (inf+taille-1) % SEQ_NUM_SIZE;

    return
        /* inf <= pointeur <= sup */
        ( inf <= sup && pointeur >= inf && pointeur <= sup ) ||
        /* sup < inf <= pointeur */
        ( sup < inf && pointeur >= inf) ||
        /* pointeur <= sup < inf */
        ( sup < inf && pointeur <= sup);
}

uint8_t generate_sommectrl(paquet_t paquet){
    uint8_t result = paquet.num_seq^paquet.type^paquet.lg_info;
    for (int i = 0; i < paquet.lg_info; i++){
        result = result^paquet.info[i];
    }
    return result;
}

uint8_t verif(paquet_t paquet){
    if (paquet.somme_ctrl == generate_sommectrl(paquet)){
        return ACK;
    }
    return NACK;
}
