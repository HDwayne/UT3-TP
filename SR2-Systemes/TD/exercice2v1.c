#include <semaphore.h>

#define N 10

struct msg
{
  int type;
  int value;
};

sem_t mutexC, mutexP, empty, full;
struct msg buffer[N];
int ICP, ICV;

void init()
{
  sem_init(&mutexC, 0, 1);
  sem_init(&mutexP, 0, 1);
  sem_init(&empty, 0, N); // nombre de cases vides
  sem_init(&full, 0, 0);  // nombre de cases pleines
  ICP = 0;
  ICV = 0;
}

void producteur(struct msg m)
{
  sem_wait(&empty);
  sem_wait(&mutexP);

  buffer[ICV].type = m.type;
  buffer[ICV].value = m.value;
  ICV = (ICV + 1) % N;

  sem_post(&mutexP);
  sem_post(&full);
}

void consommateur(struct msg *m)
{
  sem_wait(&full);
  sem_wait(&mutexC);

  m->type = buffer[ICP].type;
  m->value = buffer[ICP].value;
  ICP = (ICP + 1) % N;

  sem_post(&mutexC);
  sem_post(&empty);
}