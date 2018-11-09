#ifndef PROC_CREATE_H
#define PROC_CREATE_H
#include "build_spec_graph.h"

void makeTarget(char* target, Node* graph);
void makeNode(GraphNode* node);
int timeGreaterThan(struct timespec *a, struct timespec *b);

#endif
