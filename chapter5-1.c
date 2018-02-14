#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

struct threadargs{
int id;
int sec;
int Signal[6];
};
static int AllThreads =5;

void *process (void *arg){
   struct threadargs *targs=arg;
  printf ("Prosess %d kjører\n", targs->id);
  sleep(targs->sec);
  printf("prosess %d kjørte i %d sekunder\n",targs->id,targs->sec);
  pthread_exit(NULL);
}

int main(int argc, char *argv[])  {
int i,j;
int status;
struct threadargs *targs[AllThreads];

for (i= 0; i<AllThreads;i++) {
  targs[i] = (struct threadargs*) malloc(sizeof(struct threadargs));
  for (j=0;j<AllThreads; j++) {
    targs[i]->id = j;
    targs[i]->Signal[j]=0;
  }
}
targs[0]->sec = 1;
targs[1]->sec = 2;
targs[2]->sec = 3;
targs[3]->sec = 2;
targs[4]->sec = 3;
targs[5]->sec = 3;

pthread_t threads[AllThreads];

for(i=0; i<AllThreads;i++) {
  status= pthread_create(&threads[i], NULL, process,targs[i]);

  if (status !=0) {
    printf("pthread fucked up, with code: %d\n",status );
  }
}
return 0;
}
