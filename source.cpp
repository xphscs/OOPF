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

    return 0;
}