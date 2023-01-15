/* =================================================================== */
// HERZBERG Dwayne 22000086 - chocolaterie
/* =================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

#define NFMAX 30

#define READ 0
#define WRITE 1

#define NB_CHOCOLAT 94

/* variable global */

int TPN[NFMAX][2];

/* =================================================================== */
// Fonctions
/* =================================================================== */

int usine(int nb_fils, int nb_fois, int sec)
{
  int div, reste, temp, nb_choco;

  for (int fils = 0; fils < nb_fils; fils++){
    close(TPN[fils][READ]);
  }

  for (int fois = 0; fois < nb_fois; fois++)
  {
    nb_choco = NB_CHOCOLAT;
    fprintf(stdout, "Usine : je produis %d chocolats !\n", nb_choco);

    for (int fils = nb_fils-1; fils >= 0 && nb_choco >= 6; fils--)
    {
      // fprintf(stdout, "fils : %d\n", fils);

      div = nb_choco / ((fils+1) * 6);
      reste = nb_choco % ((fils + 1) * 6);
      temp = div * ((fils + 1) * 6);

      // fprintf(stdout, "nb_choco = %d, div = %d, reste = %d, temp = %d\n", nb_choco, div, reste, temp);

      if (temp > 0)
      {
        if (write(TPN[fils][WRITE], &temp, sizeof(int)) == -1)
        {
          perror("WRITE TFP");
          return EXIT_FAILURE;
        }
        // fprintf(stdout, "Usine : %d chocolats pour %d !\n", temp, fils);
      }

      nb_choco = reste;

      // fprintf(stderr, "nb_choco = %d\n", nb_choco);
    }

    if (nb_choco > 0)
    {
      fprintf(stdout, "Usine : aucune chaîne d’emballage ne peut traiter les %d chocolats restants !\n", nb_choco);
    }

    sleep(sec);
  }

  for (int fils = 0; fils < nb_fils; fils++){
    close(TPN[fils][WRITE]);
  }

  // fprintf(stdout, "Usine : je suis terminée !\n");

  return EXIT_SUCCESS;
}

int emballage(int rang, int nb_fils)
{
  int nb_choco, nb_boite = 0;
  size_t vread;

  // orienter les tubes
  for (int i = 0; i < nb_fils; i++)
  {
    close(TPN[i][WRITE]);
  }
  

  // lire dans le tube du coureur precedent
  while ((vread = read(TPN[rang][0], &nb_choco, sizeof(int))) > 0)
  {
    if (vread == -1)
    {
      perror("READ");
      return 2;
    }

    // fprintf(stdout, "Chaîne %d : je reçois %d chocolats !\n", rang, nb_choco);

    while (nb_choco >= 6 * (rang + 1))
    {
      nb_choco -= 6 * (rang + 1);
      fprintf(stdout, "Chaîne %d : nouvelle boite de %d !\n", rang, (rang + 1) * 6);
      nb_boite++;
    }
  }

  fprintf(stdout, "Chaîne %d : j'ai produit %d boites de %d !\n", rang, nb_boite, (rang + 1) * 6);
  

  for (int i = 0; i < nb_fils; i++)
  {
    close(TPN[rang][READ]);
  }
  

  return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
  int nb_repetitions;
  int nb_fils;
  int sec;

  // verification des arguments du programme

  if (argc != 4)
  {
    fprintf(stderr, "Usage: %s nb_repetitions nb_fils sec\n", argv[0]);
    return EXIT_FAILURE;
  }

  nb_repetitions = atoi(argv[1]);
  nb_fils = atoi(argv[2]);
  sec = atoi(argv[3]);

  // initialisation des tubes avant la creation des processus

  for (int i = 0; i < nb_fils; i++)
  {
    if (pipe(TPN[i]) == -1)
    {
      perror("TUBE");
      return EXIT_FAILURE;
    }
  }

  // creation des processus

  for (int rang = 0; rang < nb_fils; rang++)
  {
    switch (fork())
    {
    case -1:
      perror("fork");
      return EXIT_FAILURE;
    case 0:
      return emballage(rang, nb_fils);
    default:
      break;
    }
  }

  return usine(nb_fils, nb_repetitions, sec);
}
