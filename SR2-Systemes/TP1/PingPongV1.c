/* =================================================================== */
// HERZBERG Dwayne 22000086 - PingPong V1
/* =================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

/* variable global */

int TPF[2];
int TFP[2];
int N;

/* =================================================================== */
// Fonctions
/* =================================================================== */

int pere()
{
  char c;

  // orienter les tubes
  close(TPF[0]); // write
  close(TFP[1]); // read

  for (int i = 0; i < N; i++)
  {
    if (write(TPF[1], &c, sizeof(char)) == -1)
    {
      perror("READ");
      return 2;
    }

    fprintf(stdout, "Processus de pid %d : Ping\n", getpid());

    if (read(TFP[0], &c, sizeof(char)) == -1)
    {
      perror("READ");
      return 2;
    }
  }

  close(TPF[1]);
  close(TFP[0]);

  return 0;
}

int fils()
{
  char c;
  size_t vread;

  // orienter les tubes
  close(TPF[1]); // read
  close(TFP[0]); // write

  while ((vread = read(TPF[0], &c, sizeof(char))) > 0)
  {
    if (vread == -1)
    {
      perror("READ");
      return 2;
    }

    fprintf(stdout, "Processus de pid %d : Pong\n", getpid());

    if (write(TFP[1], &c, sizeof(char)) == -1)
    {
      perror("WRITE TFP");
      return 3;
    }
  }
  
  close(TPF[0]);
  close(TFP[1]);

  return 0;
}

int main(int argc, char **argv)
{
  // verification des arguments du programme

  if (argc != 2)
  {
      printf("Usage: %s <N>\n", argv[0]);
      return EXIT_FAILURE;
  }

  N = atoi(argv[1]);

  // initialisation des tubes avant la creation des processus

  if (pipe(TPF) == -1)
  {
    perror("TUBE TPF");
    return EXIT_FAILURE;
  }

  if (pipe(TFP) == -1)
  {
    perror("TUBE TFP");
    return EXIT_FAILURE;
  }

  // creation des processus

  switch (fork())
  {
    case -1:
      perror("FORK");
      return EXIT_FAILURE;
      break;
     case 0:
       return fils();
    default:
      break;
  }

  pere();

  fprintf(stdout, "Fin Ping\n");
  fprintf(stdout, "Fin Pong\n");

  return EXIT_SUCCESS;
}
