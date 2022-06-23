#ifndef NAVE_H
#define NAVE_H

#include <stddef.h>

typedef float nave_t[][2];

extern nave_t nave;
extern nave_t chorro;

//double computar_posicion(double pi, double vi, double dt);

//void trasladar(nave_t[][2], size_t n, float dx, float dy);

void rotar_nave(float nave[][2], size_t n, double grados);

//void trasladar_nave(float nave[][2], )

#endif 