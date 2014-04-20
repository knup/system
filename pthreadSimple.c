/* 
 * Simple use of C pthreads
 * @author anupkhadka
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_THREADS 5

void *taskCode(void *args) 
{
	int tid;
	tid = *((int *) args);
	printf("Hello World! Its me, thread %d\n", tid);
	return NULL;
}

int main(void) 
{
	pthread_t threads[NUM_THREADS];
	int threadArgs[NUM_THREADS];
	int rc,i;

	//create all threads
	for(i=0; i<NUM_THREADS; i++) {
		threadArgs[i] = i;
		printf("In main: creating thread %d\n", i);
		rc = pthread_create(&threads[i], NULL, taskCode, (void *) &threadArgs[i]);
		assert(0 == rc);
	}
	
	//wait for all threads to complete
	for(i=0; i<NUM_THREADS; i++) {
		rc = pthread_join(threads[i], NULL);
		assert(0 == rc);
	}

	exit(EXIT_SUCCESS);
}
