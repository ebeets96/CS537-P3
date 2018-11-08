#include "build_spec_graph.h"
#include <stdlib.h>
#include <string.h>


Node* findTarget(Node* root, char* target);

GraphNode* addTarget(Node* graph, char* target) {
	// Get target if it exists in this graph
	Node* node = findTarget(graph, target);
	GraphNode* ret;
	// If it does not, create the target
	if (node == NULL) {
		node = malloc(sizeof(Node));
		node -> next = NULL;
		ret = node -> element;	
		ret = malloc(sizeof(GraphNode));
		ret  -> target = target;
		ret  -> children = NULL;
		ret  -> visited = 0;
	} else {
		ret = node -> element;
	}
	// Return the target
	return ret;
}

// Search through the graph for a target GraphNode
Node* findTarget(Node* root, char* target) {
	if (root == NULL) {
		// We are at the end of the graph, return the last node
		return root;
	}

	if (strcmp(((GraphNode*) (root -> element)) -> target, target) == 0) {
		return root;
	}

	return findTarget(root -> next, target);
}

// Add a new GraphNode as a dependency of target
void addDepedency(Node* graph, GraphNode* target, char* dependency) {
	// Check if dependency already exists
	Node* dependency_node = findTarget(graph, dependency);
	Node* child;
	GraphNode* dependency_graphnode;
	if (dependency_node != NULL) {
		dependency_graphnode = dependency_node -> element;
		child = target -> children;
        	while (child != NULL) {
                	child = child -> next;
        	}
		child = malloc(sizeof(Node));
		child -> element = dependency_graphnode;
		child -> next = NULL;
		return;
	}

	// If it does not, create it
	dependency_graphnode = addTarget(graph, dependency);
	child = target -> children;
	while (child != NULL) {
		child = child -> next;
	}
	child = malloc(sizeof(Node));
	child -> element = dependency_graphnode;
	child -> next = NULL;
	return;
}

// Add a new command to target
void addCommandToNode(GraphNode* target, char** newCommand) {
	Command* command = (target -> commands);
	while (command != NULL) {
		command = command -> next;
	}
	command = malloc(sizeof(Command));
	command -> cmd = newCommand;
	command -> next = NULL;
}

// Set visited to 0 for all GraphNodes
void clear(Node* root) {
	if (root == NULL) {
		return;
	}
	((GraphNode*) (root -> element)) -> visited = 0;
	clear(root -> next);
	return;
}

int internalCheckForCycles(Node* root) {
        ((GraphNode*) (root -> element)) -> visited++;
        if (((GraphNode*) (root -> element)) -> visited > 1) {
                return 1;
        }
        Node* child = ((GraphNode*) (root -> element)) -> children;
        while (child != NULL) {
                if (internalCheckForCycles(child) == 1) {
                        return 1;
                }
                child = child -> next;
        }
        return 0;
}

int checkForCycles(Node* root) {
	Node* curr = root;
	while (curr != NULL) {
		clear(root);
		Node* child = ((GraphNode*) (curr -> element)) -> children;
		if (internalCheckForCycles(child) == 1) {
			return 1;
		}
		curr = curr -> next;
	}
	return 0;
}
