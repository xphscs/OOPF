#pragma once

#ifdef __APPLE__                    // Incluyo OpenGL
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif   

#include <vector>

#include "..\project headers\GlobalVariables.h"

GLdouble zNear;
GLdouble zFar;
GLfloat depth;
GLdouble plane_offset = 50.0;

GLdouble zoffset = 10.0;


// FUNCIONES DE PREPROCESAMIENTO DE LOS PARÁMETROS


void set_perspective()
{
    GLdouble World_depth = no_particles * particles_horizontal_separation;
    zNear = 0.5;
    depth = (zNear + World_depth + plane_offset);
    zFar = -(depth - World_depth - plane_offset);
}

void debug_cartesian_plane()
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);

    GLdouble offset = 0.0;
    

    for (int i = -50; i <= 50; i++)
    {
        glLoadIdentity();

        glTranslatef((GLdouble)i - offset, - offset, -zoffset);
        glScalef(1.0, 1.0, 1.0);
        glColor3f(1.0, 0.0, 0.0);

        glutSolidCube(1.0);
    }

    for (int i = -50; i <= 50; i++)
    {
        glLoadIdentity();

        glTranslatef(- offset, (GLdouble)i - offset, -zoffset);
        glScalef(1.0, 1.0, 1.0);
        glColor3f(0.0, 1.0, 0.0);

        glutSolidCube(1.0);
    }

    for (int i = -50; i <= 50; i++)
    {
        glLoadIdentity();

        glTranslatef(- offset, - offset, (GLdouble)i - zoffset);
        glScalef(1.0, 1.0, 1.0);
        glColor3f(0.0, 0.0, 1.0);

        glutSolidCube(1.0);
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

    // Se entra en el Loop
    for (int i = 0; i < no_particles; i++)
    {
        glLoadIdentity();

        //std::cout << "Se translada partícula " << i + 1 << std::endl; 
        //debug_particle(particles[i]);
        glTranslatef(particles[i].pos.x, particles[i].pos.y, -particles[i].pos.z + -zoffset);
        //std::cout << "Se terminó partícula " << i + 1 << std::endl; 
        glScalef(1.0, 1.0, 1.0);
        glColor3f(0.0, 0.0, 0.0);

        glutSolidSphere(particles_radius, 20, 20);
    }

    //debug_cartesian_plane();

    glLoadIdentity();
    glutSwapBuffers();

    //debug("Se sale de la función DISPLAY.");
}


// Función que actualiza los datos 
void timer(int)
{
    //debug("Se entra en la función TIMER.");

    glutTimerFunc( int(100 / simulator_fps), timer, 0);

    for (Pendel &particle : particles)
    {
        particle.fast_process(current_time);
    }

    current_time += dt;

    glutPostRedisplay();

    //debug("Se sale de la función TIMER.");
}


// Función de inicialización de GLUT
void init()
{
    set_perspective();
    glClearColor(1.0, 1.0, 1.0, 1.0);   // Inicializa el fondo a negro
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    debug("GLUT inicializado.");
}


// Función de resize (permite crear una ventana responsiva)
void reshape(int x, int y)
{
    debug("Se entra en la función RESHAPE.");
    if (x == 0 || y == 0){return;}

    glViewport(0, 0, x, y);

    // Creo la perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(80.0, (GLdouble)x / (GLdouble)y, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
    debug("Se sale de la función RESHAPE.");
}