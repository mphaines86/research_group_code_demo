//
// Created by michael on 3/16/17.
//

#ifndef TEST_PROJECT_ROSENTHAL_H
#define TEST_PROJECT_ROSENTHAL_H

// Define size of array (NxM) for rosenthal equation.
#define NARRAY 5000
#define MARRAY 200

class rosenthal {
    private:
        double thermal_conductivity, density, initial_temperature, voltage;
        double amperage, efficiancy, thermal_diffusivity, specific_heat;
        double** temperature;
    public:
        rosenthal(double thermal_conductivity, double density,
                  double intial_temperature, double voltage, double amperage,
                  double efficiancy, double specific_heat);

        double** calculateRosenthal(double dist_x[], double dist_y[], double z, double v);

};


#endif //TEST_PROJECT_ROSENTHAL_H
