/* =================================================================== */
// Progrmame Client à destination d'un joueur qui doit deviner la case
// du trésor. Après chaque coup le résultat retourné par le serveur est
// affiché. Le coup consite en une abcsisse et une ordonnée (x, y).
/* =================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define N 10
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"

/* ====================================================================== */
/*                  Affichage du jeu en mode texte brut                   */
/* ====================================================================== */
void afficher_jeu(int jeu[N][N], int res, int points, int coups) {

    printf("\n************ TROUVEZ LE TRESOR ! ************\n");
    printf("    ");
    for (int i=0; i<10; i++)
        printf("  %d ", i+1);
    printf("\n    -----------------------------------------\n");
    for (int i=0; i<10; i++){
        printf("%2d  ", i+1);
        for (int j=0; j<10; j++) {
            printf("|");
            switch (jeu[i][j]) {
                case -1:
                    printf(" 0 ");
                    break;
                case 0:
                    printf(GREEN " T " RESET);
                    break;
                case 1:
                    printf(YELLOW " %d " RESET, jeu[i][j]);
                    break;
                case 2:
                    printf(RED " %d " RESET, jeu[i][j]);
                    break;
                case 3:
                    printf(MAGENTA " %d " RESET, jeu[i][j]);
                    break;
            }
        }
        printf("|\n");
    }
    printf("    -----------------------------------------\n");
    printf("Pts dernier coup %d | Pts total %d | Nb coups %d\n", res, points, coups);
}


/* ====================================================================== */
/*                    Fonction principale                                 */
/* ====================================================================== */
int main(int argc, char **argv) {

    /* check arguments */

    if (argc != 3)
    {
        fprintf(stderr, "usage : %s <ip> <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Init variables game */

    int jeu[N][N];
    int lig, col;
    int res = -1, points = 0, coups = 0;

    /* Init variables socket */

    int sock;
    int server_port;
    struct in_addr server_ip;
    struct sockaddr_in server_sin;

    inet_pton(AF_INET, argv[1], &server_ip);
    server_port = atoi(argv[2]);

    /* Init jeu */

    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            jeu[i][j] = -1;

    /* Creation socket TCP */

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("Erreur creation socket");
        return EXIT_FAILURE;
    }

    /* Init caracteristiques serveur distant (struct sockaddr_in) */

    memset(&server_sin, 0, sizeof(server_sin));
    server_sin.sin_family = AF_INET;
    server_sin.sin_port = htons(server_port);
    server_sin.sin_addr = server_ip;

    /* Etablissement connexion TCP avec process serveur distant */

    if (connect(sock, (struct sockaddr *)&server_sin, sizeof(server_sin)) == -1)
    {
        perror("Erreur etablissement connexion");
        close(sock);
        return EXIT_FAILURE;
    }

    fprintf(stdout, "Connexion etablie avec le serveur %s:%d\n", argv[1], server_port);

    /* Tentatives du joueur : stoppe quand tresor trouvé */

    do {
        afficher_jeu(jeu, res, points, coups);
        printf("\nEntrer le numéro de ligne : ");
        scanf("%d", &lig);
        printf("Entrer le numéro de colonne : ");
        scanf("%d", &col);

        /* Construction requête (serialisation en chaines de caractères) */

        char request[10];
        char response[10];

        sprintf(request, "%d %d", lig, col);
        fprintf(stdout, "serialisation de la requête : %s\n", request);

        /* Envoi de la requête au serveur (send) */

        if (send(sock, request, sizeof(char **), 0) == -1)
        {
            perror("Erreur envoi requête");
        }

        fprintf(stdout, "Requête envoyée vers le serveur\n");

        /* Réception du resultat du coup (recv) */

        if (recv(sock, response, 1000, 0) == -1)
        {
            perror("Erreur reception resultat");
        }

        fprintf(stdout, "deserialisation de la réponse : %s\n", response);

        /* Deserialisation du résultat en un entier */

        res = atoi(response);

        /* Mise à jour */
        if (lig>=1 && lig<=N && col>=1 && col<=N)
            jeu[lig-1][col-1] = res;
        points += res;
        coups++;

    } while (res);

    /* Fermeture connexion TCP */

    close(sock);

    /* Terminaison du jeu : le joueur a trouvé le tresor */
    
    afficher_jeu(jeu, res, points, coups);
    printf("\nBRAVO : trésor trouvé en %d essai(s) avec %d point(s)"
            " au total !\n\n", coups, points);
    
    return EXIT_SUCCESS;
}