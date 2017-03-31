#include <iostream>
#include "rosenthal.h"


int main() {
    rosenthal weld (36.55265, 7059.5, 1000, 60000, 0.18, 0.8, 757.5);

    int i;
    double increament_x = 0.0005;
    double increament_y = 0.00005;
    double velocity = 2.4;
    double z = 0.001;
    double x_start = -2;
    double y_start = -0.005;
    double distance_x[NARRAY];
    double distance_y[MARRAY];

    for (i=0; i<NARRAY; i++){
        distance_x[i] = i * increament_x + x_start;
        // cout << distance_x[i] << '\n';
    }
    for (i=0; i<MARRAY; i++){
        distance_y[i] = i * increament_y + y_start;
    }

    double** temperatures =  weld.calculateRosenthal(distance_x, distance_y, z,
                                                     velocity);

    for( int i=0; i<NARRAY; i++){
        std::cout << distance_x[i] << ' ';
    }
    std::cout << '\n';

    for (i=0; i < MARRAY; i++){
        std::cout << distance_y[i] << ' ';
        for(int j=0; j < NARRAY; j++){
            std::cout << temperatures[j][i] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
