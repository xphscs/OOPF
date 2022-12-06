// Objetos que se tendrán en el simulador.

#pragma once

#include <cmath>

using std::sin;
using std::cos;
using std::sqrt;
using std::pow;
using std::exp;
using std::asin;

double pi = 3.14159265358;
double twopi = 2 * pi;

// Clase que simula un péndulo.
class Pendel
{
    public:

        Vector3 pos = Vector3();
        Vector3 vel = Vector3();
        Vector3 acc = Vector3();
        Vector3 force = Vector3();

        double grey_scale;

        double angle, rope_lenght;
        double x_amplitude, y_amplitude;
        double omega;

        int particle_n;

        double max_y = separation_function(0);

        Pendel(double pangle, double prope_lenght, int n)
        {
            // Creo la longitud de la cuerda según el número del péndulo. De momento se tiene un crecimiento lineal, pero pienso agregar un crecimiento con diferentes funciones
            // this -> rope_lenght = prope_lenght + (particles_vertical_separation * (double)n);
            this -> rope_lenght = -separation_function(n);

            if (sep_fun == 0)
            {
                rope_lenght = -separation_function(n);
            } else {
                rope_lenght = -alt_separation_function(n);
            }

            this -> particle_n = n;

            // -> pos.x = this -> x_amplitude = rope_lenght * sin(this -> angle);
            //  this -> pos.y = this -> y_amplitude = rope_lenght * cos(this -> angle) - (particles_vertical_separation * n);
            this -> pos.x = this -> x_amplitude = initial_amplitude;
            this -> pos.y = - sqrt(pow(this -> rope_lenght, 2) - pow(this -> x_amplitude, 2));
            this -> pos.z = -(n) * particles_horizontal_separation;

            this -> angle = asin(this -> x_amplitude / this -> rope_lenght);
            this -> omega = sqrt( (gravity / this -> rope_lenght) - pow(damping_factor, 2) );

            this -> grey_scale = ((double)(n + 1)/ (double)no_particles) / 2.0;

            // std::cout << n << " with a y of: " << this -> pos.y  << std::endl;
        }


        // Función que simula el movimiento del péndulo según lo visto en clase. Sólo funciona con ángulos pequenos.
        void fast_process(double time)
        {
            this -> pos.x = exp(-damping_factor * time) * this -> x_amplitude * cos(this -> omega * time);
            //std::cout << this -> pos.x << std::endl;
        }
};