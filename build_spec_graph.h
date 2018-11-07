#ifndef BUILD_SPEC_GRAPH_H
#define BUILD_SPEC_GRAPH_H

#include "build_spec_repr.h"

typedef struct GraphNode{
	char* target;
	Command* cmd;
	struct GraphNode* children;
	int numChildren;
} GraphNode;

typedef struct {
	GraphNode* root;
} Graph;

GraphNode* getTarget(Graph* graph, char* target);

void addDepedency(GraphNode* target, char* dependency);

void addCommandToNode(GraphNode* target, char** command);

#endif
