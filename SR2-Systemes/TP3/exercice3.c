/* =================================================================== */
// HERZBERG Dwayne 22000086 - Exercice 3
// version sans semaphores, non fonctionnelle
/* =================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define NMAX 30

struct message
{
  char texte[20];
  int owner;
};

struct message buffer[NMAX];
int ICP = 0, ICV = 0; // indice case pleine, indice case vide

int size; // taille du tableau partage
int ND;   // nombre de depots
int NR;   // nombre de retrais

/* =================================================================== */
// Fonctions
/* =================================================================== */

void *producteur(void *p)
{
  int *rang = (int *)p;
  char temp[20];

  for (int i = 0; i < ND; i++)
  {
    buffer[ICV].owner = *rang;

    sprintf(temp, "Message %d", i);
    strcpy(buffer[ICV].texte, temp);

    fprintf(stdout, "Producteur %d (%ld) : message (\"%s\")\n", *rang, pthread_self(), buffer[ICV].texte);

    ICV = (ICV + 1) % size;
  }

  pthread_exit(NULL);
}

void *consommateur(void *p)
{
  struct message m;

  for (int i = 0; i < NR; i++)
  {
    m.owner = buffer[ICP].owner;
    strcpy(m.texte, buffer[ICP].texte);

    fprintf(stdout, "Consommateur %ld : \"%s\" de %d\n", pthread_self(), m.texte, m.owner);

    ICP = (ICP + 1) % size;
  }

  pthread_exit(NULL);
}

int main(int argc, char **argv)
{
  int NP;                // nombre de producteurs
  int NC;                // nombre de consommateurs
  pthread_t ptidP[NMAX]; // tableau des identifiants des threads producteurs
  pthread_t ptidC[NMAX]; // tableau des identifiants des threads consommateurs
  int p[NMAX];           // parametres des threads producteurs

  // verification des arguments du programme

  if (argc != 6)
  {
    fprintf(stderr, "Usage: %s <nombre de producteurs> <nombre de consommateurs> <nombre de depots> <nombre de retrais> <taille du tableau partage>\n", argv[0]);
    return EXIT_FAILURE;
  }

  NP = atoi(argv[1]);
  NC = atoi(argv[2]);
  ND = atoi(argv[3]);
  NR = atoi(argv[4]);
  size = atoi(argv[5]);

  if (size > NMAX)
  {
    fprintf(stderr, "Taille du tableau partage trop grande\n");
    return EXIT_FAILURE;
  }

  // creation des processus

  for (int rang = 0; rang < NP; rang++)
  {
    p[rang] = rang;
    if (pthread_create(&ptidP[rang], NULL, producteur, (void *)&p[rang]) != 0)
    {
      perror("pthread_create");
      return EXIT_FAILURE;
    }
  }

  for (int rang = 0; rang < NC; rang++)
  {
    if (pthread_create(&ptidC[rang], NULL, consommateur, NULL) != 0)
    {
      perror("pthread_create");
      return EXIT_FAILURE;
    }
  }

  for (int rang = 0; rang < NP; rang++)
  {
    pthread_join(ptidP[rang], NULL);
  }

  for (int rang = 0; rang < NC; rang++)
  {
    pthread_join(ptidC[rang], NULL);
  }

  return EXIT_SUCCESS;
}
