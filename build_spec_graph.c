#include "build_spec_graph.h"

GraphNode* addTarget(Graph* graph, char*, target) {
	GraphNode* root = graph -> root;
	
	if (root = NULL) {
		// Graph is empty, set root as target
		root = malloc(sizeof(GraphNode));
		root -> target = target;
		return root;
	}

	// Else, find target
	return findTarget(root, target);
}

// Search through the graph for a target GraphNode
GraphNode* findTarget(GraphNode* root, char* target) {
	if (strcmp(root -> target, target) == 0) {
		return root;
	}
	Node* child = root -> children;
	while (child != NULL) {
		GraphNode* child_graphnode = findTarget(child -> element, target);
		if (child_graphnode != NULL) {
			return child_graphnode;
		}
		child = child -> next;
	}
	return NULL;
}

// Add a new GraphNode as a dependency of target 
void addDepedency(GraphNode* target, char* dependency) {
	Node* child = target -> children;
	while (child != NULL) {
		child = child -> next;
	}
	child = malloc(sizeof(Node));
	GraphNode* dependency_graphnode = child -> element;
	dependency_graphnode = malloc(sizeof(GraphNode));
	dependency_graphnode -> target = dependency;
}

// Add a new command to target
void addCommand(GraphNode* target, char** newCommand) {
	Command* command = target -> commands;
	while (command != NULL) {
		command = command -> next;
	}
	command = malloc(sizeof(Command));
	command -> cmd = newCommand;
}
