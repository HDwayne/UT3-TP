/* =================================================================== */
// HERZBERG Dwayne 22000086 - Exercice 1 - Version 1
/* =================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define NFMAX 30

/* =================================================================== */
// Fonctions
/* =================================================================== */

int processus(int rang, int nb_fois){
  for (int i = 0; i < nb_fois; i++)
  {
    fprintf(stdout, "Activité rang %d : identifiant %d\n", rang, getpid());
  }
  return rang;
}

int main(int argc, char **argv)
{
  int na;
  int nf;

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
    switch (fork())
    {
    case -1:
      perror("fork");
      return EXIT_FAILURE;
    case 0:
      return processus(rang, na);
    default:
      break;
    }
  }

  // attente de la fin des processus

  for (int rang = 0; rang < nf; rang++)
  {
    int status;
    wait(&status);
    fprintf(stdout, "Processus %d terminé avec le code %d\n", rang, WEXITSTATUS(status));
  }

  return EXIT_SUCCESS;
}
