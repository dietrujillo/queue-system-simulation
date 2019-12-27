//
// Created by Diego Trujillo on 2019-11-19.
//

#include "../stdafx.h"

double get_random_from_distribution(prob_distribution dist, const double * params) {
    double u = (double)rand()/(RAND_MAX + 1);
    if(dist == UNIFORM) {
        return u;
    }
    else if (dist == EXPONENTIAL) {
        return -log(1 - u) / (double) params[0];
    }
    else if(dist == ERLANG) {
        int i;
        double total = 1;
        for(i = 0; i < params[0]; i++)
            total *= (1 - get_random_from_distribution(UNIFORM, NULL));
        return -log(total) / (double) params[1];
    }
    else return INT_MAX;
}

