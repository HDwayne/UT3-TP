/* =================================================================== */
// HERZBERG Dwayne 22000086 - appel d'offre
/* =================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

#define NFMAX 30

#define READ 0
#define WRITE 1

struct _devis
{
  char reference[2];
  int quantite;
  int prix;
  int id_fournisseur;
};

typedef struct _devis devis;

/* variable global */

int CTF[NFMAX][2];
int FTC[2];

/* =================================================================== */
// Fonctions
/* =================================================================== */

int client(int nb_fournisseurs)
{
  // initialisation des variables
  devis ask, responds, selected;
  size_t vread;
  int ping;

  strcpy(ask.reference, "A1");
  ask.quantite = 100;

  selected.prix = 0;

  // orienter les tubes
  for (int f = 0; f < nb_fournisseurs; f++)
  {
    close(CTF[f][READ]);
  }
  close(FTC[WRITE]);

  for (int f = 0; f < nb_fournisseurs; f++)
  {
    // envoyer la demande de devis
    if (write(CTF[f][WRITE], &ask, sizeof(devis)) == -1)
    {
      perror("READ");
      return 2;
    }

    fprintf(stdout, "Client: j'envoie une demande de devis au fournisseur %d\n", f);
  }

  // attendre les réponses
  while ((vread = read(FTC[READ], &responds, sizeof(devis))) > 0)
  {
    if (vread == -1)
    {
      perror("READ");
      return 2;
    }

    fprintf(stdout, "Client : devis de %s : %d euros du fournisseur %d\n", responds.reference, responds.prix, responds.id_fournisseur);

    if (selected.prix == 0 || responds.prix < selected.prix)
    {
      selected = responds;
    }
  }

  fprintf(stdout, "Client : j'ai reçu tous les devis\n");
  fprintf(stdout, "Client : le fournisseur %d a le meilleur prix : %d euros\n", selected.id_fournisseur, selected.prix);

  // ping

  for (int f = 0; f < nb_fournisseurs; f++)
  {
    if (f == selected.id_fournisseur)
    {
      ping = 1;
    }
    else
    {
      ping = 0;
    }
    if (write(CTF[f][WRITE], &ping, sizeof(int)) == -1)
    {
      perror("READ");
      return 2;
    }
  }

  // fermer les tubes
  for (int f = 0; f < nb_fournisseurs; f++)
  {
    close(CTF[f][WRITE]);
  }
  close(FTC[READ]);

  return EXIT_SUCCESS;
}

int fournisseurs(int rang, int nb_fournisseurs)
{
  srand(time(NULL) ^ (getpid() << 16)); // https://stackoverflow.com/a/8623196
  devis devis;
  size_t vread;
  int ping;

  // orienter les tubes
  for (int f = 0; f < nb_fournisseurs; f++)
  {
    close(CTF[f][WRITE]);
  }
  close(FTC[READ]);

  // recevoir la demande de devis
  if (read(CTF[rang][READ], &devis, sizeof(devis)) == -1)
  {
    perror("READ CTF");
    return EXIT_FAILURE;
  }

  fprintf(stdout, "Fournisseur %d : j'ai reçu une demande de devis (ref %s, qu %d)\n", rang, devis.reference, devis.quantite);

  // calculer le devis [1, 100]€ par unité
  devis.prix = ((rand() % (100 + 1 - 1)) + 1) * devis.quantite;
  devis.id_fournisseur = rang;

  // envoyer la réponse
  if (write(FTC[WRITE], &devis, sizeof(devis)) == -1)
  {
    perror("WRITE FTC");
    return EXIT_FAILURE;
  }

  fprintf(stdout, "Fournisseur %d : j'ai envoyé un devis\n", rang);

  // débloquer le client
  close(FTC[WRITE]);

  // recevoir le ping
  if (read(CTF[rang][READ], &ping, sizeof(int)) == -1)
  {
    perror("READ CTF");
    return EXIT_FAILURE;
  }

  if (ping == 1)
  {
    fprintf(stdout, "Fournisseur %d : j'ai gagne le marche avec un devis de %d euros\n", rang, devis.prix);
  }
  else
  {
    fprintf(stdout, "Fournisseur %d : j'ai perdu le marche avec un devis de %d euros\n", rang, devis.prix);
  }

  for (int f = 0; f < nb_fournisseurs; f++)
  {
    close(CTF[f][READ]);;
  }

  return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
  int nb_fournisseurs;

  // verification des arguments du programme

  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s nb_fournisseurs\n", argv[0]);
    return EXIT_FAILURE;
  }

  nb_fournisseurs = atoi(argv[1]);

  // initialisation des tubes avant la creation des processus

  for (int i = 0; i < nb_fournisseurs; i++)
  {
    if (pipe(CTF[i]) == -1)
    {
      perror("TUBE");
      return EXIT_FAILURE;
    }
  }

  if (pipe(FTC) == -1)
  {
    perror("TUBE");
    return EXIT_FAILURE;
  }

  // creation des processus

  for (int rang = 0; rang < nb_fournisseurs; rang++)
  {
    switch (fork())
    {
    case -1:
      perror("fork");
      return EXIT_FAILURE;
    case 0:
      return fournisseurs(rang, nb_fournisseurs);
    default:
      break;
    }
  }

  return client(nb_fournisseurs);
}
