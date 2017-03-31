//
// Created by michael on 3/16/17.
//

#include <cmath>
#include <iostream>
#include "rosenthal.h"

#define PI 3.141592

rosenthal::rosenthal(double thermal_conductivity, double density,
                     double intial_temperature, double voltage, double amperage,
                     double efficiancy, double specific_heat)
{
    this->thermal_conductivity = thermal_conductivity;
    this->density = density;
    this->initial_temperature = intial_temperature;
    this->voltage = voltage;
    this->amperage = amperage;
    this->efficiancy = efficiancy;
    this->specific_heat = specific_heat;
    this->thermal_diffusivity = thermal_conductivity / (density * specific_heat);
}

double** rosenthal::calculateRosenthal(double dist_x[NARRAY], double dist_y[MARRAY],
                                       double z, double v) {

    double r;

    temperature = new double*[NARRAY];
    for( int i=0; i<NARRAY; i++){
        temperature[i] = new double[MARRAY];

        for( int j=0; j<MARRAY; j++){
            r = sqrt(pow(dist_x[i], 2.0) + pow(dist_y[j], 2.0) + pow(z, 2.0));
            // std::cout << r << ' ';
            temperature[i][j] = initial_temperature
                                + ((voltage*amperage*efficiancy)/(2.0 * PI * thermal_conductivity))
                                * (1.0/r) * exp(-v/(2.0 * thermal_diffusivity)*(r + dist_x[i]));
        }
        // std::cout << '\n';
    }

    return temperature;
}