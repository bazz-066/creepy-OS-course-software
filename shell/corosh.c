#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>

int parsecmd(char *line) {
	char *cmd, *tmp, **opts;
	int counter=0;

	cmd = strtok(line, " \t");
	if(!cmd) {
		return -1;
	}

	if((opts = malloc(11*sizeof(char *))) == NULL) {
		printf("Cannot allocate memory\n");
	}
	
	opts[counter] = malloc(strlen(cmd) + 1);
	strcpy(opts[counter++], cmd);

	
	while((tmp = strtok(NULL, " \t")) != NULL && counter < 10) {
		opts[counter] = malloc(strlen(tmp) + 1);
		strcpy(opts[counter], tmp);
		counter++; 
	}

	opts[counter] = NULL;

	if(strcmp(cmd, "exit") == 0) {
		exit(EXIT_SUCCESS);
	}
	else {
		pid_t pid = fork();
		if(pid == 0) {
			char path[255];
			
			strcpy(path, "/bin/");
			strcat(path, cmd);

			execv(path, opts);
			printf("error");
		}
		else if(pid > 0) {
			int status;
			waitpid(pid, &status, WUNTRACED); 
		}
	}
	
	return 0;
}

char **getuserhost() {
	char **data;

	if((data = malloc(2*sizeof(char *))) == NULL )
	{
		exit(EXIT_FAILURE);
	}
	
	data[0] = malloc(50 * sizeof(char));
	data[1] = malloc(50 * sizeof(char));
	
	struct passwd *p = getpwuid(getuid());
	if(p != NULL) {
		strncpy(data[0], p->pw_name, 49);
	}
	else {
		strcpy(data[0], "unknown");
	}

	if(gethostname(data[1], sizeof(data[1])) == 0) {
		return data;
	}
	else {
		strcpy(data[1], "unknown");
		return data;
	}
}

int readline() {
	char line[255], c;
	
	scanf("%[^\r\n]%c", line, &c);
	return parsecmd(line);	
}

int main(int argc, char **argv)
{
	while(1) {
		char **userdata;
		userdata = getuserhost();

		printf("coroshell : %s@%s > ", userdata[0], userdata[1]);
		int retval = readline();

		if(retval == -1)
		{
			exit(EXIT_FAILURE);
		}
	}
}
