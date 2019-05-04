#include "DFT.h"

int dft_inverse(double ReX[],double ImX[],double x[],int size){
    memset(x,0,size*sizeof(double));

    double rex[size/2+1];
    double imx[size/2+1];
    for(int k=0;k<size/2+1;k++){
        rex[k]=ReX[k]/(size/2);
        imx[k]=-ImX[k]/(size/2);
    }
    rex[0]=ReX[0]/size;
    rex[size/2]=ReX[size/2]/size;

    for(int i=0;i<size;i++){
        for(int k=0;k<size/2+1;k++){
            x[i]+=rex[k]*cos(2*PI*k*i/size)+imx[k]*sin(2*PI*k*i/size);
        }
    }
    return 1;
}

int dft(double x[],int size, double ReX[], double ImX[]){
    memset(ReX,0,(size/2+1)*sizeof(double));
    memset(ImX,0,(size/2+1)*sizeof(double));
    for(int k=0;k<size/2+1;k++){
        for(int i=0;i<size;i++){
            ReX[k]+=x[i]*cos(2*PI*k*i/size);
            ImX[k]-=x[i]*sin(2*PI*k*i/size);
        }
    }
}