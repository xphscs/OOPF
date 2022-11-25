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
vector<Pendel> particles;                      // Creo el arreglo que guardará los péndulos dinámicamente


#include "gl headers\GLIncludes.h"             // Incluyo los headers de OpenGL 




int main(int cargs, char **vargs)
{
    // Proceso los valores ingresados por consola
    generate_world(cargs, vargs, particles);


    // Inicializo Glut
    glutInit(&cargs, vargs);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(30, 10);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Simulador Onda de péndulos.");


    // Inicializo OpenGL
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    init();

    debug("Información pre-display.");
    debug_all_particles(particles);

    debug("Se entra en el loop principal;");
    glutMainLoop();

    return 0;
}