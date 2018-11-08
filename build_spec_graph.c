#include "build_spec_graph.h"
#include <stdlib.h>
#include <string.h>

GraphNode* findTarget(Node* root, char* target);
Node* createNewLastNode(Node* root);

GraphNode* addTarget(Node* graph, char* target) {
	// Get target if it exists in this graph
	GraphNode* graphnode = findTarget(graph, target);
	// If it does not, create the target
	if (graphnode == NULL) {	
		graphnode = malloc(sizeof(GraphNode));
		createNewLastNode(graph) -> element = graphnode;
		graphnode -> target = target;
		graphnode -> children = NULL;
		graphnode -> visited = 0;
	} 
	// Return the target
	return graphnode;
}

Node* createNewLastNode(Node* root) {
	while (root -> next != NULL) {
		root = root -> next;
	}
	root -> next = malloc(sizeof(Node));
	root -> next -> next = NULL;
	return root -> next;
}

// Search through the graph for a target GraphNode
// If found, return the GraphNode, else return NULL
GraphNode* findTarget(Node* root, char* target) {
	GraphNode* graphnode = root -> element;
	if (graphnode == NULL) {
		// We have reached the end of the graph
		return NULL;
	}

	if (strcmp(graphnode -> target, target) == 0) {
		// We have found the target
		return graphnode;
	}

	if (root -> next == NULL) {
                // We have reached the end of the graph
                return NULL;
        }

	return findTarget(root -> next, target);
}

// Add a new GraphNode as a dependency of target
void addDepedency(Node* graph, GraphNode* target, char* dependency) {
	GraphNode* dependency_graphnode = findTarget(graph, dependency);
	Node* child;

	// If dependency already exists, add it as a child of target
	if (dependency_graphnode != NULL) {
		child = target -> children;
                while (child -> next != NULL) {
                	child = child -> next;
                }
                child -> next = malloc(sizeof(Node));
		child = child -> next;
                child -> element = dependency_graphnode;
                child -> next = NULL;
                return;
	}

	// If dependency does not exist, create it and then add it as a child of target
	dependency_graphnode = addTarget(graph, dependency);
	child = target -> children;
        while (child -> next != NULL) {
        	child = child -> next;
        }
        child -> next = malloc(sizeof(Node));
        child = child -> next;
        child -> element = dependency_graphnode;
        child -> next = NULL;
        return;
}

// Add a new command to target
void addCommandToNode(GraphNode* target, char** newCommand) {
	Command* command = (target -> commands);
	while (command -> next != NULL) {
		command = command -> next;
	}
	command -> next = malloc(sizeof(Command));
	command = command -> next;
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
