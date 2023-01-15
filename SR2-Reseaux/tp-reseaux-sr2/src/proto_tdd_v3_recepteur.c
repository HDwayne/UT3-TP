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
    int connected = 0;               /* 0 = non connecté, 1 = connecté */

    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* tant que le récepteur reçoit des données */
    while (!fin)
    {
        de_reseau(&paquet);

        switch (paquet.type)
        {
        case DATA:
            /* si le paquet reçu est un paquet de données -> traitement V2 */
            paquet.type = verif(paquet);
            if (paquet.type == ACK)
            {
                if (paquet.num_seq == num_seq)
                {
                    for (int i = 0; i < paquet.lg_info; i++)
                        message[i] = paquet.info[i];
                    fin = vers_application_mode_c(T_DATA, message, paquet.lg_info);
                    num_seq = (num_seq + 1) % SEQ_NUM_SIZE;
                }
                vers_reseau(&paquet);
            }
            break;

        case CON_REQ:
            /* si le paquet reçu est une demande de connexion */
            if (connected || vers_application_mode_c(T_CONNECT, message, paquet.lg_info) == T_CONNECT_ACCEPT)
            {
                /* si le récepteur est connecté ou si l'application accepte la connexion */
                paquet.type = CON_ACCEPT;
                vers_reseau(&paquet);
                connected = 1;
            }
            else
            {
                paquet.type = CON_REFUSE;
                vers_reseau(&paquet);
                return 1;
            }
            break;

        case CON_CLOSE:
            /* si le paquet reçu est une demande de fermeture de connexion */
            vers_application_mode_c(T_DISCONNECT, message, paquet.lg_info);
            paquet.type = CON_CLOSE_ACK;
            vers_reseau(&paquet);
            fin = 1;
            break;
        }
    }

    printf("[TRP] Fin execution protocole transport.\n");
    return 0;
}
