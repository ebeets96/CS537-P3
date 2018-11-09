#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "proc_creation_prog_exe.h"

void makeTarget(char* target, Node* graph) {
	GraphNode* tNode = findTarget(graph, target)->element;

	if(tNode == NULL) {
		fprintf(stderr, "The specified target (%s) could not be found", target);
		exit(EXIT_FAILURE);
	}

	makeNode(tNode);
}

// 1 if it made anything
// 0 if it did not
int makeNode(GraphNode* node) {
	Node* child = node->children;
	int dependenciesUpdate = 0;
	while(child != NULL) {
			GraphNode* childNode = (GraphNode*) child->element;
			dependenciesUpdate += makeNode(childNode);
			child = child->next;
	}

	// If associated file has been updated, run commands
	// This is a leaf node

	struct stat *statbuf = malloc(sizeof(stat));
	int statSuccess = stat(node->target, statbuf);

	if(statSuccess == 0) {
		//Target is a file
		printf("It's a file\n");
	} else {
		//Target is not a file
		printf("It's not a file\n");
		runCommands(node->commands);
	}

	return 1;
}
