#include <stdio.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"

int main(int argc, char *argv[])
{
    unsigned char message[MAX_INFO]; /* message pour l'application */
    paquet_t paquet;                 /* paquet utilisé par le protocole */
    int fin = 0;                     /* condition d'arrêt */

    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* tant que le récepteur reçoit des données */
    while (!fin)
    {
        de_reseau(&paquet);

        paquet.type = verif(paquet);

        if (paquet.type == ACK)
        {
            for (int i = 0; i < paquet.lg_info; i++)
                message[i] = paquet.info[i];
            fin = vers_application(message, paquet.lg_info);
        }
        vers_reseau(&paquet);
    }

    printf("[TRP] Fin execution protocole transport.\n");
    return 0;
}
