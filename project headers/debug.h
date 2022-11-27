// Herramientas de debugación (odio utilizar debugers clásicos, como buen linuxero prefiero hacer prints B))

#pragma once

using std::cout;
using std::endl;

void debug(string message)
{
    cout << message << endl;
    return;
}


void debug_global_values()
{
    cout << "\n\n GLOBAL VARIABLES VALUES \n\n";
    cout << "initial angle: " << initial_angle << endl;
    cout << "initial rope lenght: " << initial_rope_lenght << endl;
    cout << "\n";
    cout << "no particles: " << no_particles << endl;
    cout << "horizontal sep: " << particles_horizontal_separation << endl;
    cout << "vertical sep: " << particles_vertical_separation << endl;
    cout << "radius: " << particles_radius << endl;
    cout << "\n";
    cout << "time speed: " << time_speed << endl;
    cout << "\n";
    cout << "gravity: " << gravity << endl;
}

void debug_particle(Pendel part)
{
    cout << part.pos.x << "\t\t" << part.pos.y << "\t\t" << part.pos.z << endl;
}

void debug_all_particles(std::vector<Pendel> particles)
{
    for (Pendel part : particles)
    {
        cout << part.pos.x << "\t\t" << part.pos.y << "\t\t" << part.pos.z << endl;
    }
}

