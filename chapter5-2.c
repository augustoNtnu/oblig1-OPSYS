#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     /* usleep */
#include <pthread.h>
#include <semaphore.h>

#define SHARED 0  /* process-sharing if !=0, thread-sharing if =0*/
#define BUF_SIZE 20
#define MAX_MOD 100000
#define NUM_ITER 200

void* Producer(void *); /* Producer thread */
void* Consumer(void *); /* Consumer thread */

sem_t empty;            /* empty: How many empty buffer slots */
sem_t full;             /* full: How many full buffer slots */
pthread_mutex_t mutex;  /* mutex: Mutex lock */

int g_data[BUF_SIZE];   /* shared finite buffer  */
int g_idx;              /* index to next available slot in buffer,
                           remember that globals are set to zero
                           according to C standard, so no init needed  */

int main(int argc, char *argv[]) {
	pthread_t pid, cid;

int *i = malloc(sizeof(*i));
*i =  strtol(argv[1], NULL, 10);
	// Initialie the semaphores
	sem_init(&empty, SHARED, BUF_SIZE);
	sem_init(&full, SHARED, 0);
	// Initialize the mutex
	pthread_mutex_init(&mutex,0);

	// Create the threads
	printf("main started\n");
	pthread_create(&pid, NULL, Producer,(void *) i);
	pthread_create(&cid, NULL, Consumer,(void *) i);

	// And wait for them to finish.
	pthread_join(pid, NULL);
	pthread_join(cid, NULL);
	printf("main done\n");

	return 0;
}


void *Producer(void *arg) {
	int i=0, j;
  int a = *((int *) arg);
	while(i < a) {
		// pretend to generate an item by a random wait
		usleep(rand()%MAX_MOD);

		// Wait for at least one empty slot
		sem_wait(&empty);
		// Wait for exclusive access to the buffer
		pthread_mutex_lock(&mutex);

		// Check if there is content there already. If so, print
    // a warning and exit.
		if(g_data[g_idx] == 1) {
			printf("Producer overwrites!, idx er %d\n",g_idx);
			exit(0);
		}

		// Fill buffer with "data" (ie: 1) and increase the index.
		g_data[g_idx]=1;
		g_idx++;

		// Print buffer status.
		j=0; printf("(Producer%d, idx is %d):  ",i,g_idx);
		while(j < g_idx) { j++; printf("="); } printf("\n");

		// Leave region with exlusive access
		pthread_mutex_unlock(&mutex);
		// Increase the counter of full bufferslots.
		sem_post(&full);

		i++;
	}

	return 0;
}


void *Consumer(void *arg) {
	int i=0, j;
int a = *((int *) arg);
	while(i < a) {
		// Wait a random amount of time, simulating consuming of an item.
		usleep(rand()%MAX_MOD);

		// Wait for at least one slot to be full
		sem_wait(&full);
		// Wait for exclusive access to the buffers
		pthread_mutex_lock(&mutex);

		// Checkt that the buffer actually contains some data
    // at the current slot.
		if(g_data[g_idx-1] == 0) {
			printf("Consumes nothing!, idx er %d\n",g_idx);
			exit(0);
		}

		// Remove the data from the buffer (ie: Set it to 0)
		g_data[g_idx-1]=0;
		g_idx--;

		// Print the current buffer status
		j=0; printf("(Consumer%d, idx is %d): ",i,g_idx);
		while(j < g_idx) { j++; printf("="); } printf("\n");

		// Leave region with exclusive access
		pthread_mutex_unlock(&mutex);
		// Increase the counter of empty slots.
		sem_post(&empty);

		i++;
	}

	return 0;

}
