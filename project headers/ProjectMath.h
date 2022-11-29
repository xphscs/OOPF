// Objetos matemáticos que son útiles para el proyecto.


#pragma once

#include <cmath>

// Clase Vector3. Emula un vector tridimensional
class Vector3
{
    public:

        double x, y, z;

        // Inicializadores
        Vector3(double px, double py, double pz)
        {
            this -> x = px;
            this -> y = py;
            this -> z = pz;
        }

        Vector3()
        {
            this -> x = 0.0;
            this -> y = 0.0;
            this -> z = 0.0;
        }

        Vector3(double *vec)
        {
            this -> x = vec[0];
            this -> y = vec[1];
            this -> z = vec[2];
        }


        // Operaciones propias del vector
        double norm()
        {
            return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2));
        }

        Vector3 normalize()
        {
            double n = this->norm();
            Vector3 normalized_vector = {this->x / n, this->y / n, this->z / n};
            return normalized_vector;
        }

        // double *array()
        // {
        //     //double array_vector[3] = {this -> x, this -> y, this -> z};
        //     return 0.1;
        // }


        // Operaciones entre vectores
        Vector3 operator + (Vector3 &vec)
        {
            return Vector3( (this->x + vec.x), (this->y + vec.y), (this->z + vec.z));
        }

        Vector3 operator - (Vector3 &vec)
        {
            return Vector3( (this->x - vec.x), (this->y - vec.y), (this->z - vec.z));
        }

        double operator * (Vector3 &vec)
        {
            return (this->x * vec.x) + (this->y * vec.y) + (this->z * vec.z);
        }
};

// Producto escalar de un vector tridimensional
Vector3 operator * (double a, Vector3 vec)
{
    return Vector3( (a * vec.x), (a * vec.y), (a * vec.z) );
}