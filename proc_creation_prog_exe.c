#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "proc_creation_prog_exe.h"

void makeTarget(char* target, Node* graph) {
	GraphNode* tNode = findTarget(graph, target)->element;

	if(tNode == NULL) {
		fprintf(stderr, "The specified target (%s) could not be found", target);
		exit(EXIT_FAILURE);
	}

	makeNode(tNode);
}


void makeNode(GraphNode* node) {
	struct stat *statbuf = malloc(sizeof(struct stat));
	int statSuccess;

	Node* child = node->children;
	// struct timespec *most_recently_modified_depency = malloc(sizeof(struct timespec));

	while(child != NULL) {
			// Make the dependency
			GraphNode* childNode = (GraphNode*) child->element;
			makeNode(childNode);

			// Check if a file with the name of the dependency targe exists
			// and if it is the most recently modified dependency
			char* dependency_name = childNode->target;
			// statSuccess = stat(dependency_name, statbuf);
			if(statSuccess == 0) {
				//Dependency is a file
				// if(timeGreaterThan(&statbuf->st_mtim, most_recently_modified_depency)) {
				// 	printf("The dependency, %s, was greater.\n", dependency_name);
				// 	most_recently_modified_depency->tv_sec = statbuf->st_mtim.tv_sec;
				// 	most_recently_modified_depency->tv_nsec = statbuf->st_mtim.tv_nsec;
				// } else {
				// 	printf("The dependency, %s, was not greater.\n", dependency_name);
				// }
			} else {
				printf("Could not open %s\n", dependency_name);
			}

			child = child->next;
	}

	// If associated file has been updated, run commands
	// This is a leaf node
	statSuccess = stat(node->target, statbuf);
	//Check if target modified time is before dependency modified time
	//Build target if it is

	//printf("The most recently modified dependency was %li\n", most_recently_modified_depency.tv_sec);

	if(statSuccess == 0) {
		//Target is a file
		printf("%s is a file\n", node->target);
		runCommands(node->commands);
		//struct timespec *target_modify_t = &(statbuf->st_mtim);
	} else {
		//File is not found
		printf("%s is not a file\n", node->target);
		runCommands(node->commands);
	}
}

//Returns 1 if a > b
//Returns 0 if a <= b
int timeGreaterThan(struct timespec *a, struct timespec *b) {
	time_t a_sec = a->tv_sec;
	long a_nsec = a->tv_nsec;

	time_t b_sec = b->tv_sec;
	long b_nsec = b->tv_nsec;

	if(a_sec > b_sec) {
		return 1;
	}

	if(a_sec < b_sec) {
		return 0;
	}

	//Second values are equal
	if(a_nsec <= b_nsec) {
		return 0;
	}

	// a_nsec > b_nsec
	return 1;
}
