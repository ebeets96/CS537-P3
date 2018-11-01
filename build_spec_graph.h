#ifndef BUILD_SPEC_GRAPH_H
#define BUILD_SPEC_GRAPH_H

#include "build_spec_repr.h"

typedef struct GraphNode{
	char* target;
	struct Node* commands;
	int numCommands;
	struct Node* children;
	int numChildren;
} GraphNode;

typedef struct {
	GraphNode* root;
} Graph;

struct Node {
	void* element;
	Node* next;
};

GraphNode* addTarget(Graph* graph, char* target);

void addDepedency(GraphNode* target, char* dependency);

void addCommand(GraphNode* target, char** command);

#endif
