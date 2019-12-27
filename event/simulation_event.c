//
// Created by Diego Trujillo on 2019-11-20.
//

#include "../stdafx.h"

int choose_exit(const simulation_state * state, const simulation_node * node) {
    const double * row = state->transition_matrix[node->id];
    double uniform = get_random_from_distribution(UNIFORM, NULL);
    int i; double total = 0;
    for(i = 0; i < NUM_NODES; i++) {
        total += row[i];
        if(uniform < total) return i;
    }
    return EXIT_SYSTEM;
}

void new_arrival(simulation_node * node, simulation_state * state) {
    if(node->isIdle) { // Start serving the client
        node->isIdle = false;
        node->next_exit = state->clock + get_random_from_distribution(node->exit_distribution, node->exit_params);
    }
    else // Add to the queue or lose the client
    {
        if(node->queue_capacity == INT_MAX || node->clients_in_queue < node->queue_capacity) node->clients_in_queue++;
        else node->clients_lost++;
    }

    // Program next arrival
    node->next_arrival = node->arrival_distribution == NONE ?
            NO_ARRIVAL :
            state->clock + get_random_from_distribution(node->arrival_distribution, node->arrival_params);
}

void new_exit(simulation_node * node, simulation_state * state) {

    if(node->isIdle) {
        printf("ERROR: EXIT EVENT PLANNED WITH IDLE SERVER");
        exit(4);
    }

    // Start serving the next client
    node->clients_served++;
    if(node->clients_in_queue == 0)
        node->isIdle = true;
    else
        node->clients_in_queue--;

    // Program next exit
    if(!node->isIdle) node->next_exit = state->clock + get_random_from_distribution(node->exit_distribution, node->exit_params);
    else node->next_exit = NO_EXIT;

    // Send client to next node, or out of the system
    int next_node = choose_exit(state, node);
    if(next_node != EXIT_SYSTEM)
        new_arrival(&state->nodes[next_node], state);
    else
        state->clients_served++;

}

void event_subroutine(simulation_state * state, simulation_node * node) {
    if(node->next_arrival < node->next_exit)
        new_arrival(node, state);
    else new_exit(node, state);
    int clients_in_node = node->clients_in_queue + (node->isIdle ? 0 : 1);
    node->total_clients_in_node += clients_in_node;
}

