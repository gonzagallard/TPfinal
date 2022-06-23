#ifndef NAVE_H
#define NAVE_H

#include <stddef.h>

typedef float nave_t[][2];

extern nave_t nave;
extern nave_t chorro;

//double computar_posicion(double pi, double vi, double dt);

//void trasladar(nave_t[][2], size_t n, float dx, float dy);

void rotar_nave(nave_t element, size_t size_element, double grados_por_seg);   

int angulo_rotado(int angulo_anterior, int grados_por_seg);

void trasladar_nave(nave_t element, size_t size_element, float dframe_x, float dframe_y);





#endif 