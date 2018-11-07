#include "build_spec_graph.h"
#include <stdlib.h>
#include <string.h>

GraphNode* findTarget(GraphNode* root, char* target);

GraphNode* addTarget(Node* graph, char* target) {
	if (graph == NULL) {
		// Graph is empty, set root as target
		graph = malloc(sizeof(Node));
		graph -> element = malloc(sizeof(GraphNode));
		graph -> next = NULL;
		GraphNode* new = graph -> element;
		new -> target = target;
		new -> children = NULL;
		return new;
	} 

	GraphNode* root = graph -> element;

	// Get target if it exists in this graph
	GraphNode* ret = findTarget(root, target);
	// If it does not,
	if (ret == NULL) {
		// If root points to another graph, check the next graph for the target
		if (graph -> next != NULL) {
			return addTarget(graph -> next, target);
		}
		// Else, create the target
		graph -> next = malloc(sizeof(Node));
		graph -> next -> element = malloc(sizeof(GraphNode));
		ret = graph -> next -> element;
		ret -> target = target;
		ret -> children = NULL;
	}
	// Return the target
	return ret;
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
void addDepedency(Node* graph, GraphNode* target, char* dependency) {
	// Check if dependency already exists
	GraphNode* target_graphNode = findTarget(graph, dependency);
	if (target_graphNode != NULL) {
		Node* child = target -> children;
        	while (child != NULL) {
                child = child -> next;
        	}
		child = malloc(sizeof(Node));
		child -> element = target;
		child -> next = NULL;
		return;
	}

	// If it does not, create it
	Node* child = target -> children;
	while (child != NULL) {
		child = child -> next;
	}
	child = malloc(sizeof(Node));
	GraphNode* dependency_graphnode = child -> element;
	dependency_graphnode = malloc(sizeof(GraphNode));
	dependency_graphnode -> target = dependency;
	dependency_graphnode -> children = NULL;
}

// Add a new command to target
void addCommand(GraphNode* target, char** newCommand) {
	Command* command = (target -> commands);
	while (command != NULL) {
		command = command -> next;
	}
	command = malloc(sizeof(Command));
	command -> cmd = newCommand;
	command -> next = NULL;
}
