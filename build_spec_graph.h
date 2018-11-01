#ifndef BUILD_SPEC_GRAPH_H
#define BUILD_SPEC_GRAPH_H

#include "build_spec_repr.h"

typedef struct Node {
        void* element;
        struct Node* next;
} Node;

typedef struct GraphNode{
	char* target;
	Command* commands;
	Node* children;
} GraphNode;

typedef struct {
	GraphNode* root;
} Graph;

GraphNode* addTarget(Graph* graph, char* target);

void addDepedency(GraphNode* target, char* dependency);

void addCommand(GraphNode* target, char** command);

#endif
