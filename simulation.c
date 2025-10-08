#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "simulation.h"

// Simple blocking state array
static int* blockage_timers = NULL;
static int blockage_count = 0;

void run_simulation_tick(VascularGraph* graph) {
    for (int i = 0; i < graph->node_count; i++) {
        VesselNode* node = &graph->nodes[i];
        if (node->neighbor_count == 0 || is_empty(node->cells)) continue;
        if (blockage_timers && i < blockage_count && blockage_timers[i] > 0) {
            blockage_timers[i]--;
            continue; // Blocked node
        }
        BloodCell* cell = dequeue(node->cells);
        if (!cell) continue;
        int idx = rand() % node->neighbor_count;
        VesselNode* next_node = node->neighbors[idx];
        if (next_node->current_cell_count < next_node->capacity) {
            enqueue(next_node->cells, cell);
            next_node->current_cell_count++;
            node->current_cell_count--;
        } else {
            enqueue(node->cells, cell);
        }
    }
}

void induce_blockage(VascularGraph* graph, int node_id, int duration) {
    if (!blockage_timers) {
        blockage_timers = calloc(graph->node_count, sizeof(int));
        blockage_count = graph->node_count;
    }
    if (node_id >= 0 && node_id < blockage_count) {
        blockage_timers[node_id] = duration;
    }
}

const char* get_simulation_state_json(VascularGraph* graph) {
    static char buffer[10000];
    char temp[256];
    strcpy(buffer, "{");
    for (int i = 0; i < graph->node_count; i++) {
        sprintf(temp, "\"node_%d\": %d", graph->nodes[i].id, graph->nodes[i].current_cell_count);
        strcat(buffer, temp);
        if (i != graph->node_count - 1) strcat(buffer, ",");
    }
    strcat(buffer, "}");
    return buffer;
}
