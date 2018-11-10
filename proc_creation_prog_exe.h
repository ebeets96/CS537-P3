#ifndef PROC_CREATE_H
#define PROC_CREATE_H
#include "build_spec_graph.h"

int makeTarget(char* target, Node* graph);
int makeNode(GraphNode* node);
int timeGreaterThan(struct timespec *a, struct timespec *b);

#endif
