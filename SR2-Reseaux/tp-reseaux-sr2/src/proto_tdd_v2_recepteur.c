#include <stdio.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"

int main(int argc, char *argv[])
{
    unsigned char message[MAX_INFO]; /* message pour l'application */
    paquet_t paquet;                 /* paquet utilisé par le protocole */
    uint8_t num_seq = 0;             /* numéro de séquence du paquet */
    int fin = 0;                     /* condition d'arrêt */

    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* tant que le récepteur reçoit des données */
    while (!fin)
    {
        /* réception d'un paquet */
        de_reseau(&paquet);
        paquet.type = verif(paquet);

        if (paquet.type == ACK)
        {
            if (paquet.num_seq == num_seq)
            {
                /* construction du message et envoyer à la couche application */
                for (int i = 0; i < paquet.lg_info; i++)
                    message[i] = paquet.info[i];
                fin = vers_application(message, paquet.lg_info);
                num_seq = (num_seq + 1) % SEQ_NUM_SIZE;
            }
            /* envoi d'un ACK */
            vers_reseau(&paquet);
        }
    }

    printf("[TRP] Fin execution protocole transport.\n");
    return 0;
}
