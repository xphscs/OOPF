#pragma once

#include "GlobalVariables.h"
#include "objects.h"
#include <vector>

void generate_world(int argc, char **argv, std::vector<Pendel> &particles)
{
    process_global_values(argc, argv);


    for (int i = 0; i <= no_particles; i++)
    {
        particles.push_back(Pendel(initial_angle, initial_rope_lenght, i));
    }
}