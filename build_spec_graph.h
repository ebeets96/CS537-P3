#ifndef BUILD_SPEC_GRAPH_H
#define BUILD_SPEC_GRAPH_H

#include "build_spec_repr.h"

typedef struct GraphNode{
	char* target;
	Command* cmd;
	struct GraphNode* children;
} GraphNode;

typedef struct {
	GraphNode* root;
} Graph;

GraphNode* getTarget(char* target);

void addDepedency(Graph* graph, char* target, char* dependency);

#endif
