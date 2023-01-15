/* =================================================================== */
// HERZBERG Dwayne 22000086 - Exercice 1 - version sem_t
/* =================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

#define NBTMAX 30    // nombre de threads max
sem_t mutex[NBTMAX]; // mutex pour chaque thread

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
    if (sem_wait(&mutex[param->rang]) != 0)
    {
      fprintf(stderr, "Erreur lors du lock du mutex %d\n", param->rang);
      exit(EXIT_FAILURE);
    }

    for (int l = 0; l < param->ligne; l++)
    {
      fprintf(stdout, "Afficheur %d (%ld) : j'afiche la ligne %d/%d du message %d/%d\n", param->rang, pthread_self(), l, param->ligne, mess, param->message);
    }
    
    if (sem_post(&mutex[(param->rang + 1) % param->nbThreads]) != 0)
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

  if (sem_init(&mutex[0], 0, 1) != 0)
  {
    fprintf(stderr, "Erreur lors de la creation du mutex 0\n");
    return EXIT_FAILURE;
  }
  
  for (int i = 1; i < nbThreads; i++)
  {
    if (sem_init(&mutex[i], 0, 0) != 0)
    {
      fprintf(stderr, "Erreur lors de la creation du mutex %d\n", i);
      return EXIT_FAILURE;
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