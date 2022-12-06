// Se guardan las varialbes globales que modelan la simulación, así como las funciones para procesar su entrada por consola

#pragma once

#include <cmath>
#include <string>
#include <fstream>

double initial_angle = 1.0;                     // Valores de las condiciones iniciales
double initial_rope_lenght = 1.0;
double initial_amplitude = 0.1;

unsigned int no_particles = 10;                 // Forma del simulador
double particles_radius = 0.02;
double particles_horizontal_separation = particles_radius * 2.0;   
double particles_vertical_separation = 0.035;
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

int sep_fun = 0;

// Variables de perspectiva
double zNear;
double zFar;
float depth;
float fovx;

double forced_zoffset = 0.0;

int camera_view = 0;

// Vaiable de offset en z. Modifica qué tan lejos queremos ver el montaje
double zoffset;\
double yoffset;


using std::atoi;                                // Funciones de cambio de string a numéricos
using std::atof;

using std::cout;       


// Función para reescribir los valores globales del simulador
void write_global_values(string param, char *value)
{    
    if (param == "initial_angle" || param == "-iag") {initial_angle = atof(value); return;}
	if (param == "initial_rope_lenght" || param == "-irl") { initial_rope_lenght = atof(value); return; }
    if (param == "initial_amplitude" || param == "-ia") {initial_amplitude = atof(value); return;}

    if (param == "no_min_oscillations" || param == "-mino") {no_min_oscillations = atoi(value); return;}
    if (param == "no_max_oscillations" || param == "-maxo") {no_max_oscillations = atoi(value); return;}
    if (param == "ciclying_time" || param == "-ct") {ciclying_time = atof(value); return;}

	if (param == "no_particles" || param == "-np") { no_particles = atoi(value); return; }
    if (param == "particles_horizontal_separation" || param == "-phs") {particles_horizontal_separation = atof(value); return;}
    if (param == "particles_vertical_separation" || param == "-pvs") {particles_vertical_separation = atof(value); return;}
    if (param == "particles_radius" || param == "-rd") { particles_radius = atof(value); particles_horizontal_separation = particles_radius * 2.0; return; }
    if (param == "particles_mass" || param == "-pm") {particles_mass = atof(value); return;}

    if (param == "time_speed" || param == "-ts") {time_speed = atof(value); dt = (1.0 / (double)simulator_fps) * time_speed; return;}

	if (param == "gravity" || param == "-g") { gravity = atof(value); return; }
    if (param == "air_resistance" || param == "-ar") {air_resistance = atof(value); return;}

    if (param == "camera_view" || param == "-cv") {camera_view = atoi(value); return;}
    if (param == "forced_zoffset" || param == "-fzo") {forced_zoffset = atof(value); return;}

    if (param == "-sf") {sep_fun = atoi(value); return;}

	std::cout << "\nParametro " << param << " no conocido. Pruebe con un parametro valido." << std::endl;
    return;
}


// Función para leer la entrada de parámetros por texto
void read_GC_file()
{
    std::ifstream file("global_constants.txt");

    if (file.is_open())
    {
        int state = 0;
        std::string current_param;

        while (file)
        {
            std::string line;
            std::getline(file, line);

            //std::cout << line << std::endl;
            
            if (line[0] == '/' || line[0] == '(' || line == "")
            {
                continue;
            }

            if(state == 0)
            {
                //std::cout << line << std::endl;
                line.pop_back();
                //std::cout << line << std::endl;
                current_param = line;

                //std::cout << "Se cambia el parámetro." << std::endl;
                state = 1;
                //std::cout << state << std::endl;
            } else {
                char charline[line.length() + 1];
                strcpy(charline, line.c_str());

                write_global_values(current_param, charline);
                
                //std::cout << "Se cambia el parámetro." << std::endl;
                state = 0;
                //std::cout << state << std::endl;
            }
        }

    } else {
        std::cout << "ERROR AL LEER EL ARCHIVO DE PARAMETROS." << std::endl;
    }
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

    read_GC_file();

	for (int i = 1; i < (NoValidParameters); i += 2)
	{
		write_global_values(argv[i], argv[i + 1]);
	}
}


// Función que contiene la separación vertical de los péndulos
double separation_function(int n)
{
    double pi = 3.14159265358;
    double twopi = 2.0 * pi;
    return -gravity * pow((ciclying_time) / (twopi * (no_min_oscillations + (n))), 2);
}
    

// Función de separación alternativa
double alt_separation_function(int n)
{
    return -((particles_radius * (n + 1)) + initial_rope_lenght);
}