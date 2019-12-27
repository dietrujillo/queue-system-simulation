//
// Created by Diego Trujillo on 2019-11-20.
//

#ifndef SIMULACION_SIMULATION_STATE_H
#define SIMULACION_SIMULATION_STATE_H


#include "stdafx.h"

typedef enum { UNIFORM, EXPONENTIAL, ERLANG, NONE } prob_distribution;


typedef struct {

    int id;

    prob_distribution arrival_distribution;
    prob_distribution exit_distribution;

    double* arrival_params;
    double* exit_params;

    int queue_capacity;

    double next_arrival;
    double next_exit;

    bool isIdle;
    int clients_in_queue;
    int clients_lost;
    int clients_served;

    double * time_with_n_clients;

    double total_queue_time;
    double time_busy;

    double total_clients_in_node;

}simulation_node;

typedef struct {

    double clock;
    double clock_last;

    int clients_served;

    simulation_node nodes[NUM_NODES];

    double transition_matrix[NUM_NODES][NUM_NODES];
}simulation_state;

typedef struct {

    clock_t start;
    clock_t end;
    time_t start_time;
    simulation_state * states[NUM_SIMULATIONS];

}simulation;

#endif //SIMULACION_SIMULATION_STATE_H
