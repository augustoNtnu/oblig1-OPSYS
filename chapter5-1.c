#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


sem_t empty;            /* empty: How many empty buffer slots */
sem_t full;

int times[5] = {1,2,3,2,3,3};
/*
int t_idx1 = 1
int t_idx2 = 3
int t_idx3 = 5
/*
struct threadargs{
int id;
int sec;
int Signal[6];
};
static int AllThreads =5;
*/
void *processT (void *arg){
  int t_idx= *((int *) arg);
  int kill = 0;
  while (kill != 2) {

  sem_post(&full);
  sem_wait(&full);

  printf ("Prosess %d kjører\n",t_idx);

  sleep(times[t_idx]);

  printf("prosess %d kjørte i %d sekunder\n",t_idx,times[t_idx]);

  sem_post(&empty);
  kill++;
  }
}

void *processTo (void *arg)
{
    int t_idx3 = *((int *) arg);
  sem_wait(&empty);


  printf ("Prosess %d kjører\n",t_idx3);

  sleep(times[t_idx3]);

  printf("prosess %d kjørte i %d sekunder\n",t_idx3, times[t_idx3]);

+

}
int *d = malloc(sizeof(*i));
int *b = malloc(sizeof(*i));
int *c = malloc(sizeof(*i));
*c = 4;
*b = 2;
*d = 0;
int main(int argc, char *argv[])  {
pthread_t one,two,three;

  sem_init(&empty, 0, 0);
  sem_init(&full, 0, 3);


pthread_create(&one,NULL,processT,(void *) d);
pthread_create(&two,NULL,processT,(void *) b);
pthread_create(&three,NULL,processTo,(void *) c);








  /*
int i,j;
int status;
struct threadargs *targs[AllThreads];

for (i= 0; i<AllThreads;i++) {
  targs[i] = (struct threadargs*) malloc(sizeof(struct threadargs));
  for (j=0;j<AllThreads; j++) {
    targs[i]->id = j;
    targs[i]->Signal[j]=0;
    targs[i]->sec = 1;
  }
}
*/

/*
pthread_t threads[AllThreads];

for(i=0; i<AllThreads;i++) {
  status= pthread_create(&threads[i], NULL, process,targs[i]);

  if (status !=0) {
    printf("pthread fucked up, with code: %d\n",status );
  }
}
*/
return 0;
}
