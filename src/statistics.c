#include "statistics.h"



double Sum(double* _input_array,int _count){
    double sum=0;
    
    for(int i=0;i<_count;i++){
        sum+=_input_array[i];
    }
    return sum;
}

double Mean(double* _input_array, int _count){
    return Sum(_input_array,_count)/_count;
}

double Mean_i(int* _input_array, int _count){
    return Sum_i(_input_array,_count)/_count;
}

double Variance(double* _input_array, int _count){
    double temp=0;
    double mean=Mean(_input_array,_count);
    for(int i=0;i<_count;i++){
        temp+=(_input_array[i]-mean)*(_input_array[i]-mean);
    }
    return temp/(_count-1);
}

int VarianceStream(struct stat *_old_stat, double _new_data){
    if(_old_stat->length==0){
        _old_stat->length++;
        _old_stat->mean=_new_data;
        _old_stat->s=0;
        _old_stat->variance=-1;
        return -1;
    }
    else{
        _old_stat->length++;
        double old_mean=_old_stat->mean;
        _old_stat->mean+=(_new_data-_old_stat->mean)/_old_stat->length;
        _old_stat->s+=(_new_data-old_mean)*(_new_data-_old_stat->mean);
        _old_stat->variance=_old_stat->s/(_old_stat->length-1);
        return 1;
    }    
}

int Max_Index(int* array,int size){
    int max=0;
    for(int i=1;i<size;i++){
        if(array[i]>array[max]){
            max=i;
        }
    }
    return max;
}

double Sum_i(int* _input_array, int _count){
    double sum=0;    
    for(int i=0;i<_count;i++){
        sum+=_input_array[i];
    }
    return sum;
}

double Sum_histogram(int* _histogram, int _count){
    double sum=0;
    for(int i=0;i<_count;i++){
        sum+=_histogram[i]*i;
    }
    return sum;
}

double Variance_i(int* _input_array, int _count){
    double temp=0;
    double mean=Mean_i(_input_array,_count);
    for(int i=0;i<_count;i++){
        temp+=(_input_array[i]-mean)*(_input_array[i]-mean);
    }
    return temp/(_count-1);
}

double Sum_uint8(uint8_t* _input_array, int _count){
    double sum=0;    
    for(int i=0;i<_count;i++){
        sum+=_input_array[i];
    }
    return sum;
}

double Mean_uint8(uint8_t* _input_array, int _count){
    return Sum_uint8(_input_array,_count)/_count;
}

double Variance_uint8(uint8_t* _input_array, int _count){
    double temp=0;
    double mean=Mean_uint8(_input_array,_count);
    for(int i=0;i<_count;i++){
        temp+=(_input_array[i]-mean)*(_input_array[i]-mean);
    }
    return temp/(_count-1);
}

double Mean_histogram(int* _histogram, int _count){
    double count=0;
    for(int i=0;i<_count;i++){
        count+=_histogram[i];
    }
    return Sum_histogram(_histogram,_count)/count;
}

double Variance_histogram(int* _histogram, int _count){
    double temp=0;
    double mean=Mean_histogram(_histogram,_count);
    for(int i=0;i<_count;i++){
        temp+=((i-mean)*(i-mean))*_histogram[i];
    }
    double count=0;
    for(int i=0;i<_count;i++){
        count+=_histogram[i];
    }
    return temp/(count-1);
}