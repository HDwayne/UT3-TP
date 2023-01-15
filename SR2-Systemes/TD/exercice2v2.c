#include <semaphore.h>

#define N 10

struct msg
{
  int type;
  int value;
};

sem_t mutexC, mutexP, empty, full, T[2];
struct msg buffer[N];
int ICP, ICV;

void init()
{
  sem_init(&mutexC, 0, 1);
  sem_init(&mutexP, 0, 1);
  sem_init(&empty, 0, N); // nombre de cases vides
  sem_init(&full, 0, 0); // nombre de cases pleines
  sem_init(&T[0], 0, 1); // type 0, start here
  sem_init(&T[1], 0, 0);
  ICP = 0;
  ICV = 0;
}

void producteur(struct msg m)
{
  sem_wait(&empty);
  sem_wait(&T[m.type]);
  sem_wait(&mutexP);

  buffer[ICV].type = m.type;
  buffer[ICV].value = m.value;
  ICV = (ICV + 1) % N;
  
  sem_post(&mutexP);
  sem_post(&full);
  sem_post(&T[m.type == 0 ? 1 : 0]);
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