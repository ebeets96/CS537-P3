/*
 * Jack David
 * Eric Beets
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "build_spec_repr.h"

void runCommands(Command* c) {
	Command* currCmd = c;
	while(currCmd != NULL) {
		// printf("run %s\n", *(currCmd->cmd));
		char** printableCmd = currCmd->cmd;
		while ( *printableCmd ) printf( "%s ", *printableCmd++ );
		printf("\n");

		pid_t childPID = fork();
		if(childPID < 0) {
			fprintf(stderr, "Could not fork to run commands.\n");
			exit(EXIT_FAILURE);
		} else if (childPID == 0) {
			// Child
			// Print commands
			char** args = currCmd->cmd;

			execvp(*args, args);
			//return if the execvp failed
			exit(EXIT_FAILURE);
		} else {
			//Parent
			int child_status;
			waitpid(childPID, &child_status, 0);
			if ( WIFEXITED(child_status) ) {
				int exit_status = WEXITSTATUS(child_status);
				if(exit_status == EXIT_FAILURE) {
					fprintf(stderr, "The command was unable to run\n");
					exit(EXIT_FAILURE);
				}
			}
			currCmd = currCmd->next;
		}
	}
}
