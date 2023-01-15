/* =================================================================== */
// Progrmame Serveur qui calcule le résultat d'un coup joué à partir
// des coordonnées reçues de la part d'un client "joueur".
// Version ITERATIVE : 1 seul client/joueur à la fois
/* =================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include "tresor.h"

#define N 10

/* =================================================================== */
/* FONCTION PRINCIPALE : SERVEUR ITERATIF                              */
/* =================================================================== */
int main(int argc, char **argv)
{
    /* check arguments */

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Init variables socket */

    int sock;
    int sock_connect;
    struct sockaddr_in server_sin;

    int port = atoi(argv[1]);
    socklen_t recsize = sizeof(server_sin);

    /* Init variables game */

    int x, y;
    int game_result;
    char coord_recev[10];
    char ch_result[2];
    int x_tresor, y_tresor;

    /* Creation socket TCP */

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("Erreur creation socket");
        return EXIT_FAILURE;
    }

    /* Init caracteristiques client distant */

    server_sin.sin_addr.s_addr = htonl(INADDR_ANY);
    server_sin.sin_family = AF_INET;
    server_sin.sin_port = htons(port);

    /* Bind socket */

    if (bind(sock, (struct sockaddr *)&server_sin, sizeof(server_sin)) == -1)
    {
        perror("Binderror");
        close(sock);
        return EXIT_FAILURE;
    }

    /* Listen socket */

    if (listen(sock, 5) == -1)
    {
        perror("Erreur listen");
    }

    fprintf(stdout, "Serveur pret, en attente de requetes...\n");

    while (1)
    {
        /* Accept connexion */
        
        sock_connect = accept(sock, (struct sockaddr *)&server_sin, &recsize);
        if (sock_connect == -1)
        {
            perror("Erreur accept");
            close(sock);
            return EXIT_FAILURE;
        }

        fprintf(stdout, "Connexion etablie avec le client %s:%d\n", inet_ntoa(server_sin.sin_addr), ntohs(server_sin.sin_port));

        /* Deroulement jeu */

        srand(time(NULL));
        x_tresor = 1 + rand() % N;
        y_tresor = 1 + rand() % N;

        fprintf(stdout, "Le tresor est cache en (%d,%d)\n", x_tresor, y_tresor);

        do
        {
            /* Reception coordonnees */

            if (recv(sock_connect, coord_recev, 1000, 0) == -1)
            {
                perror("Erreur reception des coordonnees");
            }

            x = atoi(&coord_recev[0]);
            y = atoi(&coord_recev[2]);

            game_result = recherche_tresor(N, x_tresor, y_tresor, x, y);

            sprintf(ch_result, "%d", game_result);

            /* Envoi resultat */

            if (send(sock_connect, ch_result, sizeof(game_result), 0) == -1)
            {
                perror("Erreur envoi données au client");
            }
        } while (game_result != 0);

        /* Fermeture de la connexion avec le client */

        fprintf(stdout, "Connexion avec le client %s:%d terminee\n", inet_ntoa(server_sin.sin_addr), ntohs(server_sin.sin_port));

        shutdown(sock_connect, 2);
        close(sock_connect);
    }

    /* Fermeture de la socket serveur (actuellement inatteignable) */
    close(sock);

    return EXIT_SUCCESS;
} // end main
