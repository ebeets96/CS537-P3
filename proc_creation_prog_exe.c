#include <stdlib.h>
#include <stdio.h>
#include "proc_creation_prog_exe.h"

void makeTarget(char* target, Node* graph) {
	GraphNode* tNode = findTarget(graph, target);

	if(tNode == NULL) {
		fprintf(stderr, "The specified target (%s) could not be found", target);
		exit(EXIT_FAILURE);
	}

	makeNode(tNode);
}

void makeNode(GraphNode* node) {
	Node* child = node->children;
	while(child != NULL) {
			GraphNode* childNode = (GraphNode*) child->element;
			makeNode(childNode);
			child = child->next;
	}

	runCommands(node->commands);
}
