#ifndef BUILD_GRAPH_REPR_H
#define BUILD_GRAPH_REPR_H

typedef struct Command {
	char** cmd;
	struct Command* next;
} Command;

#endif

