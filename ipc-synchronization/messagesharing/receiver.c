#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUFSIZE 20

void main() {
	char *msg;
	
	while(1) {
		printf("%s\n", msg);
		sleep(1);
	}
}
