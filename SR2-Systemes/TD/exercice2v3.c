#include <semaphore.h>

#define N 10

struct msg
{
  int type;
  int value;
};

sem_t mutexP, mutexCP, empty, head[2];
struct msg buffer[N];
unsigned int ICP, ICV, nbCasesPleines;

void init()
{
  sem_init(&mutexP, 0, 1);
  sem_init(&mutexCP, 0, 1);
  sem_init(&empty, 0, N);   // semaphore, nombre de cases vides
  sem_init(&head[0], 0, 0); // semaphore, nombre de messages de type 0 dans le buffer
  sem_init(&head[1], 0, 0); // semaphore, nombre de messages de type 1 dans le buffer
  ICP = 0;                  // indice de la case à consommer (pleine)
  ICV = 0;                  // indice de la case à produire (vide)
  nbCasesPleines = 0;       // nombre de cases pleines
}

void producteur(struct msg m)
{
  sem_wait(&empty);
  sem_wait(&mutexP);

  buffer[ICV].type = m.type;
  buffer[ICV].value = m.value;
  ICV = (ICV + 1) % N;

  sem_wait(&mutexCP);
  if (++nbCasesPleines == 1)
    sem_post(&head[m.type]);
  sem_post(&mutexCP);
  sem_post(&mutexP);
}

void consommateur(struct msg *m)
{
  sem_wait(&head[m->type]);

  m->type = buffer[ICP].type;
  m->value = buffer[ICP].value;
  ICP = (ICP + 1) % N;

  sem_wait(&mutexCP);
  if (--nbCasesPleines > 0)
    sem_post(&head[buffer[ICP].type]);
  sem_post(&mutexCP);
  sem_post(&empty);
}