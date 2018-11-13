/*
 * Jack David
 * Eric Beets
 */

#include "text_parsing.h"
#include "build_spec_graph.h"
#include "consts.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* parseFile(FILE* fp, Node* g) {
	// Allocate string buffer for each line
	char* line = malloc(sizeof(char) * string_buffer);
	char* line_copy = malloc(sizeof(char) * string_buffer);
	if(line == NULL) {
		printf("Could not allocate space for string buffer.\n");
		exit(EXIT_FAILURE);
	}

	// Read file until the end
	char* firstTarget = NULL;
	Node* gn = NULL;
	int line_number = 1;
	while(fgets(line, string_buffer, fp) != NULL) {
		if(line[0] == '\n'){
			continue; //Ignore blank lines
		}
		//Remove new lines
		line[strcspn(line, "\n")] = 0;

		//Copy line to line_copy in case that it needs to be printed
		//since strtok ruins the original string
		strncpy(line_copy, line, string_buffer);

		if(line[0] == '\t') {
			if(gn == NULL) {
				printf("A command line was encountered before a target.\n");
		        exit(EXIT_FAILURE);
			}
			line++;
			char* curr = strtok(line, " ");
			char** command = malloc(sizeof (char*));
			if(command == NULL) {
				printf("Space could not be reallocated for commands.\n");
				exit(EXIT_FAILURE);
			}

			// Create an array of the command
			int size = 0;
			while (1) {
				command = realloc (command, sizeof (char*) * ++size);

				if(command == NULL) {
					printf("Space could not be reallocated for commands.\n");
			        exit(EXIT_FAILURE);
				}

				command[size-1] = curr;

				// Ensure that a NULL is added to end of list
				if(curr == NULL) {
					break;
				} else {
					curr = strtok(NULL, " ");
				}
			}

			// Add to the current GraphNode
			addCommandToNode(gn->element, command);

		} else if (strstr(line, ":") != NULL){
			// Split the string by : character
			char* target = strtok(line, ":");
			char* dependencies = strtok(NULL, ":");
			char* errorCheck = strtok(NULL, ":"); // Check if there's a second colon

			if(target == NULL || errorCheck != NULL) {
				fprintf(stderr, "%i: Invalid line: %s\n", line_number, line_copy);
				exit(EXIT_FAILURE);
			}

			// Save the name of the first target to return
			if(firstTarget == NULL) {
				firstTarget = target;
			}

			// Add Target to the Graph
			gn = addTarget(g, target);

			//convert dependencies to an array of strings
			char* dependency = strtok(dependencies, " ");

			while(dependency != NULL && dependency[0] != '\n') {
				addDepedency(g, gn, dependency);
				dependency = strtok(NULL, " ");
			}
		} else {
			fprintf(stderr, "%i: Invalid line: %s\n", line_number, line_copy);
			exit(EXIT_FAILURE);
		}

		// Allocate string buffer for each line
		line = malloc(sizeof(char) * string_buffer);
		if(line == NULL) {
			printf("Could not allocate space for string buffer.\n");
			exit(EXIT_FAILURE);
		}
		line_number++;
	}

	free(line_copy);
	free(line);
	return firstTarget;
}
