#pragma once

#include <cmath>

using std::sin;
using std::cos;
using std::sqrt;
using std::pow;

class Pendel
{
    public:

        Vector3 pos = Vector3();
        Vector3 vel = Vector3();
        Vector3 acc = Vector3();
        Vector3 force = Vector3();

        double angle, rope_lenght;
        double x_amplitude, y_amplitude;
        double omega;

        Pendel(double pangle, double prope_lenght, int n)
        {
            this -> angle = pangle;
            this -> rope_lenght = prope_lenght + (particles_vertical_separation * n);

            this -> pos.x = this -> x_amplitude = rope_lenght * sin(this -> angle);
            this -> pos.y = this -> y_amplitude = rope_lenght * cos(this -> angle);
            this -> pos.z = n * particles_horizontal_separation;

            this -> omega = sqrt(gravity / this -> rope_lenght);
        }

        void fast_process(double time)
        {
            this -> pos.x = x_amplitude * cos(this -> omega * time);
        }
};