//
// Created by Diego Trujillo on 2019-11-19.
//

#include "stdafx.h"


int main() {
    printf("==========================================\n");
    printf("          QUEUE SYSTEM SIMULATION\n");
    printf("==========================================\n");

    srand(time(NULL));

    simulation sim;
    sim.start = clock();
    sim.start_time = time(NULL);
    int i;
    for(i = 0; i < NUM_SIMULATIONS; i++) {
        printf("\nStarting simulation #%d...", i + 1);
        printf("\n\tInitializing simulation state...");
        simulation_state state;
        startup(&state);
        sim.states[i] = &state;
        printf("Done.");
        printf("\n\tRunning simulation...");
        int j = 0;
        while (state.clients_served != SAMPLE_SIZE + STATIONARY_WAIT) {

            simulation_node *node = clock_subroutine(&state);
            event_subroutine(&state, node);
#if SHOW_LOG
            /* Log will show simulation state at every relevant moment in the process.
             * It is very slow and is recommended for debugging only.
             */
            simulation_log(&state, node, j);
#endif
            j++;
        }
        printf("Done");
        printf("\nDone.\n");
    }
    sim.end = clock();
    printf("\n\tEND OF SIMULATION\n");
    generate_report(&sim);
}