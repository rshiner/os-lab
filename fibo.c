#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

pthread_barrier_t barr;
pthread_mutex_t mutex;
int fib_seq[47];
int fib_num = 2;
void runner(int arg);

int main(int argc, char *argv[])
{
	int k = 0;
	for(k = 0; argv[1][k] != 0; k++)
	{
		if(!isdigit(argv[1][k]))
		{ 
			printf ("Please enter a digit between 0 and 47\n");
			exit(0);
		}
	}
	int num_thread = atoi(argv[1]);
	int i, err;

	fib_seq[0] = 0;
	fib_seq[1] = 1;
	
	
	if(argc != 2) {
		printf("invalid input\n");
		exit(0);
	}
	for(k = 0; k < num_thread; k++)
	{
		if(num_thread < 0 || num_thread > 47)
		{
			printf("Please enter a whole number from 0 to 47\n");
			exit(0);
		}
	}
	/* initializes mutex */
	if(pthread_mutex_init(&mutex, NULL)){
		printf("Unable to initialize a mutex\n");
		return -1;
	}

	/* initializes barrier */
	if(pthread_barrier_init(&barr, NULL, num_thread)){
		printf("Could not create barrier\n");
		return -1;
	}
	
	pthread_t threads[num_thread];
	int thread_ids[num_thread];

	int i = 0;
	for(i = 0; i < num_thread; i++)
	{
		pthread_create(&thread_ids[i], NULL, &runner, i);
	}

	for(i = 0; i < num_thread; i++)
	{
	pthread_join(thread_ids[i], NULL);
	}

	for(i =0; i < num_thread; i++) {
		printf("%d", fib_seq[i]);
		if(i != num_thread - 1){
		printf(",");
		}
		else
		printf("\n");
	}
	return 0;
}

/* The thread will begin control in this function */
void runner(int arg)
{
	pthread_mutex_lock(&mutex);
	if(fib_num >1)
	{
		fib_seq[fib_num] = (fib_seq[fib_num - 1] + fib_seq[fib_num - 2]);
		fib_num++;
	}
	pthread_mutex_unlock(&mutex);

	int rc = pthread_barrier_wait(&barr);
	if(rc !=0 && rc != PTHREAD_BARRIER_SERIAL_THREAD)
		{
			printf("Could not wait on barrier\n");
			exit(-1);
		}
	return NULL;
}
