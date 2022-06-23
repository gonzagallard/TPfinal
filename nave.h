#ifndef NAVE_H
#define NAVE_H

#include <stddef.h>

extern float nave[][2];
extern float chorro[][2];

//double computar_posicion(double pi, double vi, double dt);

//void trasladar(nave_t[][2], size_t n, float dx, float dy);

void rotar_nave(float nave[][2], double grados);


#endif 