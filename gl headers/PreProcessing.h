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

// FUNCIONES DE PREPROCESAMIENTO DE LOS PARÁMETROS


// Función de conversión de radianes a grados
double rad_to_deg(double rad)
{
    return rad * (180.0/3.141592653589793238463);
}
double deg_to_rad(double deg)
{
    return deg * (3.141592653589793238463 / 180.0);
}

void get_off(double ar)
{
    // double num = particles_radius*(zFar - zNear) - (zFar*separation_function(0) + zNear*separation_function(no_particles));
    // double dem = zNear + zFar;

    // return num / dem;
    double phi = deg_to_rad(fovx);

    zoffset =  ( (separation_function(0)) * ar * zNear) / (std::tan(phi / 2.0) * ar) * std::log10(no_particles);
    yoffset =  -(separation_function(0) - ( (zoffset*std::tan(phi / 2.0)) / ar));
    zFar = (depth - zoffset);
}

// Esta función se llama después de procesar los datos de consola en la función Init. Crea la perspectiva del mundo.
void set_perspective()
{
    zNear = 0.15;
    //zoffset = -(zNear - (() / (std::tan(fovx / 2))) );
    depth = (no_particles * particles_horizontal_separation) + particles_radius;
    // yoffset = -(zFar*separation_function(0) + zNear*separation_function(no_particles)) / (zFar + zNear) + (particles_radius / 2.0);
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
        glTranslatef(particles[i].pos.x, particles[i].pos.y + yoffset, particles[i].pos.z + zoffset);
        //std::cout << "Se terminó partícula " << i + 1 << std::endl; 
        glScalef(1.0, 1.0, 1.0);
        double grey_color = particles[i].grey_scale;
        glColor3f(grey_color, grey_color, grey_color);

        glutSolidSphere(particles_radius, 20, 20);

    }

    glLoadIdentity();
    debug_cartesian_plane();
    // debug_all_particles(particles);
    // debug_particles_perspective(particles);

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

    get_off(double(x) / double(y));
    gluPerspective(90.0, (GLdouble)x / (GLdouble)y, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
    debug_perspective();
    // debug("Se sale de la función RESHAPE.");
}