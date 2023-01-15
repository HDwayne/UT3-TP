/* =================================================================== */
// HERZBERG Dwayne 22000086 - Exercice 1 - Version 2
/* =================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NFMAX 30

int na = 0;

/* =================================================================== */
// Fonctions
/* =================================================================== */

void *processus(void *p){
  int *cr = malloc(sizeof(int));
  cr = (int*)p;
  for (int i = 0; i < na; i++)
  {
    fprintf(stdout, "Activité rang %d : identifiant %ld\n", *cr, pthread_self());
  }
  pthread_exit((void*)cr);
}

int main(int argc, char **argv)
{
  int nf;
  pthread_t ptid[NFMAX];
  int trang[NFMAX];
  int *res = NULL;

  // verification des arguments du programme

  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s NA NF\n", argv[0]);
    return EXIT_FAILURE;
  }

  na = atoi(argv[1]);
  nf = atoi(argv[2]);

  // creation des processus

  for (int rang = 0; rang < nf; rang++)
  {
    trang[rang] = rang;
    if (pthread_create(&ptid[rang], NULL, processus, (void *)&trang[rang]) != 0)
    {
      perror("pthread_create");
      return EXIT_FAILURE;
    }
  }

  // attente de la fin des processus

  for (int rang = 0; rang < nf; rang++)
  {
    pthread_join(ptid[rang], (void**)&res);
    fprintf(stdout, "Processus %d terminé avec le code %d\n", rang, *res);
  }

  return EXIT_SUCCESS;
}
