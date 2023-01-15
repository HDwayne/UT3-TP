/* =================================================================== */
// HERZBERG Dwayne 22000086 - Exercice 4 - rendez-vous
/* =================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

#define NMAX 30

sem_t mutex, rdv;
int nbArrivee = 0;

/* =================================================================== */
// Fonctions
/* =================================================================== */

void *rendezVous(void *p)
{
  int *nbTT = (int *)p; // nombre de personnes TT

  sem_wait(&mutex);
  fprintf(stdout, "J'arrive au rdv\n");
  nbArrivee++;

  if (nbArrivee < *nbTT) // si il reste des personnes a attendre
  {
    fprintf(stdout, "Je ne suis pas le dernier arrivé\n");
    sem_post(&mutex);
    sem_wait(&rdv);
    fprintf(stdout, "Je peux continuer\n");
  }
  else
  {
    fprintf(stdout, "Je suis le dernier arrivé\n");
    sem_post(&mutex);

    for (int i = 0; i < *nbTT; i++)
    {
      sem_post(&rdv);
    }

    fprintf(stdout, "Je peux continuer\n");
  }

  pthread_exit(NULL);
}

int main(int argc, char **argv)
{
  int nbThreads;        // nombre de threads
  pthread_t ptid[NMAX]; // tableau des identifiants des threads producteurs
  int param[NMAX];      // tableau des parametres des threads producteurs

  // verification des arguments du programme

  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s <nombre de thread>\n", argv[0]);
    return EXIT_FAILURE;
  }

  nbThreads = atoi(argv[1]);

  // initialisation des semaphores

  sem_init(&mutex, 0, 1);
  sem_init(&rdv, 0, 0);

  // creation des processus

  for (int rang = 0; rang < nbThreads; rang++)
  {
    param[rang] = nbThreads;
    if (pthread_create(&ptid[rang], NULL, rendezVous, (void *)&param[rang]) != 0)
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