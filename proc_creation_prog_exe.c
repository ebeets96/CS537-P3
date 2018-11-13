/*
 * Jack David jdavid3
 * Eric Beets ebeets
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "proc_creation_prog_exe.h"

int makeTarget(char* target, Node* graph) {
	GraphNode* tNode = findTarget(graph, target)->element;

	if(tNode == NULL) {
		fprintf(stderr, "The specified target (%s) could not be found", target);
		exit(EXIT_FAILURE);
	}

	return makeNode(tNode);
}

// 1 if it made anything
// 0 if it did not
int makeNode(GraphNode* node) {
	Node* child = node->children;
	int hasNonFileDependency = 0;
	struct timespec most_recently_modified_depency;
	most_recently_modified_depency.tv_sec = 0;
	most_recently_modified_depency.tv_nsec = 0;

	struct stat *statbuf = malloc(sizeof(struct stat));
	int statSuccess; //Holds return value for latest stat call

	while(child != NULL) {
			GraphNode* childNode = (GraphNode*) child->element;
			makeNode(childNode);

			char* dependency_name = childNode->target;
			statSuccess = stat(dependency_name, statbuf);
			if(statSuccess == 0) {
				//Dependency is a file
				if(timeGreaterThan(&statbuf->st_mtim, &most_recently_modified_depency)) {
					// printf("The dependency, %s, was greater.\n", dependency_name);
					most_recently_modified_depency.tv_sec = statbuf->st_mtim.tv_sec;
					most_recently_modified_depency.tv_nsec = statbuf->st_mtim.tv_nsec;
				} else {
					// printf("The dependency, %s, was not greater.\n", dependency_name);
				}
			} else {
				hasNonFileDependency = 1;
			}

			child = child->next;
	}

	statSuccess = stat(node->target, statbuf);

	if(statSuccess == 0) {
		//Target is a file
		if(hasNonFileDependency || timeGreaterThan(&most_recently_modified_depency, &statbuf->st_mtim)) {
			runCommands(node->commands);
			free(statbuf);
			return 1;
		} else {
			//Didn't have to make anything
			free(statbuf);
			return 0;
		}
	} else {
		runCommands(node->commands);
		free(statbuf);
		return 1;
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
