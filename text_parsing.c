#include "text_parsing.h"
#include "build_spec_graph.h"
#include "consts.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void parseFile(char* filename, Graph* g) {
	// Attempt to open file
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
        printf("Cannot open file.\n");
        exit(EXIT_FAILURE);
    }
	// Allocate string buffer for each line
	char* line = malloc(sizeof(char) * string_buffer);
	if(line == NULL) {
		printf("Could not allocate space for string buffer.\n");
        exit(EXIT_FAILURE);
	}

	// Read file until the end
	char* currentTarget;
	while(fgets(line, string_buffer, fp) != NULL) {
		if(line[0] == '\n'){
			continue; //Ignore blank lines
		} else if(line[0] == '\t') {

		} else {
			// Split the string by : character
			char* target = strtok(line, ":");
			char* dependencies = strtok(NULL, "s");
			char* errorCheck = strtok(NULL, "s");

			if(target == NULL || dependencies == NULL || errorCheck != NULL) {
				printf("This line was not a valid target\n");
				continue; // Skip processing this line
			}

			// Add Target to the Graph
			GraphNode* gn = addTarget(g, target);

			//convert dependencies to an array of strings
			char* dependency = strtok(dependencies, " ");

			while(dependency != NULL) {
				addDepedency(gn, dependency);
				dependency = strtok(NULL, " ");
			}
		}
	}

	free(line);
}
