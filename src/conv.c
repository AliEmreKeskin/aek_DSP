#include "conv.h"

int conv(double s[],int s_size, double h[], int h_size, double y[]){
    memset(y,0,(s_size+h_size-1)*sizeof(double));
    int i,j;
    for(i=0;i<s_size;i++){
        for(j=0;j<h_size;j++){
            y[i+j]+=s[i]*h[j];
        }
    }
    return 1;
}

int conv2(double s[],int s_size, double h[], int h_size, double y[]){
    memset(y,0,(s_size+h_size-1)*sizeof(double));
    int i,j;
    int y_size=s_size+h_size-1;
    for(i=0;i<y_size;i++){
        for(j=0;j<h_size;j++){
            if(i-j<0||i-j>s_size) continue;
            y[i]+=s[i-j]*h[j];
        }
    }
    return 1;
}