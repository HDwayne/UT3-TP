#include <stdio.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"

int main(int argc, char *argv[])
{
    unsigned char message[MAX_INFO]; /* message de l'application */
    int taille_msg;                  /* taille du message */
    paquet_t paquet;                 /* paquet utilisé par le protocole */
    int service;                     /* service demandé par l'application */
    uint8_t num_seq = 0;             /* numéro de séquence du paquet */
    int evt;                         /* évènement reçu */

    init_reseau(EMISSION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /*  établissement de la connexion */

    de_application_mode_c(&service, message, &taille_msg);

    if (service == T_CONNECT)
    {
        /* envoi de la demande de connexion */

        paquet.type = CON_REQ;
        do
        {
            vers_reseau(&paquet);
            depart_temporisateur(100);
            evt = attendre();
        } while (evt != PAQUET_RECU);

        arret_temporisateur();

        /* attente de l'acceptation de la connexion */

        attendre();
        de_reseau(&paquet);

        switch (paquet.type)
        {
        case CON_ACCEPT:
            vers_application_mode_c(T_CONNECT_ACCEPT, message, taille_msg);
            break;
        case CON_REFUSE:
            vers_application_mode_c(T_CONNECT_REFUSE, message, taille_msg);
            return 1;
            break;
        }
    }

    /* transfert des données */

    de_application_mode_c(&service, message, &taille_msg);

    while (taille_msg != 0 && service != T_DISCONNECT)
    {
        /* construction paquet */
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
        de_application_mode_c(&service, message, &taille_msg);

        num_seq = (num_seq + 1) % SEQ_NUM_SIZE;
    }

    /* libération de la connexion */

    /* envoi de la demande de deconnexion */

    paquet.type = CON_CLOSE;
    do
    {
        vers_reseau(&paquet);
        depart_temporisateur(100);
        evt = attendre();
    } while (evt != PAQUET_RECU);
    arret_temporisateur();

    /* attente de la confirmation de la deconnexion */

    attendre();
    de_reseau(&paquet);

    printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
    return 0;
}
