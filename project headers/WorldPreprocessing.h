// Se encuentran las funciones para preprocesar el mundo en general. De momento se ve vació e innecesario pero cuando agregue cosas de perspectiva va a servir mucho tener esto organizadito aquí

#pragma once

#include "GlobalVariables.h"
#include "objects.h"
#include <vector>

void generate_world(int argc, char **argv, std::vector<Pendel> &particles)
{
    // Procesa las variables globales que son pasadas por consola
    process_global_values(argc, argv);


    // Genera las partículas
    for (int i = 0; i <= no_particles; i++)
    {
        particles.push_back(Pendel(initial_angle, initial_rope_lenght, i));
    }
}