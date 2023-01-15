/* =================================================================== */
// HERZBERG Dwayne 22000086 - Exercice 1 - version pthread_mutex_t
/* =================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define NBTMAX 30              // nombre de threads max
pthread_mutex_t mutex[NBTMAX]; // mutex pour chaque thread

struct param
{
  int rang;
  int message;
  int ligne;
  int nbThreads;
};

/* =================================================================== */
// Fonctions
/* =================================================================== */

void *ecran(void *p)
{
  struct param *param = (struct param *)p;

  for (int mess = 0; mess < param->message; mess++)
  {
    if (pthread_mutex_lock(&mutex[param->rang]) != 0)
    {
      fprintf(stderr, "Erreur lors du lock du mutex %d\n", param->rang);
      exit(EXIT_FAILURE);
    }
    
    for (int l = 0; l < param->ligne; l++)
    {
      fprintf(stdout, "Afficheur %d (%ld) : j'afiche la ligne %d/%d du message %d/%d\n", param->rang, pthread_self(), l, param->ligne, mess, param->message);
    }

    if (pthread_mutex_unlock(&mutex[(param->rang + 1) % param->nbThreads]) != 0)
    {
      fprintf(stderr, "Erreur lors du unlock du mutex %d\n", (param->rang + 1) % param->nbThreads);
      exit(EXIT_FAILURE);
    }
  }

  fprintf(stdout, "Afficheur %d (%ld) : j'ai fini mon travail\n", param->rang, pthread_self());

  pthread_exit(NULL);
}

int main(int argc, char **argv)
{
  int nbThreads;          // nombre de threads
  int nbMessage;          // nombre de messages
  int nbLigne;            // nombre de lignes
  pthread_t ptid[NBTMAX]; // tableau des identifiants des threads
  struct param p[NBTMAX]; // tableau des parametres des threads

  if (argc != 4)
  {
    fprintf(stderr, "Usage: %s <nbThreads> <nbMessage> <nbLigne>\n", argv[0]);
    return EXIT_FAILURE;
  }

  nbThreads = atoi(argv[1]);
  nbMessage = atoi(argv[2]);
  nbLigne = atoi(argv[3]);

  if (nbThreads > NBTMAX)
  {
    fprintf(stderr, "Nombre de threads trop grand, max = %d\n", NBTMAX);
    return EXIT_FAILURE;
  }

  // Creation des mutex

  for (int i = 0; i < nbThreads; i++)
  {
    if (pthread_mutex_init(&mutex[i], NULL) != 0)
    {
      fprintf(stderr, "Erreur lors de l'initialisation du mutex %d\n", i);
      exit(EXIT_FAILURE);
    }
    if (i != 0)
    {
      if (pthread_mutex_lock(&mutex[i]) != 0)
      {
        fprintf(stderr, "Erreur lors du lock du mutex %d\n", i);
        exit(EXIT_FAILURE);
      }
    }
  }

  // Creation des threads

  for (int rang = 0; rang < nbThreads; rang++)
  {
    p[rang].rang = rang;
    p[rang].message = nbMessage;
    p[rang].ligne = nbLigne;
    p[rang].nbThreads = nbThreads;

    if (pthread_create(&ptid[rang], NULL, ecran, (void *)&p[rang]) != 0)
    {
      perror("pthread_create");
      return EXIT_FAILURE;
    }
  }

  for (int rang = 0; rang < nbThreads; rang++)
  {
    if (pthread_join(ptid[rang], NULL) != 0)
    {
      perror("pthread_join");
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}