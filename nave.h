#ifndef NAVE_H
#define NAVE_H

#include <stddef.h>

typedef float nave_t[][2];

extern nave_t nave;
extern nave_t chorro;

//double computar_posicion(double pi, double vi, double dt);


void rotar_nave(nave_t element, size_t size_element, int grados_por_seg);   

int angulo_rotado(int angulo_anterior, int grados_por_seg);

void componentes_segun_angulo(int grados, float * x, float * y);

void trasladar_nave(nave_t element, size_t size_element, int angulo_nave);

//void center_nave(nave_t element, size_t size_element, float *center_x, float *center_y)



#endif 