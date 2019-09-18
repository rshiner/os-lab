#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int SharedVariable = 0;
pthread_barrier_t barr;
pthread_mutex_t mutex;

void SimpleThread(int which) {
	int num, val;
	for(num = 0; num < 20; num++){
		if(random() > RAND_MAX / 2)
			usleep(10); 
	pthread_mutex_lock(&mutex);

	val = SharedVariable;
		printf("*** thread %d sees value %d\n", which, val);
		SharedVariable = val + 1;
	pthread_mutex_unlock(&mutex);
		}
	int rc = pthread_barrier_wait(&barr);
	if(rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD)
		{
			printf("Could not wait on barrier\n");
			exit(-1);
		}
	val = SharedVariable;
	printf("Thread %d sees final value %d\n", which, val);
}




int main(int argc, char *argv[]){
		
	int console = 0;
	if(pthread_mutex_init(&mutex, NULL)){
		printf("Unable to initialize a mutex\n");
		return -1;
	}

	printf("Enter Number of Threads ");
	scanf("%d", &console);
	printf("\n");
	pthread_t id[console];
	if(pthread_barrier_init(&barr, NULL, console)){
		printf("Could not create a barrier\n");
		return -1;
	}

	int i = 0;
	for(i = 0; i < console; i++){

	pthread_create(&id[i], NULL, &SimpleThread, i);
	}
	for(i = 0; i < console; i++){

	pthread_join(id[i], NULL);
	}	
	
}
