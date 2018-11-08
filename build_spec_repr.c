#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "build_spec_repr.h"

void runCommands(Command* c) {
	Command* currCmd = c;
	while(currCmd != NULL) {
		pid_t childPID = fork();
		if(childPID < 0) {
			fprintf(stderr, "Could not fork to run commands.\n");
			exit(EXIT_FAILURE);
		} else if (childPID == 0) {
			//Child
			//Print commands
			char** printPointer = currCmd->cmd;
			while(*printPointer != NULL) {
				printf("%s\n", *printPointer);
				printPointer++;
			}
			char* filename = currCmd->cmd[0];
			char** args = &currCmd->cmd[1];
			int exec = execvp(filename, args);

			if(exec == -1) {
				exit(EXIT_FAILURE);
			} else {
				exit(EXIT_SUCCESS);
			}
		} else {
			//Parent
			int status;
			waitpid(childPID, &status, 0);

		}

		currCmd = c->next;
	}
}
