#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define SRCFILE "1stfile.txt"
#define DSTFILE "2ndfile.txt"

char buf[100];
int len;

void *thread1_copy(void *arg) {
	FILE *fsrc;
	
	fsrc = fopen(SRCFILE, "r");
	
	if (fsrc == NULL) {
		printf("Cannot open file\n");
		return;
	}
	
	while(!feof(fsrc)) {
		len = fread(buf, sizeof(char), 100, fsrc);
		sleep(1);
	}
	
	buf[0] = '\0';
	fclose(fsrc);
}

void *thread2_copy(void *arg) {
	FILE *fdst;
	int retval;

	fdst = fopen(DSTFILE, "w");
	
	if (fdst == NULL) {
		printf("Cannot open file\n");
		return;
	}
	
	while(buf[0] != '\0') {
		retval = fwrite(buf, sizeof(char), len, fdst);
		sleep(1);
	}
	
	fclose(fdst);
}

int main(int argc, char *argv) {
	pthread_t t1, t2;
	int retval1, retval2;
	time_t t;
	
	srand((unsigned) time(&t));

	retval1 = pthread_create(&t1, NULL, thread1_copy, NULL);
	retval2 = pthread_create(&t2, NULL, thread2_copy, NULL);

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

	printf("Finished copying file.\n");
	return 0;
}
