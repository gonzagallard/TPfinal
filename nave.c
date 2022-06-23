#include <math.h>

#include "nave.h"
#include "config.h"

float nave[][2] = {{8, 0}, {-1, 6}, {-4, 4}, {-4, 2}, {-2, 0}, {-4, -2}, {-4, -4}, {-1, -6}, {8, 0}};

float chorro[][2] = {{-4, 2}, {-8, 0}, {-4, -2}};

double grad_a_rad(double grados){
    return (PI/180) * grados;
}

void rotar(float nave[][2], size_t n, double rad){
    double coseno = cos(rad), seno = sin(rad);
    float px_aux, py_aux;

    for(size_t i = 0 ; i < n ; i++){ 
        px_aux = nave[i][0]*coseno - nave[i][1]*seno;
        py_aux = nave[i][0]*seno + nave[i][1]*coseno;

        nave[i][0] = px_aux;
        nave[i][1] = py_aux;
    }
}   

void rotar_nave(float nave[][2], double grados){
    double rad = grad_a_rad(grados);
    rotar(nave, 9, rad);
}


