// Se guardan las varialbes globales que modelan la simulación, así como las funciones para procesar su entrada por consola

#pragma once

#include <cmath>

double initial_angle = 1.0;                     // Valores de las condiciones iniciales
double initial_rope_lenght = 1.0;
double initial_amplitude = 0.1;

unsigned int no_particles = 10;                 // Forma del simulador
double particles_horizontal_separation = 0.05;   
double particles_vertical_separation = 0.035;
double particles_radius = 0.02;
double particles_mass = 1.0;

double time_speed = 1.0;                        // Velocidad del simulador
int simulator_fps = 75;
double dt = 1.0 / simulator_fps;
long double current_time = 0.0;

double gravity = 9.81;                          // Valores universales del simulador
double air_resistance = 0.00006;
double damping_factor = air_resistance / (2 * particles_mass);
double treshold = 0.00001;
int no_min_oscillations = 50;
int no_max_oscillations = 65;
double ciclying_time = 120.0;


using std::atoi;                                // Funciones de cambio de string a numéricos
using std::atof;

using std::cout;       


// Función para reescribir los valores globales del simulador
void write_global_values(string param, char *value)
{    
    if (param == "initial_angle" || param == "-ia") {initial_angle = atof(value); return;}
	if (param == "initial_rope_lenght" || param == "-irl") { initial_rope_lenght = atof(value); return; }

	if (param == "no_particles" || param == "-np") { no_particles = atoi(value); return; }
    if (param == "particles_horizontal_separation" || param == "-phs") {particles_horizontal_separation = atof(value); return;}
    if (param == "particles_vertical_separation" || param == "-pvs") {particles_vertical_separation = atof(value); return;}
    if (param == "particles_radius" || param == "-rd") { particles_radius = atof(value); return; }

    if (param == "time_speed" || param == "-ts") {time_speed = atof(value); dt = (1.0 / (double)simulator_fps) * time_speed; return;}

	if (param == "gravity" || param == "-g") { gravity = atof(value); return; }
    if (param == "air_resistance" || param == "-ar") {air_resistance = atof(value); return;}

	std::cout << "\nParametro " << param << " no conocido. Pruebe con un parametro valido." << std::endl;
    return;
}


// Función para procesar los parámetros escritos por consola
bool process_global_values(int argc, char **argv)
{
    int NoValidParameters = argc;

	if ((argc - 1) % 2 != 0)
	{
        std::cout << "\n \nLa cantidad de parametros no coincide, ignorando ultimo parametro. \n";
		NoValidParameters -= 1;
	}

	for (int i = 1; i < (NoValidParameters); i += 2)
	{
		write_global_values(argv[i], argv[i + 1]);
	}
}


// Función que contiene la separación vertical de los péndulos
double separation_function(int n)
{
    double pi = 3.14159265358;
    double twopi = 2 * pi;
    return gravity * pow((ciclying_time) / (twopi * (no_min_oscillations + n)), 2);
}
