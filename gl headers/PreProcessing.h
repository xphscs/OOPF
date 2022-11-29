// Aquí se encuentran las funciones encesarias para correr OpenGL

#pragma once

#ifdef __APPLE__                    // Incluyo OpenGL
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif   

#include <vector>
#include <chrono>
#include <cmath>

#include "..\project headers\GlobalVariables.h"

// Variables de perspectiva
GLdouble zNear;
GLdouble zFar;
GLfloat depth;
GLfloat fovx;
GLdouble plane_offset = 1.0;

// Vaiable de offset en z. Modifica qué tan lejos queremos ver el montaje
GLdouble zoffset = 0.1;

// FUNCIONES DE PREPROCESAMIENTO DE LOS PARÁMETROS


// Esta función se llama después de procesar los datos de consola en la función Init. Crea la perspectiva del mundo.
void set_perspective()
{
    zNear = 0.01;
    zoffset = -(zNear + (particles_radius * 10) + (no_particles * particles_vertical_separation));
    depth = (no_particles + 1) * particles_horizontal_separation;
    zFar = -(depth + zNear);
    fovx = 90.0;
}


// Función de debug. Crea un plano cartesiano 3D para ver el comportamiento de las bolas de una forma más precisa
void debug_cartesian_plane()
{

    GLdouble offset = 0.0;
    

    for (int i = -50; i <= 50; i++)
    {
        glLoadIdentity();

        glTranslatef((GLdouble)i * 0.01 , 0.0, 0.0 + zoffset);
        glScalef(1.0, 1.0, 1.0);
        glColor3f(1.0, 0.0, 0.0);

        glutSolidCube(0.001);
    }

    for (int i = -50; i <= 50; i++)
    {
        glLoadIdentity();

        glTranslatef(0.0, (GLdouble)i * 0.01, 0.0 + zoffset);
        glScalef(1.0, 1.0, 1.0);
        glColor3f(0.0, 1.0, 0.0);

        glutSolidCube(0.001);
    }

    for (int i = 0; i <= 50; i++)
    {
        glLoadIdentity();

        glTranslatef(0.0, 0.0, (GLdouble)i * 0.01 + zoffset);
        glScalef(1.0, 1.0, 1.0);
        glColor3f(0.0, 0.0, 1.0);

        glutSolidCube(0.001);
    }
}
    

// FUNCIONES DE INICIALIZACIÓN DE GL

// Función que renderiza en la pantalla la información que le otorguemos
void display()
{
    //debug("Se entra en la función DISPLAY.");
    
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);

    //debug("Información post-display.");
    //debug_all_particles(particles);

    // Se entra en el Loop donde se renderizan los objetos según su posición
    for (int i = no_particles - 1; i >= 0; i--)
    {
        glLoadIdentity();

        //std::cout << "Se translada partícula " << i + 1 << std::endl; 
        //debug_particle(particles[i]);
        glTranslatef(particles[i].pos.x, particles[i].pos.y, particles[i].pos.z + zoffset);
        //std::cout << "Se terminó partícula " << i + 1 << std::endl; 
        glScalef(1.0, 1.0, 1.0);
        double grey_color = particles[i].grey_scale;
        glColor3f(grey_color, grey_color, grey_color);

        glutSolidSphere(particles_radius, 20, 20);
    }

    glLoadIdentity();
    debug_cartesian_plane();

    //glLoadIdentity();
    glutSwapBuffers();

    //debug("Se sale de la función DISPLAY.");
}


// Función que actualiza los datos 
void timer(int)
{
    //debug("Se entra en la función TIMER.");

    glutTimerFunc((int)(1000 / simulator_fps), timer, 0);

    for (int i = 0; i < no_particles; i++)
    {
        particles[i].fast_process(current_time);
    }
    
    //debug_all_particles(particles);
    current_time += dt;

    glutPostRedisplay();

    // debug("Se sale de la función TIMER.");
}


// Función de inicialización de GLUT, donde se crea la matriz de perspectiva y otras cositas para preparas los gráficos.
void init()
{
    set_perspective();
    glClearColor(1.0, 1.0, 1.0, 1.0);   // Inicializa el fondo a negro
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    debug("GLUT inicializado.");
}


// Función de resize (permite crear una ventana responsiva). Es llamada al iniciar la simulación, por lo que aquí creo la matriz de perspectiva.
void reshape(int x, int y)
{
    // debug("Se entra en la función RESHAPE.");
    if (x == 0 || y == 0){return;}

    glViewport(0, 0, x, y);

    // Creo la perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(fovx, (GLdouble)x / (GLdouble)y, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
    // debug("Se sale de la función RESHAPE.");
}