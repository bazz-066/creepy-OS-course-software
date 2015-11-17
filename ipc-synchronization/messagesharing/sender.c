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
	char msg[BUFSIZE+1];
	
	while(1) {
		printf("Enter your message (Type 'END' to quit) : ");
		scanf("%s", msg);
		
		if (strncmp(msg, "END", BUFSIZE) == 0) {
			printf("Bye\n");
			break;
		}
	}
}
