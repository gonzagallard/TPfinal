#include <math.h>
#include <stdio.h>

#include "nave.h"
#include "config.h"

nave_t nave = {{8, 0}, {-1, 6}, {-4, 4}, {-4, 2}, {-2, 0}, {-4, -2}, {-4, -4}, {-1, -6}, {8, 0}};

nave_t chorro = {{-4, 2}, {-8, 0}, {-4, -2}};

double grad_a_rad(double grados){
    return (PI/180) * grados;
}

void rotar(nave_t element, size_t n, double rad){
    double coseno = cos(rad), seno = sin(rad);
    float element_x_aux, element_y_aux;

    for(size_t i = 0 ; i < n ; i++){ 
        element_x_aux = element[i][0]*coseno - element[i][1]*seno;
        element_y_aux = element[i][0]*seno + element[i][1]*coseno;

        element[i][0] = element_x_aux;
        element[i][1] = element_y_aux;
    }
}   

void rotar_nave(nave_t element, size_t n, double grados){
    double rad = grad_a_rad(grados);
    rotar(element, n, rad);
}

void trasladar(float nave[][2], size_t n, float dx, float dy){
    for(size_t i = 0 ; i < n ; i++){ 
        nave[i][0] += dx;
        nave[i][1] += dy;
    }
}



