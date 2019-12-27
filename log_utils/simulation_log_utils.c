//
// Created by Diego Trujillo on 2019-11-20.
//

#include "../stdafx.h"

void simulation_log(simulation_state * state, simulation_node * node, int iteration) {

    printf("\n\tLOG FOR SIMULATION STATE #%d\n", iteration);
    printf("Node is node #%d\n", node->id + 1);
    printf("Clock = %f", state->clock);

    int i;
    for(i = 0; i < NUM_NODES; i++) {
        printf("\nNode #%d has %d clients in queue, ", state->nodes[i].id + 1, state->nodes[i].clients_in_queue);
        printf("isIdle = %d, next arrival = %f, next exit = %f, clients lost = %d\n", state->nodes[i].isIdle,
                state->nodes[i].next_arrival == INT_MAX ? -1 : state->nodes[i].next_arrival,
                state->nodes[i].next_exit == INT_MAX ? -1 : state->nodes[i].next_exit, state->nodes[i].clients_lost);
    }
    printf("clients served = %d\n", state->clients_served);

}

void generate_report(simulation * sim) {
    time_t t = time(NULL);
    struct tm simulation_end_time = *localtime(&t);
    struct tm simulation_start_time = *localtime(&sim->start_time);






#if WRITE_REPORT_TO_FILE
    FILE* file = fopen("SimulationReport.txt", "w");
    {
        fprintf(file, "============================================\n");
        fprintf(file, "    Simulation report for queue system      \n");
        fprintf(file, "============================================\n");
        fprintf(file, "Simulation started on %d-%d-%d %d:%d:%d\n", simulation_start_time.tm_year + 1900, simulation_start_time.tm_mon + 1, simulation_start_time.tm_mday, simulation_start_time.tm_hour, simulation_start_time.tm_min, simulation_start_time.tm_sec);
        fprintf(file, "Simulation ended on %d-%d-%d %d:%d:%d\n", simulation_end_time.tm_year + 1900, simulation_end_time.tm_mon + 1, simulation_end_time.tm_mday, simulation_end_time.tm_hour, simulation_end_time.tm_min, simulation_end_time.tm_sec);
        fprintf(file, "Time elapsed: %lf s\n", (double)(sim->end - sim->start)/CLOCKS_PER_SEC);
        fprintf(file, "\n--------------------------------------------\n");

        fprintf(file, "\nSimulation parameters: \n");
        fprintf(file, "Number of distinct simulations: %d\n", NUM_SIMULATIONS);
        fprintf(file, "Sample size per simulation (without stationary wait) = %d\n", SAMPLE_SIZE);
        fprintf(file, "Sample size for stationary wait; %d\n", STATIONARY_WAIT);
        fprintf(file, "Number of nodes: %d\n", NUM_NODES);
        fprintf(file, "Node info: \n");
        {
            char buf[1024];
            FILE *node_info = fopen("node_info.csv", "r");
            while (fgets(buf, 1024, node_info))
                fprintf(file, "\t%s\n", buf);
        }

        fprintf(file, "\n--------------------------------------------\n");

        fprintf(file, "\nResults: \n");
    }
    fclose(file);
    printf("A report has been saved to \"SimulationReport.txt\"");

#ifdef _WIN32
    system("SimulationReport.txt");
#endif

#else

#endif
}