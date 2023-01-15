/* =================================================================== */
// HERZBERG Dwayne 22000086 - Exercice 2
/* =================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NFMAX 30

int solde = 0;  // solde du compte
int nb_c_d = 0; // nombre de debits et de credits

/* =================================================================== */
// Fonctions
/* =================================================================== */

void *credit(void *p)
{
  srand(time(NULL));

  for (int i = 0; i < nb_c_d; i++)
  {
    int random = rand() % 100;
    solde += random;
    printf("Credit %ld : Credit (%d) => solde (%d)\n", pthread_self(), random, solde);
  }
  
  pthread_exit(NULL);
}

void *debit(void *p)
{
  srand(time(NULL));

  for (int i = 0; i < nb_c_d; i++)
  {
    int random = rand() % 100;
    solde -= random;
    printf("Debit %ld : Debit (%d) => solde (%d)\n", pthread_self(), random, solde);
  }
  
  pthread_exit(NULL);
}

int main(int argc, char **argv)
{
  int nb_thread;
  pthread_t ptid[NFMAX];
  int *res = NULL;

  // verification des arguments du programme

  if (argc != 4)
  {
    fprintf(stderr, "Usage: %s nb_thread solde nb_debit_credit\n", argv[0]);
    return EXIT_FAILURE;
  }

  nb_thread = atoi(argv[1]);
  solde = atoi(argv[2]);
  nb_c_d = atoi(argv[3]);

  if (nb_thread > NFMAX)
  {
    fprintf(stderr, "Nombre de thread trop grand (max %d)\n", NFMAX);
    return EXIT_FAILURE;
  }

  // creation des processus

  for (int rang = 0; rang < nb_thread; rang++)
  {
    if (pthread_create(&ptid[rang], NULL, credit, NULL) != 0)
    {
      perror("pthread_create");
      return EXIT_FAILURE;
    }
  }

  for (int rang = 0; rang < nb_thread; rang++)
  {
    pthread_join(ptid[rang], NULL);
  }

  for (int rang = 0; rang < nb_thread; rang++)
  {
    if (pthread_create(&ptid[rang], NULL, debit, NULL) != 0)
    {
      perror("pthread_create");
      return EXIT_FAILURE;
    }
  }

  for (int rang = 0; rang < nb_thread; rang++)
  {
    pthread_join(ptid[rang], NULL);
  }

  fprintf(stdout, "Solde final : %d\n", solde);

  return EXIT_SUCCESS;
}
