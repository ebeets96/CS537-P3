/*
 * Jack David
 * Eric Beets
 */

#include <stdio.h>
#include <stdlib.h>
#include "build_spec_graph.h"
#include "text_parsing.h"
#include "proc_creation_prog_exe.h"
#include "consts.h"

const int string_buffer = 1024;
const char* makefile1 = "makefile";
const char* makefile2 = "Makefile";

int main(int argc, char **argv) {
	// Check that there are 1 or 2 arguments
	if (argc > 2) {
		fprintf(stderr, "Too many arguments\n");
		return -1;
	}

	// Get makefile
	FILE* file;
	file = fopen(makefile1, "r");
	if (file == NULL) {
		file = fopen(makefile2, "r");
	}
	if (file == NULL) {
		fprintf(stderr, "No file named 'makefile' or 'Makefile' found.\n");
		return -1;
	}

	// Parse the file
	Node* graph = malloc(sizeof(Node));
	graph->element = NULL;
	graph->next = NULL;

	char* firstTarget = parseFile(file, graph);

	// printNodes(graph);

	// Check the dependency graph for cycles
	if (checkForCycles(graph) == 1) {
		fprintf(stderr, "The makefile contained a cycle.\n");
		exit(EXIT_FAILURE);
	}

	// If a target was specified, make that target, else make the first target in the makefile
	char* target;
	if (argc == 2) {
		target = argv[1];
	} else {
		target = firstTarget;
	}

	if(!makeTarget(target, graph)) {
		printf("make: '%s' is up to date.\n", target);

	}

	return 0;
}
