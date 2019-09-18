#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int SharedVariable = 0;

void SimpleThread(int which) {
	int num, val;
	for(num = 0; num < 20; num++){
		if(random() > RAND_MAX / 2)
			usleep(10); 
	
	val = SharedVariable;
		printf("*** thread %d sees value %d\n", which, val);
		SharedVariable = val + 1;
		}
	val = SharedVariable;
	printf("Thread %d sees final value %d\n", which, val);
}




int main(int argc, char *argv[]){
		
	int console = 0;
	
	printf("Enter Number of Threads ");
	scanf("%d", &console);
	printf("\n");
	pthread_t id[console];
	
	int i = 0;
	for(i = 0; i < console; i++){

	pthread_create(&id[i], NULL, &SimpleThread, i);
	}
	for(i = 0; i < console; i++){

	pthread_join(id[i], NULL);
	}	
	
}
