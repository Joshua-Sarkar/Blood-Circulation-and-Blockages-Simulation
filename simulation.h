#ifndef SIMULATION_H
#define SIMULATION_H

#include "graph.h"

void run_simulation_tick(VascularGraph* graph);
void induce_blockage(VascularGraph* graph, int node_id, int duration);
const char* get_simulation_state_json(VascularGraph* graph);

#endif
