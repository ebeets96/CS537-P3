#include <stdio.h>
#include <stdlib.h>
#include "build_spec_graph.h"
#include "text_parsing.h"
#include "proc_creation_prog_exe.h"
#include "consts.h"

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
	Node* graph = malloc(sizeof(Node*));

	char* firstTarget = parseFile(file, graph);

	// Check the dependency graph for cycles
	if (checkForCycles(graph) == 1) {
		fprintf(stderr, "Cycle in dependency graph\n");
		return -1;
	}

	// If a target was specified, make that target, else make the first target in the makefile
	if (argc == 2) {
		makeTarget(argv[1], graph);
	} else {
		makeTarget(firstTarget, graph);
	}

	return 0;
}
