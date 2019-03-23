#ifndef DSP_H
#define DSP_H

#include <stdint.h>

struct stat
{
    int length;
    double mean;
    double s;
    double variance;
};

double Sum(double* _input_array, int _count);
double Sum_i(int* _input_array, int _count);
double Sum_uint8(uint8_t* _input_array, int _count);
double Sum_histogram(int* _histogram, int _count);
double Mean(double* _input_array, int _count);
double Mean_i(int* _input_array, int _count);
double Mean_uint8(uint8_t* _input_array, int _count);
double Mean_histogram(int* _histogram, int _count);
double Variance(double* _input_array, int _count);
double Variance_i(int* _input_array, int _count);
double Variance_uint8(uint8_t* _input_array, int _count);
double Variance_histogram(int* _histogram, int _count);
int VarianceStream(struct stat *_old_stat, double _new_data);
int Max_Index(int* array,int size);


#endif