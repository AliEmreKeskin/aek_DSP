#ifndef DFT_H
#define DFT_H

#include <math.h>
#define PI 3.14159265358979323846

int dft_inverse(double ReX[],double ImX[],double x[],int size);

int dft(double x[],int size, double ReX[], double ImX[]);

#endif