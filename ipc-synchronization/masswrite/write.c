#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

#define DSTFILE "dstfile.txt"
#define BUFSIZE 100

void writemsg(FILE *fdst, char *src, char alphabet, int size) {
	int i;
	
	fprintf(fdst, "%s : ", src);
	for (i=1; i<=size; i++) {
		fprintf(fdst, "%c", alphabet);
	}
	
	fprintf(fdst, "\n");
}

void *thread1_write(void *arg) {
	int i, loop = rand() % 5 + 1;
	
	FILE *fdst = (FILE *) arg;
	
	for(i=1; i<=loop; i++) {
		writemsg(fdst, "Thread 1", 'a', 200);
	}
}

void *thread2_write(void *arg) {
	int i, loop = rand() % 5 + 1;
	
	FILE *fdst = (FILE *) arg;
	
	for(i=1; i<=loop; i++) {
		writemsg(fdst, "Thread 2", 'b', 200);
	}
}

int main(int argc, char *argv) {
	pthread_t t1, t2;
	int retval1, retval2;
	time_t t;
	
	FILE *fdst = fopen(DSTFILE, "w");
	srand((unsigned) time(&t));
	
	retval1 = pthread_create(&t1, NULL, thread1_write, (void *)fdst);
	retval2 = pthread_create(&t2, NULL, thread2_write, (void *)fdst);

	if (retval1 != 0 || retval2 != 0) {
		char errmsg[100];
		retval1 != 0 ? strerror_r(retval1, errmsg, sizeof(errmsg)-1):strerror_r(retval2, errmsg, sizeof(errmsg)-1);
		printf("Error : %s\n", errmsg);
		return -1;
	}

	retval1 = pthread_join(t1, NULL);
	retval2 = pthread_join(t2, NULL);

	if (retval1 != 0 || retval2 != 0) {
		char errmsg[100];
		retval1 != 0 ? strerror_r(retval1, errmsg, sizeof(errmsg)-1):strerror_r(retval2, errmsg, sizeof(errmsg)-1);
		printf("Error : %s\n", errmsg);
		return -1;
	}

	fclose(fdst);

	printf("Finished writing file.\n");
	return 0;
}
