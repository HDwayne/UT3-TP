#include <stdio.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"

int main(int argc, char *argv[])
{
    unsigned char message[MAX_INFO]; /* message de l'application */
    int taille_msg;                  /* taille du message */
    paquet_t paquet;                 /* paquet utilisé par le protocole */
    uint8_t num_seq = 0;             /* numéro de séquence du paquet */
    int evt;                         /* évènement reçu */

    init_reseau(EMISSION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* lecture de donnees provenant de la couche application */
    de_application(message, &taille_msg);

    /* tant que l'émetteur a des données à envoyer */

    while (taille_msg != 0)
    {
        /* construction du paquet */
        for (int i = 0; i < taille_msg; i++)
            paquet.info[i] = message[i];
        paquet.lg_info = taille_msg;
        paquet.type = DATA;
        paquet.num_seq = num_seq;
        paquet.somme_ctrl = generate_sommectrl(paquet);

        /* envoi du paquet */
        do
        {
            vers_reseau(&paquet);
            depart_temporisateur(100);
            evt = attendre();
        } while (evt != PAQUET_RECU);

        arret_temporisateur();
        de_reseau(&paquet);
        de_application(message, &taille_msg);

        num_seq = (num_seq + 1) % SEQ_NUM_SIZE;
    }

    printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
    return 0;
}
