//
// Created by Diego on 2019-11-20.
//

#include "stdafx.h"


void read_node(simulation_node * node, char * stream)
{

    char * arrival_dist = strtok(stream, ","), * exit_dist, * lambda = NULL, * n = NULL, * beta = NULL, * capacity;

    if(strcmp(arrival_dist, "EXPONENTIAL") == 0) {
        lambda = strtok(NULL, ",");
        double * param = malloc(sizeof(double));
        param[0] = atof(lambda);
        node->arrival_distribution = EXPONENTIAL;
        node->arrival_params = param;
    }
    else if(strcmp(arrival_dist, "ERLANG") == 0) {
        n = strtok(NULL, ",");
        beta = strtok(NULL, ",");
        double * param = malloc(2 * sizeof(double));
        param[0] = atoi(n);
        param[1] = atof(beta);
        node->arrival_distribution = ERLANG;
        node->arrival_params = param;

    } else node->arrival_distribution = NONE;


    exit_dist = strtok(NULL, ",");
    if(strcmp(exit_dist, "EXPONENTIAL") == 0) {
        lambda = strtok(NULL, ",");
        double * param = malloc(sizeof(double));
        param[0] = atof(lambda);
        node->exit_distribution = EXPONENTIAL;
        node->exit_params = param;
    }
    else if(strcmp(exit_dist, "ERLANG") == 0) {
        n = strtok(NULL, ",");
        beta = strtok(NULL, ",");
        double * param = malloc(2 * sizeof(double));
        param[0] = atoi(n);
        param[1] = atof(beta);
        node->exit_distribution = ERLANG;
        node->exit_params = param;
    }
    else node->exit_distribution = NONE;

    capacity = strtok(NULL, ",");
    if(strcmp(capacity, "inf") == 0) node->queue_capacity = INT_MAX;
    else node->queue_capacity = atoi(capacity);
    free(arrival_dist);
    free(exit_dist);
    free(lambda);
    free(n);
    free(beta);
    free(capacity);
}

void startup_node(simulation_node * node, char * stream, int i) {

    node->id = i;
    read_node(node, stream);

    node->next_arrival = get_random_from_distribution(node->arrival_distribution, node->arrival_params);
    node->next_exit = NO_EXIT;
    node->isIdle = true;
    node->clients_in_queue = 0;
    node->clients_lost = 0;
    node->clients_served = 0;

    if (node->queue_capacity != INT_MAX) {
        int j;
        node->time_with_n_clients = malloc((node->queue_capacity + 2) * sizeof(double));
        for (j = 0; j < node->queue_capacity + 2; j++)
            node->time_with_n_clients[i] = 0;
    }
    else node->time_with_n_clients = NULL;

    node->total_queue_time = 0;
    node->time_busy = 0;

    node->total_clients_in_node = 0;
}

void startup(simulation_state * state) {
    int i = 0, j = 0;

    FILE* file;
    if((file = fopen("node_info.csv", "r")))
    {
        char line[1024];
        while (fgets(line, 1024, file) && i < NUM_NODES) {
            char * tmp = strdup(line);
            startup_node(&state->nodes[i], tmp, i);
            free(tmp);
            i++;
        }
        if(i != NUM_NODES) {
            printf("ERROR: Not enough nodes defined in node_info.csv. Check definition of simulation_globals::NUM_NODES.");
            exit(2);
        }
        fclose(file);
    }
    else {
        printf("ERROR: file \"node_info.csv\" not found");
        exit(1);
    }

    double transition_matrix[NUM_NODES][NUM_NODES] = TRANSITION_MATRIX;

    for(i = 0; i < NUM_NODES; i++)
        for(j = 0; j < NUM_NODES; j++)
            state->transition_matrix[i][j] = transition_matrix[i][j];

    state->clock = 0;
    state->clock_last = 0;
    state->clients_served = 0;
}