/* =================================================================== */
// HERZBERG Dwayne 22000086 - Course de relais
/* =================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

#define NMAX 30

/* variable global */

int TPN[NMAX][2];

/* =================================================================== */
// Fonctions
/* =================================================================== */

int arbitre(int n)
{
  // initialisation des variables
  char c;
  struct timeval t1;
  struct timeval t2;

  gettimeofday(&t1, NULL);

  // orienter les tubes
  close(TPN[n][1]); // read
  close(TPN[0][0]); // write

  // ecrire dans le tube de depart 0
  if (write(TPN[0][1], &c, sizeof(char)) == -1)
  {
    perror("WRITE TFP");
    return EXIT_FAILURE;
  }

  fprintf(stdout, "[%d] Arbitre : Top depart !\n", getpid());

  // lire dans le tube de fin, n coureur
  if (read(TPN[n][0], &c, sizeof(char)) == -1)
  {
    perror("READ");
    return EXIT_FAILURE;
  }

  gettimeofday(&t2, NULL);

  fprintf(stdout, "[%d] Arbitre : chrono = %ld sec %ld msec\n", getpid(), t2.tv_sec - t1.tv_sec, t2.tv_usec - t1.tv_usec);

  close(TPN[n][0]);
  close(TPN[0][1]);

  return EXIT_SUCCESS;
}

int coureur(int i, int n)
{
  char c;

  // orienter les tubes
  close(TPN[i - 1][1]); // read
  close(TPN[i][0]);     // write

  // lire dans le tube du coureur precedent
  if (read(TPN[i - 1][0], &c, sizeof(char)) == -1)
  {
    perror("READ");
    return EXIT_FAILURE;
  }
  fprintf(stdout, "[%d] Coureur n°%d j'ai reçu le témoin\n", getpid(), i);

  // courir n fois
  for (int j = 0; j < n; j++)
    fprintf(stdout, "[%d] Coureur : je cours\n", getpid());

  // ecrire dans le tube du coureur suivant
  if (write(TPN[i][1], &c, sizeof(char)) == -1)
  {
    perror("WRITE TFP");
    return EXIT_FAILURE;
  }
  fprintf(stdout, "[%d] Coureur n°%d j'ai passé le témoin\n", getpid(), i);

  close(TPN[i - 1][0]);
  close(TPN[i][1]);

  return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
  int N;
  int D;

  // verification des arguments du programme

  if (argc != 3)
  {
    printf("Usage: %s <N> <d>\n", argv[0]);
    return EXIT_FAILURE;
  }

  N = atoi(argv[1]);
  D = atoi(argv[2]);

  // initialisation des tubes avant la creation des processus

  for (int i = 0; i < N + 1; i++)
  {
    if (pipe(TPN[i]) == -1)
    {
      perror("TUBE");
      return EXIT_FAILURE;
    }
  }

  // creation des processus

  for (int i = 1; i < N + 1; i++)
  {
    switch (fork()) 
    {
      case -1:
        perror("fork");
        return EXIT_FAILURE;
      case 0:
        return coureur(i, D);
      default:
        break;
    }
  }

  return arbitre(N);
}
