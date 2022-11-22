#include <iostream>                 // Incluyo librerías estándar
#include <string>
#include <vector>
#include <cmath>


#ifdef __APPLE__                    // Incluyo OpenGL
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif                      


using std::vector;                  // Utilizo funciones comunes de la librería estandar
using std::string;
using std::sin;
using std::cos;





#include "project headers\PrivateLibraries.h"  // Incluyo los headers propios

int main(int cargs, char **vargs)
{
    
    process_global_values(cargs, vargs);


    Pendel part = Pendel(initial_angle, initial_rope_lenght, 1);

    double time = 0.0;

    for (int i = 0; i < 1000; i++)
    {   
        time += dt;

        debug_particle(part);
        part.fast_process(time);

    }

    return 0;
}