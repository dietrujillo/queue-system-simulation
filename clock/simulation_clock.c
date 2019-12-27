//
// Created by Diego Trujillo on 2019-11-20.
//

#include "../stdafx.h"

simulation_node * get_next_node(simulation_state * state) {

    int i;
    double min = INT_MAX;
    simulation_node * ret = NULL;
    for(i = 0; i < NUM_NODES; i++) {
        if (state->nodes[i].next_arrival < min || state->nodes[i].next_exit < min) {
            ret = &state->nodes[i];
            if (state->nodes[i].next_arrival < min)
                min = state->nodes[i].next_arrival;
            if(state->nodes[i].next_exit < min)
                min = state->nodes[i].next_exit;
        }
    }
    if(ret != NULL)
        return ret;
    else {
        printf("ERROR: next node for simulation unspecified");
        exit(3);
    }
}


simulation_node * clock_subroutine(simulation_state * state) {

    double next_clock = 0;

    simulation_node *node = get_next_node(state);
    if (node->next_arrival < node->next_exit)
        next_clock = node->next_arrival;
    else next_clock = node->next_exit;

    double timespan = next_clock - state->clock;

    state->clock_last = state->clock;
    state->clock = next_clock;

    int i;
    for (i = 0; i < NUM_NODES; i++) {
        state->nodes[i].total_queue_time += state->nodes[i].clients_in_queue * timespan;
        if (state->nodes[i].isIdle && state->nodes[i].queue_capacity != INT_MAX)
            state->nodes[i].time_with_n_clients[0] += timespan;
        else {
            state->nodes[i].time_busy += timespan;
            if(state->nodes[i].queue_capacity != INT_MAX)
                state->nodes[i].time_with_n_clients[state->nodes[i].clients_in_queue + 1] += timespan;
        }
    }

    return node;

}