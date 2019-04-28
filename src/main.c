#include "statistics.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include "conv.h"
#include "FIR_filter.h"
#define PI 3.14

int main() {
    //image operations
    aek_image img=aek_imread("data/elma.jpg");
    img=aek_RGB_to_Gray(img);
    aek_setpixel3b(img,10,10,0,0,0);
    aek_color color;
    color.r=150;
    color.g=0;
    color.b=0;
    aek_setpixel(img,15,15,color);
    aek_imwrite_png(img,"out.png");

    //histogram
    int* histogram_gray=aek_histogram(img);
    printf("***************\n");
    printf("Histogram of image:\n");
    for(int i=0;i<256;i++){
        printf("%d:\t%d\n",i,histogram_gray[i]);
    }

    //mean from histogram
    printf("******************\n");
    printf("normal sum:\t%f\n",     Sum_uint8(img.data,img.w*img.h));
    printf("normal mean:\t%f\n",    Mean_uint8(img.data,img.w*img.h));
    printf("normal variance:\t%f\n",Variance_uint8(img.data,img.w*img.h));
    printf("******************\n");
    printf("histogram sum:\t%f\n",  Sum_histogram(histogram_gray,256));
    printf("histogram mean:\t%f\n",  Mean_histogram(histogram_gray,256));
    printf("histogram variance:\t%f\n",  Variance_histogram(histogram_gray,256));

    /**********************/
    /*stream variance demo*/
    /**********************/

    int count=100;
    double* a=(double*) malloc(sizeof(double*)*count);
    for(int i = 0; i < count; i++)
    {
        a[i]=i;
    }
    double sum=Sum(a,count);
    double mean=Mean(a,count);
    double variance=Variance(a,count);

    printf("*********************\n");
    printf("Stream variance demo\n");
    printf("normal sum:\t%f\n",sum);
    printf("normal mean:\t%f\n",mean);
    printf("normal variance:\t%f\n\n",variance);

    struct stat stat0;
    stat0.length=0;
    stat0.mean=0.0;
    stat0.s=0.0;
    stat0.variance=0.0;

    struct stat* stat_ptr;
    stat_ptr=&stat0;

    printf("val\tmean\t\tvariance\n");
    for(int i=0;i<count;i++){
        VarianceStream(stat_ptr,i);
        printf("%d\t%f\t%f\n", stat_ptr->length, stat_ptr->mean, stat_ptr->variance);
    }

    /*****************/
    /*  Convolution  */
    /*****************/
    printf("*********************\n");
    printf("Convolution Demo\n");
    int s_size=9;
    int h_size=4;
    double s[]={0,-1,-1.2,2,1.2,1.2,0.7,0,-0.7};
    double h[]={1,-0.5,-0.2,-0.1};
    double y[s_size+h_size-1];

    int temp=conv2(s,s_size,h,h_size,y);
    for(int i=0;i<s_size+h_size-1;i++){
        printf(" %.2f \n",y[i]);
    }

    /**************/
    /* FIR Filter */
    /**************/
    int signal_size = 6;
    int signal[]={1,2,3,4,5,6};
    int coefficients_size=5;
    int coefficients[]={-2,0,1,2,3};
    int output_y[signal_size];
    FIR_filter(signal,signal_size,coefficients,coefficients_size,output_y);
    printf("*********************\n");
    printf("FIR Filter Test\n");
    for(int i=0;i<signal_size;i++){
        printf("%d\n",output_y[i]);
    }

    printf("**************\n");
    printf("Sine wave test \nSampling Rate: 20KHz\nNumber of samples: 200\n");
    int numberOfSamples=200;
    int samplingRate=20000;

    int freq3K=3000;
    double sineWave3K[numberOfSamples];
    for(int i=0;i<numberOfSamples;i++){
        sineWave3K[i]=sin(2*PI*freq3K*(double)i/samplingRate);
    }

    int freq5K=5000;
    double sineWave5K[numberOfSamples];
    for(int i=0;i<numberOfSamples;i++){
        sineWave5K[i]=sin(2*PI*freq5K*(double)i/samplingRate);
    }

    printf("Fifth grade 4KHz low pass\n");
    double lowPass4KHz5G[5];
    lowPass4KHz5G[0]=0.075037080444813233914835848281654762104;
    lowPass4KHz5G[1]=0.284218843522212105678903526495560072362;
    lowPass4KHz5G[2]=0.381488152065949326363636373571353033185;
    lowPass4KHz5G[3]=0.284218843522212105678903526495560072362;
    lowPass4KHz5G[4]=0.075037080444813233914835848281654762104;
    
    double out1[numberOfSamples];
    FIR_filterd(sineWave3K,numberOfSamples,lowPass4KHz5G,5,out1);

    double out2[numberOfSamples];
    FIR_filterd(sineWave5K,numberOfSamples,lowPass4KHz5G,5,out2);

    printf("3K\t\toutput\t\t5K\t\toutput\n");
    for(int i=0;i<numberOfSamples;i++){
        printf("%f\t%f\t%f\t%f\n",sineWave3K[i],out1[i],sineWave5K[i],out2[i]);
    }

    return 0;
}