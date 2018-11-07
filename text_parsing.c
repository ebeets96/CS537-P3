#include "text_parsing.h"
#include "build_spec_graph.h"
#include "consts.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* parseFile(FILE* fp, Graph* g) {
	// Allocate string buffer for each line
	char* line = malloc(sizeof(char) * string_buffer);
	if(line == NULL) {
		printf("Could not allocate space for string buffer.\n");
        exit(EXIT_FAILURE);
	}

	// Read file until the end
	char* firstTarget;
	char* currentTarget;
	GraphNode* gn;
	while(fgets(line, string_buffer, fp) != NULL) {
		if(line[0] == '\n'){
			continue; //Ignore blank lines
		} else if(line[0] == '\t') {
			if(gn == NULL) {
				printf("A command line was encountered before a target.\n");
		        exit(EXIT_FAILURE);
			}

			char* curr = strtok(line, " ");
			char** command;

			// Create an array of the command
			int size = 0;
			while(curr != NULL) {
				command = realloc (command, sizeof (char*) * ++size);

				if(command == NULL) {
					printf("Space could not be reallocated for commands.\n");
			        exit(EXIT_FAILURE);
				}

				command[size-1] = curr;

				curr = strtok(NULL, " ");
			}

			// Add to the current GraphNode
			addCommandToNode(gn, command);

		} else {
			// Split the string by : character
			char* target = strtok(line, ":");
			char* dependencies = strtok(NULL, ":");
			char* errorCheck = strtok(NULL, ":");

			if(target == NULL || dependencies == NULL || errorCheck != NULL) {
				printf("This line was not a valid target\n");
				continue; // Skip processing this line
			}

			// Save the name of the first target to return
			if(firstTarget == NULL) {
				firstTarget = target;
			}

			// Add Target to the Graph
			gn = getTarget(g, target);

			//convert dependencies to an array of strings
			char* dependency = strtok(dependencies, " ");

			while(dependency != NULL) {
				addDepedency(gn, dependency);
				dependency = strtok(NULL, " ");
			}
		}
	}

	free(line);
	return firstTarget;
}
