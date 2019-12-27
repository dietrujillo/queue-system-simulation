//
// Created by Diego Trujillo on 2019-11-19.
//

#ifndef SIMULACION_SIMULATION_GLOBALS_H
#define SIMULACION_SIMULATION_GLOBALS_H

#define SAMPLE_SIZE 1000000
#define STATIONARY_WAIT 500

#define NUM_NODES 6
#define NUM_SIMULATIONS 25

/* Transition matrix[i][j] is defined as the probability of exiting node i and going to node j.
 * Probabilities in a row must add up to at most one. If they add up to less than one, the remainder will
 * be understood as the probability of exiting the system (See simulation_event::choose_exit).
 */
#define TRANSITION_MATRIX \
        { \
                {0, 0, 0, 0.5, 0.5, 0},  \
                {0, 0, 0, 0.5 ,0.5, 0},  \
                {0, 0, 0, 0.5 ,0.5, 0},  \
                {0, 0, 0,   0,   0, 1},  \
                {0, 0, 0,   0,   0, 1},  \
                {0, 0, 0,   0,   0, 0}   \
        }

#define SHOW_LOG 0
#define WRITE_REPORT_TO_FILE 1

#define EXIT_SYSTEM -1
#define NO_ARRIVAL INT_MAX
#define NO_EXIT INT_MAX

#endif //SIMULACION_SIMULATION_GLOBALS_H
