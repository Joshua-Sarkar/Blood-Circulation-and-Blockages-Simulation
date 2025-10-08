#ifndef GRAPH_H
#define GRAPH_H

#include "queue.h"

typedef struct VesselNode {
    int id;
    int capacity;
    int current_cell_count;
    Queue* cells;
    struct VesselNode** neighbors;
    int neighbor_count;
} VesselNode;

typedef struct VascularGraph {
    VesselNode* nodes;
    int node_count;
} VascularGraph;

VascularGraph* create_graph(int node_count);
VesselNode* get_node_by_id(VascularGraph* graph, int id);
void add_connection(VascularGraph* graph, int from_id, int to_id);
void free_graph(VascularGraph* graph);

#endif
