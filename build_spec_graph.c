#include "build_spec_graph.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Node* addTarget(Node* graph, char* target) {
	// Get target if it exists in this graph
	Node* graphnode = findTarget(graph, target);

	if(graphnode != NULL) {
		return graphnode;
	}

	GraphNode* newNode = malloc(sizeof(GraphNode));
	if(newNode == NULL) {
		fprintf(stderr, "Couldn't allocate space for GraphNode.\n");
	}
	newNode -> target = target;
	newNode -> commands = NULL;
	newNode -> children = NULL;
	newNode -> visited = 0;

	if(graph->element == NULL) {
		graphnode = graph;
	} else {
		graphnode = createNewLastNode(graph);
	}

	graphnode->element = newNode;
	
	// Return the target
	return graphnode;
}

Node* createNewLastNode(Node* root) {
	while (root -> next != NULL) {
		root = root -> next;
	}
	root -> next = malloc(sizeof(Node));
	root -> next -> next = NULL;
	root -> next -> element = NULL;
	return root -> next;
}

// Search through the graph for a target GraphNode
// If found, return the GraphNode, else return NULL
Node* findTarget(Node* root, char* target) {

	if (root == NULL || root->element == NULL) {
		// We have reached the end of the graph
		return NULL;
	}

	GraphNode* graphnode = root -> element;
	if (strcmp(graphnode -> target, target) == 0) {
		// We have found the target
		return root;
	}

	if (root -> next == NULL) {
		// We have reached the end of the graph
		return NULL;
	}

	return findTarget(root -> next, target);
}

// Add a new GraphNode as a dependency of target
void addDepedency(Node* graph, Node* target, char* dependency) {
	Node* dependency_graphnode = findTarget(graph, dependency);
	// If dependency already exists, add it as a child of target
	if (dependency_graphnode == NULL) {
		dependency_graphnode = addTarget(graph, dependency);
	}


	GraphNode* targetGraphNode = target->element;


	if(targetGraphNode->children == NULL) {
		targetGraphNode->children = malloc(sizeof(Node));
		targetGraphNode->children->element = dependency_graphnode->element;
		targetGraphNode->children->next = NULL;
	} else {
		Node* lastDependency = targetGraphNode->children;
		//Loop through to last dependency
		while (lastDependency->next != NULL) {
			lastDependency = lastDependency->next;
		}
		//Set new Node as last dependency
		lastDependency->next = malloc(sizeof(Node));
		lastDependency->next->next = NULL;
		lastDependency->next->element = dependency_graphnode->element;
	}
}

// Add a new command to target
void addCommandToNode(GraphNode* target, char** newCommand) {
	if(target->commands == NULL) {
		target->commands = malloc(sizeof(Command));
		target->commands->cmd = newCommand;
		target->commands->next = NULL;
	} else {
		Command* command = target->commands;
		while (command->next != NULL) {
			command = command -> next;
		}
		command->next = malloc(sizeof(Command));
		command->next->cmd = newCommand;
		command->next->next = NULL;
	}
}

// Set visited to 0 for all GraphNodes
void clear(Node* root) {
	if (root == NULL || root->element == NULL) {
		return;
	}
	GraphNode* currNode = root->element;
	currNode->visited = 0;
	clear(root->next);
}

int internalCheckForCycles(Node* root) {
	if(root == NULL || root->element == NULL) {
		return 0;
	}

	GraphNode* curr  = root -> element;
	curr->visited++;

	if (curr->visited > 1) {
		return 1;
	}

	Node* child = curr->children;
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
		if (internalCheckForCycles(curr) == 1) {
			return 1;
		}
		curr = curr -> next;
	}
	return 0;
}

void printNodes(Node* root) {
	if (root == NULL || root->element == NULL) {
		return;
	}
	GraphNode* currNode = root->element;
	printf("%s\n", currNode->target);
	printNodes(root->next);
}
