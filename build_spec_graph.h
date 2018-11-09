/*
 * Jack David
 * Eric Beets
 */

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
	int visited;
} GraphNode;

Node* findTarget(Node* root, char* target);

Node* addTarget(Node* graph, char* target);

void addDepedency(Node* graph, Node* target, char* dependency);

void addCommandToNode(GraphNode* target, char** command);

int checkForCycles(Node* n);

Node* createNewLastNode(Node* root);

void printNodes(Node* root);

#endif
