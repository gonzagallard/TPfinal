#include <math.h>
#include <stdio.h>

#include "nave.h"
#include "config.h"

nave_t nave = {{8, 0}, {-1, 6}, {-4, 4}, {-4, 2}, {-2, 0}, {-4, -2}, {-4, -4}, {-1, -6}, {8, 0}};

nave_t chorro = {{-4, 2}, {-8, 0}, {-4, -2}};

double grad_a_rad(int grados){
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

void rotar_nave(nave_t element, size_t n, int grados){
    double rad = grad_a_rad(grados);
    rotar(element, n, rad);
}

int angulo_rotado(int angulo_ant, int grados){
    int grad_aux = angulo_ant;    
    grad_aux += grados;
    if(grad_aux < 0)
        return grad_aux % 360 + 360;
    else
        return grad_aux % 360; 
}

void trasladar(nave_t element, size_t n, float dx, float dy){
    for(size_t i = 0 ; i < n ; i++){ 
        element[i][0] += dx;
        element[i][1] += dy;
    }
}

float x, y;
void componentes_segun_angulo(int grados, float * x, float * y){
    double rad = grad_a_rad(grados);
    *x = cos(rad)*0.5;
    *y = sin(rad)*0.5;
}


void trasladar_nave(nave_t element, size_t n, int grado){
    componentes_segun_angulo(grado, &x, &y);
    trasladar(element, n, x, y);
}



